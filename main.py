import serial
import pyvjoy
import time

arduino = serial.Serial('COM10', 115200, timeout=1)
time.sleep(2) 

j = pyvjoy.VJoyDevice(1)

def map_encoder_to_axis(pos):
    return int((pos + 100) * (32767 / 200))  

def map_button_to_axis(val): 
    return int(val * (32767 / 1023)) 

try:
    while True:
        line = arduino.readline().decode().strip()
        if line:
            try:
                parts = line.split(',')
                if len(parts) != 3:
                    continue

                pos = int(parts[0])  
                gaz = int(parts[1])   
                fren = int(parts[2]) 

                axis_x = map_encoder_to_axis(pos)
                axis_y = map_button_to_axis(gaz)
                axis_rz = map_button_to_axis(fren)

                j.set_axis(pyvjoy.HID_USAGE_X, axis_x)    
                j.set_axis(pyvjoy.HID_USAGE_Y, axis_y)   
                j.set_axis(pyvjoy.HID_USAGE_RZ, axis_rz)  

                print(f"Direksiyon: {pos}, Gaz: {gaz}, Fren: {fren}")
            except ValueError:
                pass
except KeyboardInterrupt:
    print("Program sonlandırıldı.")
