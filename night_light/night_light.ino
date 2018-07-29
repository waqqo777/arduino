#include <SoftwareSerial.h>
SoftwareSerial BTSerial(13,12);
const int light=A0;
const int green=6;
const int red=3;
const int blue=5;
const int trigpin=7;
const int echopin=8;
//燈條上藍綠顛倒

void setup() {
  Serial.begin(9600);
  BTSerial.begin(9600);
  for(int i=3;i<8;i++)
    pinMode(i,OUTPUT);
  pinMode(8,INPUT);
  pinMode(A0,INPUT);
  DARK();
}

void loop() {
  /*while(1)
  {
    ULTRASONIC();
  }*/
  int i,tmp=104;
  while(i=BTSerial.read())
  {
    if(i==104)
      tmp=i;
    else if(i==107)
      tmp=i;
    else if(i==108)
      tmp=i;
    if(tmp==104)
    {
      switch(i)
      {
        case 97:
        GREEN();
        break;
        case 98:
        RED();
        break;
        case 99:
        BLUE();
        break;
        case 100:
        YELLOW();
        break;
        case 101:
        BLUEGREEN();
        break;
        case 102:
        WHITE();
        break;
        case 103:
        DARK();
        break;
      }
    }
    else if(tmp==107)
    {
      switch(i)
      {
        case 97:
        GREEN_(2000,2);
        break;
        case 98:
        RED_(2000,2);
        break;
        case 99:
        BLUE_(2000,2);
        break;
        case 100:
        YELLOW_(2000,2);
        break;
        case 101:
        BLUEGREEN_(2000,2);
        break;
        case 102:
        WHITE_(2000,2);
        break;
        case 103:
        DARK();
        break;
      }
    }
    else if(tmp==108)
    {
      switch(i)
      {
        case 97:
        GREEN_(2000,1);
        break;
        case 98:
        RED_(2000,1);
        break;
        case 99:
        BLUE_(2000,1);
        break;
        case 100:
        YELLOW_(2000,1);
        break;
        case 101:
        BLUEGREEN_(2000,1);
        break;
        case 102:
        WHITE_(2000,1);
        break;
        case 103:
        DARK();
        break;
      }
    }
    if(i==105)
    {
      while(1)
      {
        ULTRASONIC();
        delay(200);
        if(BTSerial.available()>0)
          break;
      }
    }
    else if(i==106)
    {
      while(1)
      {
        LIGHT();
        delay(200);
        if(BTSerial.available()>0)
          break;
      }
    }
  }
}

void GREEN()
{
  digitalWrite(green,LOW);
  digitalWrite(red,HIGH);
  digitalWrite(blue,HIGH);
}

void RED()
{
  digitalWrite(green,HIGH);
  digitalWrite(red,LOW);
  digitalWrite(blue,HIGH);
}

void BLUE()
{
  digitalWrite(green,HIGH);
  digitalWrite(red,HIGH);
  digitalWrite(blue,LOW);
}

void YELLOW()
{
  digitalWrite(green,LOW);
  digitalWrite(red,LOW);
  digitalWrite(blue,HIGH);
}

void PURPLE()
{
  digitalWrite(green,HIGH);
  digitalWrite(red,LOW);
  digitalWrite(blue,LOW);
}

void BLUEGREEN()
{
  digitalWrite(green,LOW);
  digitalWrite(red,HIGH);
  digitalWrite(blue,LOW);
}

void WHITE()
{
  digitalWrite(green,LOW);
  digitalWrite(red,LOW);
  digitalWrite(blue,LOW);
}

void DARK()
{
  digitalWrite(green,HIGH);
  digitalWrite(red,HIGH);
  digitalWrite(blue,HIGH);
}

void GREEN_(int t,int m)
{
  //t=delay time
  //m=1>>漸暗
  //m=2>>漸亮
  if(m==1)
  {
    for(int i=0;i<256;i++)
    {
      analogWrite(green,i);
      analogWrite(red,255);
      analogWrite(blue,255);
      delay(t/256);
    }
  }
  else if(m==2)
  {
    for(int i=255;i>=0;i--)
    {
      analogWrite(green,i);
      analogWrite(red,255);
      analogWrite(blue,255);
      delay(t/256);
    }
  }
}

void RED_(int t,int m)
{
  //t=delay time
  //m=1>>漸暗
  //m=2>>漸亮
  if(m==1)
  {
    for(int i=0;i<256;i++)
    {
      analogWrite(green,255);
      analogWrite(red,i);
      analogWrite(blue,255);
      delay(t/256);
    }
  }
  else if(m==2)
  {
    for(int i=255;i>=0;i--)
    {
      analogWrite(green,255);
      analogWrite(red,i);
      analogWrite(blue,255);
      delay(t/256);
    }
  }
}

void BLUE_(int t,int m)
{
  //t=delay time
  //m=1>>漸暗
  //m=2>>漸亮
  if(m==1)
  {
    for(int i=0;i<256;i++)
    {
      analogWrite(green,255);
      analogWrite(red,255);
      analogWrite(blue,i);
      delay(t/256);
    }
  }
  else if(m==2)
  {
    for(int i=255;i>=0;i--)
    {
      analogWrite(green,255);
      analogWrite(red,255);
      analogWrite(blue,i);
      delay(t/256);
    }
  }
}

void YELLOW_(int t,int m)
{
  //t=delay time
  //m=1>>漸暗
  //m=2>>漸亮
  if(m==1)
  {
    for(int i=0;i<256;i++)
    {
      analogWrite(green,i);
      analogWrite(red,i);
      analogWrite(blue,255);
      delay(t/256);
    }
  }
  else if(m==2)
  {
    for(int i=255;i>=0;i--)
    {
      analogWrite(green,i);
      analogWrite(red,i);
      analogWrite(blue,255);
      delay(t/256);
    }
  }
}

void PURPLE_(int t,int m)
{
  //t=delay time
  //m=1>>漸暗
  //m=2>>漸亮
  if(m==1)
  {
    for(int i=0;i<256;i++)
    {
      analogWrite(green,255);
      analogWrite(red,i);
      analogWrite(blue,i);
      delay(t/256);
    }
  }
  else if(m==2)
  {
    for(int i=255;i>=0;i--)
    {
      analogWrite(green,255);
      analogWrite(red,i);
      analogWrite(blue,i);
      delay(t/256);
    }
  }
}

void BLUEGREEN_(int t,int m)
{
  //t=delay time
  //m=1>>漸暗
  //m=2>>漸亮
  if(m==1)
  {
    for(int i=0;i<256;i++)
    {
      analogWrite(green,i);
      analogWrite(red,255);
      analogWrite(blue,i);
      delay(t/256);
    }
  }
  else if(m==2)
  {
    for(int i=255;i>=0;i--)
    {
      analogWrite(green,i);
      analogWrite(red,255);
      analogWrite(blue,i);
      delay(t/256);
    }
  }
}

void WHITE_(int t,int m)
{
  //t=delay time
  //m=1>>漸暗
  //m=2>>漸亮
  if(m==1)
  {
    for(int i=0;i<256;i++)
    {
      analogWrite(green,i);
      analogWrite(red,i);
      analogWrite(blue,i);
      delay(t/256);
    }
  }
  else if(m==2)
  {
    for(int i=255;i>=0;i--)
    {
      analogWrite(green,i);
      analogWrite(red,i);
      analogWrite(blue,i);
      delay(t/256);
    }
  }
}

void RANDOM()
{
    int i;
    i=random(1,7);
    Serial.println(i);
    switch(i)
    {
      case 1:
      GREEN();
      delay(1000);
      break;
      case 2:
      RED();
      delay(1000);
      break;
      case 3:
      BLUE();
      delay(1000);
      break;
      case 4:
      YELLOW();
      delay(1000);
      break;
      case 5:
      BLUEGREEN();
      delay(1000);
      break;
      case 6:
      WHITE();
      delay(1000);
      break;
    }
}

void ULTRASONIC()
{
  int dist;
  dist=distance();
  analogWrite(red,dist*4);
  analogWrite(green,255);
  analogWrite(blue,255);
  delay(20);
  /*analogWrite(green,dist/4);
  analogWrite(red,255);
  analogWrite(blue,255);
  delay(100);
  analogWrite(blue,dist/4);
  analogWrite(red,255);
  analogWrite(green,255);
  delay(100);*/
  Serial.println(dist);
  BTSerial.println(dist);  
  delay(20);
}

void LIGHT()
{
  int i=0;
  i=analogRead(light);
  Serial.println(i);
  BTSerial.println(i);
  analogWrite(red,i/2);
}

int distance()
{
  float time;
  float dist;
  digitalWrite(trigpin,HIGH); delayMicroseconds(10);
  digitalWrite(trigpin,LOW);
  time=pulseIn(echopin,HIGH);
  return time/58.82;  //一秒鐘約0.034m=1/29.41，來回再/2
}
