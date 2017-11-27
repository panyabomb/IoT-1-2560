import RPi.GPIO as GPIO
import time

LedPin = 21    # pin21

def setup():
    GPIO.setwarnings(False)
    #GPIO.setmode(GPIO.BOARD)       # Numbers GPIOs by physical location
    GPIO.setmode(GPIO.BCM)       # Numbers GPIOs by Broadcom pin
    GPIO.setup(LedPin, GPIO.OUT)   # Set LedPin's mode is output
    GPIO.output(LedPin, GPIO.HIGH) # Set LedPin high(+3.3V) to turn on led

def blink():
    while True:
        print("LED ON")
        GPIO.output(LedPin, GPIO.HIGH)  # led on
        time.sleep(1)
        print("LED OFF")
        GPIO.output(LedPin, GPIO.LOW)   # led off
        time.sleep(1)

def destroy():
    GPIO.output(LedPin, GPIO.LOW)   # led off
    GPIO.cleanup()                  # Release resource

if __name__ == '__main__':     # Program start from here
    setup()
    try:
        blink()
    except KeyboardInterrupt:  # When 'Ctrl+C' is pressed, the child program destroy() will be  executed.
        destroy()
