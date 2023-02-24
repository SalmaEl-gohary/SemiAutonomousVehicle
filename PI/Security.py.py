import RPi.GPIO as GPIO
import board
import busio
from digitalio import DigitalInOut, Direction
import adafruit_fingerprint
import serial
import pynmea2

uart = serial.Serial("/dev/ttyUSB0", baudrate=57600, timeout=1)


finger = adafruit_fingerprint.Adafruit_Fingerprint(uart)



def get_fingerprint():
    """Get a finger print image, template it, and see if it matches!"""
    while finger.get_image() != adafruit_fingerprint.OK:
        pass
    if finger.image_2_tz(1) != adafruit_fingerprint.OK:
        return False
    if finger.finger_search() != adafruit_fingerprint.OK:
        return False
    return True




##################################################



while True:
	
    if finger.read_templates() != adafruit_fingerprint.OK:
        raise RuntimeError("Failed to read templates")

    if get_fingerprint():
	    port = "/dev/ttyS0"
	    ser2 = serial.Serial(port, baudrate = 9600, timeout = 0.5)
	    ser2.write('A'.encode())
	    break
		
	
	
			
                

    else:
	    GPIO.output(2,GPIO.HIGH)
	    time.sleep(0.5)
	    GPIO.output(2,GPIO.LOW)
	    time.sleep(0.5)


	
	
