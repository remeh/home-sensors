#!/usr/bin/python2

import httplib
import json
import time
import serial
import sys

# configuration
server = 'http://localhost:9000'
sensorId = '1'
header = 'X-Header'

# global var containing the sensors values
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
    call_server(temp, light, presence)

def call_server(temp, light, presence):
    global server
    global sensorId

    data = {'values':[{'type': 'temp', 'value': temp}, {'type': 'presence', 'value': 1}, {'type': 'light', 'value': light}]}
    body = json.dumps(data)

    http = httplib.HTTPConnection('remy.io', 9005, timeout=10)
    headers = { "Content-Type": "application/json", header: 'OK' }
    http.request('POST', '/api/hit/' + sensorId, body, headers)
    http.close()

def listener(argv):
    if len(argv) == 0:
        print('Not enough argument:\n python2 serial_listener.py port baudrate')
        sys.exit(1)

    call_server(10, 5, 1)

    ser = serial.Serial(argv[0], argv[1])

    while 1:
        data = ser.readline().strip()
        process_line(data)
    ser.close()

if __name__ == '__main__':
    listener(sys.argv[1:])
