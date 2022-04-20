/////////////////////////////////
//
//  11 avril 2022
//
////////////////////////////////

#include <Arduino.h>
#include <Wire.h>
#include <AFMotor.h>

AF_DCMotor motor1(1);

int motorDur   = 200;
int motorSpeed = 255;

unsigned long time;
bool motorActive = false;

void setup()
{
  Serial.begin(9600);

  Wire.begin(4);                // join i2c bus with address #4
  Wire.onReceive(receiveEvent); // register event
}

void loop()
{
  if (millis() - time > motorDur && motorActive) {
    motorActive = false;
    motor1.run(RELEASE);
  }
}


void receiveEvent(int howMany)
{
  if (2 <= Wire.available())
  {
    motorDur   = Wire.read() * 10;
    motorSpeed = Wire.read();

    Serial.print(motorDur);
    Serial.print(" ");
    Serial.println(motorSpeed);

    motor1.setSpeed(motorSpeed);
    motor1.run(FORWARD);
    
    motorActive = true;
    time = millis();
  }
}  