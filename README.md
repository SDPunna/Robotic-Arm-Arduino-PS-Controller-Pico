<img width="512" height="232" alt="image" src="https://github.com/user-attachments/assets/3ac49396-af2b-4ec7-9eb0-1816da1bcece" />This project implements a wireless robotic arm control system using two Arduino boards communicating via nRF24L01 modules. The transmitter reads values from two analog joysticks, while the receiver converts this data into servo movements for a 4-DOF robotic arm.
Component	                             Role
Arduino UNO (Transmitter)	   |      Reads joystick inputs, sends data via nRF24L01
Arduino UNO (Receiver)	     |     Receives data, controls 4 servo motors
nRF24L01 (x2)	               |    2.4 GHz wireless communication
Dual Joystick Module	       |      4 analog axes (X1, Y1, X2, Y2)
4 Servo Motors	             |      Base, Shoulder, Elbow, Gripper/Wrist
