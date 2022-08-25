import serial
import time
import numpy as np

# #arduino = serial.Serial('COM4', 9600)
arduino = serial.Serial('/dev/ttyACM0', baudrate=9600, timeout=0.5)

l1 = 2
l2 = 2
x = 3
y = 4

q2 = np.arccos( (x**2 + y**2 - l1**2 - l2**2) / (2*l1*l2) )
q1 = np.arctan(y/x) - np.arctan(l2*np.sin(q2)/(l1 + l2*np.arccos(q2)))

str_q1 = "000"
if q1 < 10:
    str_q1 = "00" + str(q1)
elif q1 < 100:
    str_q1 = "0" + str(q1)
else:
    str_q1 = str(q1)

if q2 < 10:
    str_q1 = "00" + str(q2)
elif q2 < 100:
    str_q2 = "0" + str(q2)
else:
    str_q2 = str(q2)

command1 = "8," + str_q1
command2 = "9," + str_q2

print("Command 1: " + command1)
print("Command 2: " + command2)

arduino.write(command1.encode())
arduino.write(command2.encode())