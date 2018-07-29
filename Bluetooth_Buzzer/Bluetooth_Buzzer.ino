#define DO 262
#define RE 294
#define MI 330
#define FA 349
#define SOL 392
#define LA 440
#define SI 494
#define DO5 523
#include <SoftwareSerial.h>
SoftwareSerial BTSerial(10,11);
bool ledState=true;
void setup() 
{
  pinMode(13,OUTPUT);
  pinMode(3,OUTPUT);
  pinMode(4,OUTPUT);
  BTSerial.begin(9600); // 注意預設藍芽通訊使用9600
}
void loop() 
{
  if(BTSerial.available())
  {
    char input=BTSerial.read();
    switch(input)
    {
      case '1': 
        tone(6,DO); 
        break;
      case '2': 
        tone(6,RE); 
        break;
      case '3': 
        tone(6,MI); 
        break;
      case '4': 
        tone(6,FA); 
        break;
      case '5': 
        tone(6,SOL); 
        break;
      case '6': 
        tone(6,LA); 
        break;
      case '7': 
        tone(6,SI); 
        break;
      case '8': 
        tone(6,DO5); 
        break; 
      case 'S': 
        noTone(6); 
        break; 
      case 'A':
        ledState=!ledState;
        digitalWrite(13,ledState);
        break;
    }
    /*if(input=='a')
    {
      digitalWrite(3,HIGH);
      delayMicroseconds(1000);
      digitalWrite(3,LOW);
      BTSerial.print(pulseIn(4,HIGH)/58);
    }*/
  }
}
