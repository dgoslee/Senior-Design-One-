import serial

ser = serial.Serial('/dev/ttyUSB0', 9600, timeout=5)
ser.flushInput()

while True:
    if ser.in_waiting > 0:

        A = ser.readline().split()
        print(A)

