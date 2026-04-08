#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#include <Servo.h>

RF24 radio(9, 10); // CE, CSN
const byte address[6] = "00001";

int data[4]; // Received joystick values

// Create servo objects
Servo servo1; // Base
Servo servo2; // Shoulder
Servo servo3; // Elbow
Servo servo4; // Gripper / Wrist

void setup() {
  Serial.begin(9600);

  // Attach servos to PWM pins
  servo1.attach(3);
  servo2.attach(5);
  servo3.attach(6);
  servo4.attach(9);

  radio.begin();
  radio.openReadingPipe(0, address);
  radio.setPALevel(RF24_PA_MIN);
  radio.startListening(); // RX mode
}

void loop() {
  if (radio.available()) {
    radio.read(&data, sizeof(data));

    int x1 = data[0];
    int y1 = data[1];
    int x2 = data[2];
    int y2 = data[3];

    // Convert joystick (0–1023) → servo angle (0–180)
    int angle1 = map(x1, 0, 1023, 0, 180);
    int angle2 = map(y1, 0, 1023, 0, 180);
    int angle3 = map(x2, 0, 1023, 0, 180);
    int angle4 = map(y2, 0, 1023, 0, 180);

    // Move servos
    servo1.write(angle1);
    servo2.write(angle2);
    servo3.write(angle3);
    servo4.write(angle4);

    // Debug
    Serial.print("Angles: ");
    Serial.print(angle1); Serial.print(" ");
    Serial.print(angle2); Serial.print(" ");
    Serial.print(angle3); Serial.print(" ");
    Serial.println(angle4);
  }
}