#!/usr/bin/env python3
# -*- coding: utf-8 -*-

import sys, time, serial, socket, selectors, types

###########
# Constants

L_FATAL, L_ERROR, L_INFO, L_DEBUG = 0, 1, 2, 3
RECV_BUFSIZE = 256

###############
# Configurables

SERIAL_PORT = '/dev/ttyUSB0'
SERIAL_SPEED = 115200
ENABLE_SERIAL_WRITE = True
TCP_HOST = 'localhost'
# TCP_HOST = '0.0.0.0'
TCP_PORT = 14242
LOGLVL = L_DEBUG

###################
# Utility functions

S_LOGLVL = {0: 'FATAL',
            1: 'ERROR',
            2: 'INFO',
            3: 'DEBUG'}

def timestamp(t=None):
    if not t: t = time.time()
    return time.strftime('%Y-%m-%d %H:%M:%S', time.localtime(t))

def mylog(level, msg):
    if LOGLVL < level: return None
    msg = msg.rstrip()
    for ln in msg.splitlines():
        sys.stderr.write('[{}] ({}) {}\n'.format(timestamp(), S_LOGLVL[level], ln))
    return None


################
# Program begins

sel = selectors.DefaultSelector()

ser = serial.Serial(SERIAL_PORT, baudrate=SERIAL_SPEED)
ser.bytesize = serial.EIGHTBITS
ser.parity = serial.PARITY_NONE
ser.stopbits = serial.STOPBITS_ONE
ser.xonxoff = False
ser.rtscts = False
ser.dsrdtr = False
ser.timeout = 0

# Create a 'serial' type IO handle
data = types.SimpleNamespace(stype='serial', addr=None, inb=b'', outb=b'')
sel.register(ser, selectors.EVENT_READ, data=data)
mylog(L_INFO, 'Opened serial port '+SERIAL_PORT)
if ENABLE_SERIAL_WRITE:
    mylog(L_INFO, 'Serial write enabled.')
else:
    mylog(L_INFO, 'Serial write disabled.')

lsock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
lsock.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)

lsock.bind((TCP_HOST, TCP_PORT))
lsock.listen()
lsock.setblocking(False)
# Create a 'net_listener' type IO handle
data = types.SimpleNamespace(stype='net_listener', addr=None, inb=b'', outb=b'')
sel.register(lsock, selectors.EVENT_READ, data=data)
mylog(L_INFO, 'Listening on '+str(lsock.getsockname()))

net_clients = {}


###########
# Functions

def client_status():
    mylog(L_DEBUG, 'Now I have %d clients:' % len(net_clients))
    for c in net_clients:
        mylog(L_DEBUG, repr(net_clients[c].data.addr))
    return None


def cleanup_and_exit():
    try:
        sel.unregister(ser)
        ser.close()
    except:
        pass
    try:
        sel.unregister(lsock)
        lsock.close()
    except:
        pass
    for c in net_clients:
        try:
            f = net_clients[c].fileobj
            sel.unregister(f)
            f.close()
        except:
            pass
    mylog(L_INFO, 'Clean exit.')
    sys.exit(1)
    return None


# Handle serial port
# Duplicate data received to all 'net_client' type IO handles
def handle_serial(key, mask):
    f = key.fileobj
    data = key.data

    if mask & selectors.EVENT_READ:
        try:
            ser_data = f.read(1024)
        except:
            ser_data = None

        if ser_data:
            mylog(L_DEBUG, 'serial read: '+str(ser_data))
            for c in net_clients:
                ckey = net_clients[c]
                ckey.data.outb += ser_data
                # Enable write events to actually send them
                sel.modify(ckey.fileobj,
                           selectors.EVENT_READ|selectors.EVENT_WRITE,
                           ckey.data)
        else:
            mylog(L_ERROR, 'serial EVENT_READ: cannot read. Exit.')
            return cleanup_and_exit()

    if mask & selectors.EVENT_WRITE:
        if not data.outb:
            # Should not happen
            mylog(L_ERROR, 'serial EVENT_WRITE with no data? Turn off write events.')
            sel.modify(f, selectors.EVENT_READ, data)
            return None

        try:
            wrote = f.write(data.outb)
        except:
            wrote = 0
        if wrote > 0:
            data.outb = data.outb[wrote:]
            if not data.outb:
                # Output buffer is empty, disable write events to save cpu.
                sel.modify(f, selectors.EVENT_READ, data)
        else:
            # Our serial port is gone?
            mylog(L_INFO, 'serial EVENT_WRITE: cannot write. Exit.')
            return cleanup_and_exit()
    return None


# Handle listener
# New IO handles of type 'net_client' are made here.
def handle_listener(key, mask):
    f = key.fileobj
    data = key.data

    try:
        conn, addr = f.accept()
    except:
        mylog(L_ERROR, 'accept failed.')
        return None

    mylog(L_INFO, 'accepted connection from '+str(addr))
    conn.setblocking(False)
    newdata = types.SimpleNamespace(stype='net_client', addr=addr, inb=b'', outb=b'')
    # Now enable only read events
    # Write events get enabled when we have something to write
    net_clients[conn] = sel.register(conn,
                                     selectors.EVENT_READ,
                                     data=newdata)
    if LOGLVL >= L_DEBUG: client_status()
    return None


# Handle network clients, type 'net_client'
def handle_client(key, mask):
    f = key.fileobj
    data = key.data

    # We received something, or the socket was closed.
    if mask & selectors.EVENT_READ:
        try:
            recv_data = f.recv(RECV_BUFSIZE)
        except:
            recv_data = None
        if recv_data:
            mylog(L_INFO, 'Received %d bytes from client %s'
                  % (len(recv_data), str(data.addr)))
            mylog(L_DEBUG, 'data: '+str(recv_data))
            if ENABLE_SERIAL_WRITE:
                mylog(L_DEBUG, 'writing to serial')
                ser_key = sel.get_key(ser)
                ser_key.data.outb += recv_data
                # Enable write events to actually send them
                sel.modify(ser_key.fileobj,
                           selectors.EVENT_READ|selectors.EVENT_WRITE,
                           ser_key.data)
        else:
            # Our client is gone.
            mylog(L_INFO, 'EVENT_READ: closing connection to '+str(data.addr))
            sel.unregister(f)
            del net_clients[f]
            f.close()
            if LOGLVL >= L_DEBUG: client_status()

    # We are to write something
    if mask & selectors.EVENT_WRITE:
        if not data.outb:
            # Should not happen
            mylog(L_ERROR, 'net_client EVENT_WRITE with no data? Turn off write events.')
            sel.modify(f, selectors.EVENT_READ, data)
            return None

        try:
            sent = f.send(data.outb)
        except:
            sent = 0
        if sent > 0:
            data.outb = data.outb[sent:]
            if not data.outb:
                # Output buffer is empty, disable write events to save cpu.
                sel.modify(f, selectors.EVENT_READ, data)
        else:
            # Our client is gone.
            mylog(L_INFO, 'EVENT_WRITE: closing connection to '+str(data.addr))
            sel.unregister(f)
            del net_clients[f]
            f.close()
            if LOGLVL >= L_DEBUG: client_status()
    return None


###################
# Main program loop

while True:
    events = sel.select(timeout=None)
    for key, mask in events:
        t = key.data.stype
        if t == 'serial':
            handle_serial(key, mask)
        if t == 'net_listener':
            handle_listener(key, mask)
        if t == 'net_client':
         handle_client(key, mask)

# not reached
sys.exit(0)
# EOF
