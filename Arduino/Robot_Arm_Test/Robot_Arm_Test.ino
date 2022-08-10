#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>

// Define MG669R servo specs
#define SERVOMIN  340  // This is the 'minimum' pulse length count (out of 4096)
#define SERVOMAX  2505 // This is the 'maximum' pulse length count (out of 4096)
#define USMIN  600 // This is the rounded 'minimum' microsecond length based on the minimum pulse of 150
#define USMAX  2400 // This is the rounded 'maximum' microsecond length based on the maximum pulse of 600
#define SERVO_FREQ 50 // Analog servos run at ~50 Hz updates

#define VALUEMAX 255
#define VALUEMIN 0

int SERVOMID = (SERVOMAX - SERVOMIN) / 2;

//int servo_num[] = {8, 9};
//int servo_val[] = {0, 0};

Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();

void setPWM(String command);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);

  pwm.begin();
  pwm.setOscillatorFrequency(27000000);
  pwm.setPWMFreq(SERVO_FREQ);
  pwm.writeMicroseconds(8, SERVOMID);
  pwm.writeMicroseconds(9, SERVOMID);
  pwm.writeMicroseconds(10, SERVOMID);
  pwm.writeMicroseconds(11, SERVOMIN);
  pwm.writeMicroseconds(12, SERVOMIN);
  pwm.writeMicroseconds(13, SERVOMID);

  Serial.println("Ready");
}

void loop() {
  // put your main code here, to run repeatedly:
  if (Serial.available())
  {
//    value = Serial.parseInt();
//    int step = map(value, VALUEMIN, VALUEMAX, SERVOMIN, SERVOMAX);
//    Serial.print(value);
//    Serial.print(", ");
//    Serial.println(step);
//    pwm.writeMicroseconds(8, step);
      SetPWM(Serial.readString());
  }
  delay(100);
}

void SetPWM(String command)
{
//  Serial.print("Input: ");
//  Serial.println(string);
//  int index = string.lastIndexOf(",");
//  String str_servo_num = string.substring(0, index);
//  String str_value = string.substring(index+1, string.length());
//  int servo_num = str_servo_num.toInt();
//  int value = str_value.toInt();
//  Serial.print("Output: ");
//  Serial.print(servo_num);
//  Serial.print(", ");
//  Serial.println(value);

  Serial.print("Input: ");
  Serial.println(command);
  int index = command.lastIndexOf(",");
  String str_servo_num = command.substring(0, index);
  String str_servo_val = command.substring(index + 1, command.length());
  int servo_num = str_servo_num.toInt();
  int servo_val = map(str_servo_val.toInt(), VALUEMIN, VALUEMAX, SERVOMIN, SERVOMAX);

  Serial.print("Output: Servo ");
  Serial.print(servo_num);
  Serial.print(" at pos ");
  Serial.println(servo_val);

  pwm.writeMicroseconds(servo_num, servo_val);
}
