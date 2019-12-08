#!/usr/bin/env python                    
# -*- coding: utf-8 -*-

import sys, time, serial

sys.stdout.write('Status: 200 OK\r\n'
                 'Content-Type: text/event-stream\r\n'
                 'Cache-Control: no-cache\r\n'
                 '\r\n')
sys.stdout.flush()

with serial.Serial('/dev/ttyUSB0', baudrate=9600) as c:
    c.timeout = None
    c.bytesize = serial.EIGHTBITS
    c.parity = serial.PARITY_NONE
    c.stopbits = serial.STOPBITS_ONE
    c.xonxoff = False
    c.rtscts = False
    c.dsrdtr = False

    while True:
        line = c.readline()
        line = line.rstrip()
        sys.stdout.write('ID: %f\r\n'
                         'SENSOR READINGS: %s\r\n'
                         '\r\n' % (time.time(), line))
        sys.stdout.flush()

# not reached
sys.exit(0)
# EOF
