#include <SoftwareSerial.h>
SoftwareSerial BTSerial(10, 11); // Arduino的RX | TX
void setup() 
{
  pinMode(9, OUTPUT);
  digitalWrite(9, HIGH); //給EN高電位,進AT模式
  Serial.begin(9600);
  Serial.println("Enter AT commands:");
  BTSerial.begin(38400); //AT模式使用38400鮑率
}

void loop() 
{
  if (BTSerial.available())
    Serial.write(BTSerial.read()); // HC05到電腦
  if (Serial.available())
    BTSerial.write(Serial.read()); // 電腦到HC05
}
