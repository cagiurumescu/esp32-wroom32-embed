import serial

ser = serial.Serial('/dev/ttyUSB1', baudrate=115200)
ser.write(b'AT+GMR\r\n')
ser.flush()
print(str(ser.readline(),'utf-8'), end='')
print(str(ser.readline(),'utf-8'), end='')
print(str(ser.readline(),'utf-8'), end='')
print(str(ser.readline(),'utf-8'), end='')
