# Wireless Robotic Arm Control System

A wireless control system for robotic arms using dual joysticks and nRF24L01 RF modules. The system enables real-time control of 4 servo motors through 2 analog joysticks, providing intuitive wireless operation up to 100 meters range.


## 🎯 Overview

This project implements a wireless robotic arm control system with the following features:

- **Dual Joystick Control**: Two analog joysticks control 4 degrees of freedom
- **Wireless Communication**: 2.4GHz RF communication using nRF24L01 modules
- **Real-time Response**: 100ms update rate for smooth servo movements
- **Servo Mapping**: Automatic conversion from joystick values (0-1023) to servo angles (0-180°)
- **Serial Debugging**: Built-in debug output for monitoring system performance

### Control Mapping

| Joystick | Axis | Controls | Function |
|----------|------|----------|----------|
| Joystick 1 | X-axis (A0) | Servo 1 | Base rotation |
| Joystick 1 | Y-axis (A1) | Servo 2 | Shoulder movement |
| Joystick 2 | X-axis (A3) | Servo 3 | Elbow movement |
| Joystick 2 | Y-axis (A2) | Servo 4 | Gripper/Wrist control |

## 🏗️ System Architecture

<img width="512" height="232" alt="image" src="https://github.com/user-attachments/assets/3aa62411-b7f6-4d1b-996c-d2b4cba545a3" />



### Communication Flow

<img width="512" height="232" alt="image" src="https://github.com/user-attachments/assets/aafc1966-eed2-4a64-bb0f-629cd109282d" />


## 🔧 Hardware Requirements

### Transmitter Side (Controller)

| Component | Quantity | Specifications |
|-----------|----------|----------------|
| Arduino UNO | 1 | ATmega328P |
| Analog Joystick Module | 2 | 2-axis with push button (optional) |
| nRF24L01 RF Module | 1 | 2.4GHz transceiver |
| Regulated Power Supply | 1 | 5V and 3.3V outputs |
| Battery | 1 | 7-12V (depending on regulator) |
| Jumper Wires | As needed | Male-to-male and male-to-female |

### Receiver Side (Robotic Arm)

| Component | Quantity | Specifications |
|-----------|----------|----------------|
| Arduino UNO | 1 | ATmega328P |
| nRF24L01 RF Module | 1 | 2.4GHz transceiver |
| Servo Motors | 4 | SG90 or MG996R (depending on load) |
| Regulated Power Supply | 1 | 5V for Arduino, appropriate voltage for servos |
| Battery | 1 | Capacity based on servo requirements |

### Additional Components

- Breadboard or PCB for connections
- Capacitors (10µF, 100nF) for power filtering
- External power supply for servos (recommended for 4 servos)

## 📐 Wiring Diagrams

<img width="512" height="301" alt="image" src="https://github.com/user-attachments/assets/acd4b9bb-d897-4107-8d46-22c9607ededa" />

<img width="512" height="436" alt="image" src="https://github.com/user-attachments/assets/cdd01069-0d45-4674-80ea-03622350f9f4" />



### Transmitter (Controller) Connections

#### Arduino UNO to Joystick 1

Joystick 1:
  VCC  → 5V
  GND  → GND
  VRx  → A0 (X-axis)
  VRy  → A1 (Y-axis)


#### Arduino UNO to Joystick 2

Joystick 2:
  VCC  → 5V
  GND  → GND
  VRx  → A3 (X-axis)
  VRy  → A2 (Y-axis)


#### Arduino UNO to nRF24L01 Module

nRF24L01:
  VCC  → 3.3V (IMPORTANT: Not 5V!)
  GND  → GND
  CE   → Pin 9
  CSN  → Pin 10
  SCK  → Pin 13 (SPI)
  MOSI → Pin 11 (SPI)
  MISO → Pin 12 (SPI)


**⚠️ CRITICAL**: The nRF24L01 module operates at 3.3V. Connecting to 5V will damage the module!

### Receiver (Robotic Arm) Connections

#### Arduino UNO to nRF24L01 Module

nRF24L01:
  VCC  → 3.3V (IMPORTANT: Not 5V!)
  GND  → GND
  CE   → Pin 9
  CSN  → Pin 10
  SCK  → Pin 13 (SPI)
  MOSI → Pin 11 (SPI)
  MISO → Pin 12 (SPI)


#### Arduino UNO to Servo Motors

Servo 1 (Base):
  Signal  → Pin 3
  VCC     → External 5-6V supply
  GND     → Common GND

Servo 2 (Shoulder):
  Signal  → Pin 5
  VCC     → External 5-6V supply
  GND     → Common GND

Servo 3 (Elbow):
  Signal  → Pin 6
  VCC     → External 5-6V supply
  GND     → Common GND

Servo 4 (Gripper/Wrist):
  Signal  → Pin 9
  VCC     → External 5-6V supply
  GND     → Common GND
```

**⚠️ NOTE**: Connect all GNDs together (Arduino GND, servo GND, and power supply GND) to ensure proper operation.

## 💻 Software Setup

### Required Libraries

Both transmitter and receiver require the following Arduino libraries:

1. **RF24** - For nRF24L01 communication
   - Install via Library Manager: `Sketch → Include Library → Manage Libraries → Search "RF24"`
   - Or download from: https://github.com/nRF24/RF24

2. **SPI** - For SPI communication (built-in with Arduino IDE)

3. **Servo** - For servo motor control (built-in with Arduino IDE, receiver only)

### Arduino IDE Configuration

1. **Board**: Arduino UNO
2. **Port**: Select the appropriate COM port
3. **Programmer**: AVRISP mkII (or default)


## 🎮 Usage

### Starting the System

1. **Power Up Sequence**:
   - Turn on receiver (robotic arm) first
   - Wait 2-3 seconds for initialization
   - Turn on transmitter (controller)

2. **Verify Communication**:
   - Open Serial Monitor on transmitter (9600 baud)
   - You should see continuous output of joystick values
   - Open Serial Monitor on receiver (9600 baud)
   - You should see continuous output of servo angles

3. **Control the Robotic Arm**:
   - Move Joystick 1 X-axis: Controls base rotation (Servo 1)
   - Move Joystick 1 Y-axis: Controls shoulder movement (Servo 2)
   - Move Joystick 2 X-axis: Controls elbow movement (Servo 3)
   - Move Joystick 2 Y-axis: Controls gripper/wrist (Servo 4)

### Serial Monitor Output

**Transmitter Output Example**:
```
TX -> 512 498 520 510
TX -> 723 501 519 508
TX -> 1020 499 521 512
```
Format: `X1 Y1 X2 Y2` (raw analog values 0-1023)

**Receiver Output Example**:
```
Angles: 90 87 91 89
Angles: 127 88 91 89
Angles: 179 87 91 90
```
Format: `Angle1 Angle2 Angle3 Angle4` (mapped servo angles 0-180°)

## 🔍 Code Explanation

### Transmitter Code Structure

```cpp
// Initialize RF24 radio
RF24 radio(9, 10);  // CE=9, CSN=10

// Communication address (must match receiver)
const byte address[6] = "00001";

// Joystick analog pins
int joystickX1 = A0;  // Joystick 1 X-axis
int joystickY1 = A1;  // Joystick 1 Y-axis
int joystickX2 = A3;  // Joystick 2 X-axis
int joystickY2 = A2;  // Joystick 2 Y-axis
```

**Key Functions**:
- `radio.begin()`: Initialize nRF24L01 module
- `radio.openWritingPipe(address)`: Set transmission address
- `radio.setPALevel(RF24_PA_MIN)`: Set power level (MIN/LOW/HIGH/MAX)
- `radio.stopListening()`: Set to transmitter mode
- `analogRead()`: Read joystick positions
- `radio.write()`: Send data packet

### Receiver Code Structure

```cpp
// Initialize RF24 radio
RF24 radio(9, 10);  // CE=9, CSN=10

// Communication address (must match transmitter)
const byte address[6] = "00001";

// Create servo objects
Servo servo1;  // Base
Servo servo2;  // Shoulder
Servo servo3;  // Elbow
Servo servo4;  // Gripper/Wrist
```

**Key Functions**:
- `servo.attach(pin)`: Attach servo to PWM pin
- `radio.startListening()`: Set to receiver mode
- `radio.available()`: Check if data is available
- `radio.read()`: Read incoming data
- `map(value, fromLow, fromHigh, toLow, toHigh)`: Convert joystick to servo angle
- `servo.write(angle)`: Move servo to specified angle

### Data Transfer Protocol

**Data Packet Structure**:
```cpp
int data[4] = {xValue1, yValue1, xValue2, yValue2};
```
- Size: 8 bytes (4 integers × 2 bytes each)
- Update rate: 10 Hz (100ms delay)
- Address: "00001" (5-byte address)

## 🔧 Troubleshooting

### Common Issues and Solutions

#### 1. No Communication Between Modules

**Symptoms**: Receiver shows no output, servos don't move

**Solutions**:
- ✅ Verify both modules use the same address: `"00001"`
- ✅ Check nRF24L01 connections (especially CE and CSN pins)
- ✅ Ensure nRF24L01 is powered with 3.3V, not 5V
- ✅ Add 10µF capacitor across VCC and GND of nRF24L01
- ✅ Reduce distance between modules for testing (< 1 meter)
- ✅ Check power supply stability

#### 2. Servos Jittering or Not Moving Smoothly

**Symptoms**: Servos shake, move erratically, or don't respond

**Solutions**:
- ✅ Use external power supply for servos (not Arduino 5V pin)
- ✅ Ensure common ground between Arduino and servo power supply
- ✅ Add capacitors (100µF) across servo power lines
- ✅ Check servo wire connections
- ✅ Reduce update rate if necessary (increase delay)

#### 3. Joystick Not Centering at 90°

**Symptoms**: Servos don't center when joystick is at rest

**Solutions**:
- ✅ Calibrate joystick center values:
  ```cpp
  // Read center position values
  int centerX1 = analogRead(joystickX1);  // e.g., 512
  int centerY1 = analogRead(joystickY1);
  
  // Adjust mapping
  int angle1 = map(x1, 0, 1023, 0, 180);
  ```
- ✅ Add deadzone in code:
  ```cpp
  if (abs(xValue1 - 512) < 20) xValue1 = 512;  // Deadzone
  ```

#### 4. nRF24L01 Module Not Detected

**Symptoms**: Radio.begin() fails, no communication

**Solutions**:
- ✅ Check SPI connections (pins 11, 12, 13)
- ✅ Verify 3.3V power supply
- ✅ Try different nRF24L01 module (they can be faulty)
- ✅ Add 10µF capacitor across VCC-GND
- ✅ Use nRF24L01+ with external antenna for better range

#### 5. Serial Monitor Shows No Output

**Symptoms**: Blank Serial Monitor

**Solutions**:
- ✅ Check baud rate is set to 9600
- ✅ Verify correct COM port is selected
- ✅ Ensure USB cable is data-capable (not charge-only)
- ✅ Re-upload code

#### 6. Servo Movement Reversed

**Symptoms**: Servo moves opposite to joystick direction

**Solutions**:
- ✅ Reverse the mapping:
  ```cpp
  int angle1 = map(x1, 0, 1023, 180, 0);  // Reversed
  ```

## 🎯 Performance Specifications

| Parameter | Value |
|-----------|-------|
| Update Rate | 10 Hz (100ms) |
| RF Frequency | 2.4 GHz |
| Communication Range | Up to 100m (line of sight) |
| Data Packet Size | 8 bytes |
| Power Consumption (TX) | ~50mA (active) |
| Power Consumption (RX) | ~50mA + servo current |
| Servo Response Time | ~20ms (typical) |

## 🚀 Future Enhancements

### Results

<img width="330" height="330" alt="image" src="https://github.com/user-attachments/assets/768dfe0c-e22c-422e-9a62-9fe086b60cac" />


<img width="330" height="330" alt="image" src="https://github.com/user-attachments/assets/e1754435-ebaa-4ebe-8553-f44ef1ab7859" />


<img width="344" height="194" alt="image" src="https://github.com/user-attachments/assets/d3fb80e8-abf0-493f-b1f4-4338bc59d086" />


<img width="383" height="219" alt="image" src="https://github.com/user-attachments/assets/587baf8c-a769-48bb-aa2a-01fdbd91ac48" />


### Potential Improvements

1. **Add Buttons for Gripper Control**:
   ```cpp
   int buttonPin = 2;
   bool gripperState = false;
   
   if (digitalRead(buttonPin) == LOW) {
     gripperState = !gripperState;
     servo4.write(gripperState ? 0 : 180);
   }
   ```

2. **Implement Smooth Servo Movement**:
   ```cpp
   // Use servo easing library or custom interpolation
   for (int pos = currentAngle; pos <= targetAngle; pos++) {
     servo1.write(pos);
     delay(15);
   }
   ```

3. **Add Position Memory**:
   ```cpp
   #include <EEPROM.h>
   
   // Save position
   EEPROM.write(0, angle1);
   EEPROM.write(1, angle2);
   
   // Recall position
   int savedAngle1 = EEPROM.read(0);
   ```

4. **Implement Error Checking**:
   ```cpp
   unsigned long lastReceiveTime = 0;
   
   if (radio.available()) {
     radio.read(&data, sizeof(data));
     lastReceiveTime = millis();
   }
   
   // Safety timeout
   if (millis() - lastReceiveTime > 1000) {
     // Stop all servos or move to safe position
     servo1.write(90);
     servo2.write(90);
     // ...
   }
   ```

5. **Add LCD Display**:
   - Show current angles
   - Display battery voltage
   - Show signal strength

6. **Implement Speed Control**:
   ```cpp
   int speedPot = A4;  // Potentiometer for speed
   int speed = map(analogRead(speedPot), 0, 1023, 10, 200);
   delay(speed);
   ```

## 📝 License

This project is open-source and available under the MIT License.

## 🤝 Contributing

Contributions are welcome! Please feel free to submit pull requests or open issues for bugs and feature requests.

## ⚠️ Safety Notes

1. **Power Safety**:
   - Never connect 5V to nRF24L01 (3.3V only!)
   - Use appropriate current capacity for servos
   - Add fuses to prevent overcurrent

2. **Mechanical Safety**:
   - Ensure robotic arm cannot harm people or damage objects
   - Add physical limits to movement range
   - Implement emergency stop functionality

3. **RF Safety**:
   - Ensure no interference with critical systems
   - Follow local regulations for 2.4GHz devices

## 📧 Support

For questions or issues:
- Open an issue on GitHub
- Check the troubleshooting section
- Review the RF24 library documentation: https://nrf24.github.io/RF24/

## 🙏 Acknowledgments

- RF24 library by TMRh20
- Arduino community for examples and support
- nRF24L01 module manufacturers

---

**Version**: 1.0  
**Last Updated**: 2024  
**Status**: Active Development

**Happy Building! 🤖**
