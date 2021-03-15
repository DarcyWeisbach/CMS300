import spidev
import time
#import datetime
import RPi.GPIO as GPIO

BIT_OUT = 12
RESET = 26

def setup():
    GPIO.setwarnings(False)
    GPIO.setmode(GPIO.BCM)
    GPIO.setup(BIT_OUT,GPIO.IN)
    GPIO.setup(RESET,GPIO.OUT)
    

def main():
    bit_status = GPIO.input(BIT_OUT)
    print(bit_status)
    send_data = [0x00,0x00,0xA1,0x01]
    

    received_data = spi.xfer2(send_data)
    #received_data2 = spi.readbytes(4)
    received_data = [hex(i) for i in received_data]
    #received_data2 = [hex(i) for i in received_data2]
    print(received_data)
    #print(received_data2)
    

if __name__ =='__main__':
    setup()
    try:
        while(1):
            spi = spidev.SpiDev()
            spi.open(0,0)
            spi.max_speed_hz =1000000
            spi.mode=0
            GPIO.output(RESET,0)
            GPIO.output(RESET,1)
            main()
            #time.sleep(1)
            spi.close
    except KeyboardInterrupt:
        destroy()
        

