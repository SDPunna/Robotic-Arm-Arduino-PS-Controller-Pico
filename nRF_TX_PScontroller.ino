#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

RF24 radio(9, 10); // CE, CSN
const byte address[6] = "00001";

int joystickX1 = A0;
int joystickY1 = A1;
int joystickX2 = A3;
int joystickY2 = A2;

void setup() {
  Serial.begin(9600);

  radio.begin();
  radio.openWritingPipe(address);
  radio.setPALevel(RF24_PA_MIN);
  radio.stopListening(); // TX mode

  pinMode(joystickX1, INPUT);
  pinMode(joystickY1, INPUT);
  pinMode(joystickX2, INPUT);
  pinMode(joystickY2, INPUT);
}

void loop() {
  int xValue1 = analogRead(joystickX1);
  int yValue1 = analogRead(joystickY1);
  int xValue2 = analogRead(joystickX2);
  int yValue2 = analogRead(joystickY2);

  int data[4] = {xValue1, yValue1, xValue2, yValue2};

  radio.write(&data, sizeof(data));

  // Debug print
  Serial.print("TX -> ");
  Serial.print(xValue1); Serial.print(" ");
  Serial.print(yValue1); Serial.print(" ");
  Serial.print(xValue2); Serial.print(" ");
  Serial.println(yValue2);

  delay(100);
}