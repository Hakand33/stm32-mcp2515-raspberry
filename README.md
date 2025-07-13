# CAN-Servo Control with Raspberry Pi

This project enables a Raspberry Pi to control a servo motor based on incoming CAN messages received over UART. The messages are assumed to be forwarded from an STM32 + MCP2515 setup.

## Features

- UART communication at 115200 baud
- Interprets CAN messages in text format (e.g., `CAN_ID:0x101 DATA: 5A`)
- Controls a servo motor connected to GPIO17 (BCM mode)
- Responds to specific CAN data values:
  - `DATA: 00` → 0°
  - `DATA: 5A` → 90°
  - `DATA: B4` → 180°

## Hardware Setup

- Raspberry Pi (any model with `/dev/serial0`)
- Servo motor (e.g., SG90 or MG90)
- MCP2515 CAN module (external, sends CAN messages via STM32)
- GPIO17 → Servo PWM control

## Wiring Diagram
MCP2515 | STM32 (SPI1) | Raspberry Pi  
--------------------------------  
VCC    | 3.3V         | 3.3V  
GND    | GND          | GND  
CS     | PA4          | GPIO8 (CE0)  
SCK    | PA5          | GPIO11 (SCLK)  
SI     | PA7          | GPIO10 (MOSI)  
SO     | PA6          | GPIO9 (MISO)  

## Project Highlights

- CAN Bus communication between STM32 and Raspberry Pi via MCP2515
- Python script on Raspberry Pi reads messages from UART
- Servo motor positioning (0°, 90°, 180°) based on CAN message content
- Low-level C drivers for MCP2515 communication (no external libraries)
- UART redirection on STM32 using custom `retarget.c/h` files for debugging

- ##  Raspberry Pi Code (Python)

Located at: `rpi/can_servo_control.py`

- Listens on `/dev/serial0` at 115200 baud
- Accepts strings like: `CAN_ID:0x101 DATA: 5A`
- Interprets data:
  - `00` → `0°`
  - `5A` → `90°`
  - `B4` → `180°`
- Uses PWM on GPIO17 (BCM) to control servo
- 
- ## STM32 Code

| File Name       | Description                                                                                     
| `main.c`        | Main application file. CAN message transmission via MCP2515 is implemented here.                
| `main.h`        | Header file. Contains function prototypes and global definitions.                              
| `mcp2515.c`     | Contains MCP2515 SPI communication functions. Basic commands such as RESET, READ, WRITE, RTS, BIT_MODIFY are defined here. 
| `mcp2515.h`     | Contains MCP2515 register addresses, command constants, and function prototypes.                
| `retarget.c`    | Redirects output functions like `printf()` to UART for debugging purposes.              

## Run Instructions:
```bash
# Enable UART on Pi (disable shell over serial)
sudo raspi-config

# Clone repo and run
git clone https://github.com/yourusername/can-servo-project.git
cd can-servo-project/rpi
python3 can_servo_control.py
