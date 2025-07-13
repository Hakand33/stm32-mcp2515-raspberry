import serial
import time
import RPi.GPIO as GPIO


ser = serial.Serial(
    port = '/dev/serial0',
    baudrate=115200,
    timeout=1
)
SERVO_PIN = 17
GPIO.setmode(GPIO.BCM)
GPIO.setup(SERVO_PIN, GPIO.OUT)

servo = GPIO.PWM(SERVO_PIN, 50)
servo.start(0)

def set_angle(angle):
    duty = 2 + (angle / 18)
    servo.ChangeDutyCycle(duty)
    print(f"Servo > {angle} (duty: {duty:.2f})")
    
print("UART Dinleniyor")


try:
    while True:
        if ser.in_waiting:
            line= ser.readline().decode('utf-8',errors='ignore').strip()
            print("[Gelen] = " , line)
            
            if "CAN_ID:0x101" in line:
                
                if "DATA: 00" in line:
                    set_angle(0)
                elif "DATA: 5A" in line:
                    set_angle(90)
                elif "DATA: B4" in line:
                    set_angle(180)
        time.sleep(0.1)
        
except KeyboardInterrupt:
    servo.stop()
    GPIO.cleanup()
    print("Program sonlandırıldı")
    
    
                    
    
