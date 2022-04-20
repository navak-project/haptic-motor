/////////////////////////////////
//
//  11 avril 2022
//
////////////////////////////////

#include <Arduino.h>
#include <Wire.h>
#include <AFMotor.h>

AF_DCMotor motor1(1, MOTOR12_64KHZ);

int motorDur   = 200;
int motorSpeed = 255;

bool queueRun = false;

void setup()
{
  Serial.begin(9600);

  Wire.begin(4);                // join i2c bus with address #4
  Wire.onReceive(receiveEvent); // register event
}

void loop()
{
  if (queueRun) {
    queueRun = false;

    motor1.setSpeed(motorSpeed);
    motor1.run(FORWARD);
    delay(motorDur);
    motor1.run(RELEASE);
  }
}


void receiveEvent(int howMany)
{
  if (2 <= Wire.available())
  {
    motorDur   = Wire.read() * 2;
    motorSpeed = Wire.read();

    Serial.print(motorDur);
    Serial.print(" ");
    Serial.println(motorSpeed);

    queueRun = true;
  }
}  