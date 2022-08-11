#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>

void setup() {
  // put your setup code here, to run once:
  ServoInit();
  SerialInit();
}

void loop() {
  // put your main code here, to run repeatedly:
  SerialSetPWM();
  ServoRun();
  delay(100);
}
