import serial 
import time 

arduino = serial.Serial(port='COM5', baudrate=115200, timeout=1) 

def write_read(x): 
    arduino.write(bytes(x, 'utf-8')) 
    time.sleep(0.5) 
    data = arduino.readline() 
    return str(data)


while True: 
    num = input("Enter a command: ") # Taking input from user 
    value = write_read(num).split('\'')[1].split('\\')[0]
    print(value) # printing the value 


 #  "1?3?200"  write in A7 200