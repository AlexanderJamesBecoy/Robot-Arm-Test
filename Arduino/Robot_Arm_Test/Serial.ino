void SerialInit (void)
{
  Serial.begin(9600);
  Serial.println("Ready");
}

void SerialSetPWM (void)
{
  if (Serial.available())
  {
    Serial.print("Input: ");
    Serial.println(Serial.readString());
    String * outputs = ServoSetVal(Serial.readString());
  
    Serial.print("Output: Servo ");
    Serial.print(outputs[0]);
    Serial.print(" at pos ");
    Serial.println(outputs[1]);
  }
  delay(50);
}
