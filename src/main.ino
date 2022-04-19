/////////////////////////////////
//
//  11 avril 2022
//
////////////////////////////////

#include <Arduino.h>
#include <Wire.h>
#include <AFMotor.h>

AF_DCMotor motor1(1);
AF_DCMotor motor2(2);
AF_DCMotor motor3(3);
AF_DCMotor motor4(4);

int motorDur   = 200;
int motorSpeed = 255;

void setup()
{
  Wire.begin(4);                // join i2c bus with address #4
  Wire.onReceive(receiveEvent); // register event
}

void loop()
{
  
}


void receiveEvent(int howMany)
{
  if (2 <= Wire.available()) 
  {
    motorDur   = Wire.read() * 10;
    motorSpeed = Wire.read();

    motor1.setSpeed(motorSpeed);
    motor1.run(FORWARD);
    motor2.setSpeed(motorSpeed);
    motor2.run(FORWARD);
    motor3.setSpeed(motorSpeed);
    motor3.run(FORWARD);
    motor4.setSpeed(motorSpeed);
    motor4.run(FORWARD);
    
    delay(motorDur);
    
    motor1.run(RELEASE);
    motor2.run(RELEASE);
    motor3.run(RELEASE);
    motor4.run(RELEASE);
  }
}  