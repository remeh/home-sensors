#!/usr/bin/python2

import time
import serial
import sys

temp = 0
light = 0
presence = False

def process_line(data):
    global temp
    global light
    global presence

    parts = data.split(' ')

    for part in parts:
        if part[0] == 'T':
            temp = part[1:]
        if part[0] == 'L':
            light = part[1:]
        if part[0] == 'P':
            if part[1] == '1':
                presence = True
            else:
                presence = False

    print('T%s L%s P%s' % (temp, light, presence))

def listener(argv):
    if len(argv) == 0:
        print('Not enough argument:\n python2 serial_listener.py port baudrate')
        sys.exit(1)

    ser = serial.Serial(argv[0], argv[1])

    while 1:
        data = ser.readline().strip()
        process_line(data)
    ser.close()

if __name__ == '__main__':
    listener(sys.argv[1:])
