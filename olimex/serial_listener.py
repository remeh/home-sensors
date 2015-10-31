#!/usr/bin/python2

import time
import serial
import sys

def listener(argv):
    if len(argv) == 0:
        print('Not enough argument:\n python2 serial_listener.py port baudrate')
        sys.exit(1)
    ser = serial.Serial(argv[0], argv[1])
    while 1:
        serial_line = ser.readline()
        print(serial_line.strip())
    ser.close()

if __name__ == '__main__':
    listener(sys.argv[1:])
