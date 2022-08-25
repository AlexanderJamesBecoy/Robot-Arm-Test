#define NO_OF_SERVOS 5
#define VALUEMAX 180
#define VALUEMIN 0

// Define MG669R servo specs
#define SERVOMIN  340                         // This is the 'minimum' pulse length count (out of 4096)
#define SERVOMAX  2505                        // This is the 'maximum' pulse length count (out of 4096)
#define SERVOMID (SERVOMAX + SERVOMIN) / 2    // This is the 'average' pulse length count (out of 4096)
#define USMIN  600                            // This is the rounded 'minimum' microsecond length based on the minimum pulse of 150
#define USMAX  2400                           // This is the rounded 'maximum' microsecond length based on the maximum pulse of 600
#define SERVO_FREQ 50                         // Analog servos run at ~50 Hz updates

int servo_nums[NO_OF_SERVOS];
int servo_vals[NO_OF_SERVOS];

Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();

void ServoInit (void)
{
  pwm.begin();
  pwm.setOscillatorFrequency(27000000);
  pwm.setPWMFreq(SERVO_FREQ);
  
  pwm.writeMicroseconds(8, SERVOMID);
  pwm.writeMicroseconds(9, SERVOMID);
  pwm.writeMicroseconds(10, SERVOMID);
  pwm.writeMicroseconds(11, SERVOMIN);
  pwm.writeMicroseconds(12, SERVOMIN);
  pwm.writeMicroseconds(13, SERVOMID);
}

void ServoRun(void)
{
  for (int i = 0; i < NO_OF_SERVOS; i++)
  {
    pwm.writeMicroseconds(servo_nums[i], servo_vals[i]);
  }
}

String * ServoSetVal (String command)
{
  static String * outputs = new String[2];
  outputs[0] = outputs[1] = -1;
  
  int index = command.lastIndexOf(",");
  String str_servo_num = command.substring(0, index);
  String str_servo_val = command.substring(index + 1, command.length());
  int servo_num = str_servo_num.toInt();
  int servo_val = map(str_servo_val.toInt(), VALUEMIN, VALUEMAX, SERVOMIN, SERVOMAX);

  int servo_index = -1;
  for (int i = 0; i < NO_OF_SERVOS; i++)
  {
    if (servo_nums[i] == servo_num) servo_index = i;
  }
  if (servo_index == -1) return outputs;
  servo_vals[servo_index] = servo_val;

  outputs[0] = servo_num;
  outputs[1] = servo_val;
  return outputs;
}
