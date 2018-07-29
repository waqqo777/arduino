#include <SoftwareSerial.h>
SoftwareSerial BTSerial(5,6);
const int green=9;
const int red=10;
const int blue=11;
//燈條上藍綠顛倒

void setup() {
  Serial.begin(9600);
  BTSerial.begin(9600);
  for(int i=9;i<12;i++)
    pinMode(i,OUTPUT);
}

void loop() {
  GREEN();
  delay(500);
  RED();
  delay(500);
  BLUE();
  delay(500);
  YELLOW();
  delay(500);
  BLUEGREEN();
  delay(500);
  WHITE();
  delay(500);
  DARK();
  delay(500);
  
  GREEN_(2,1);
  RED_(2,1);
  BLUE_(2,1);
  YELLOW_(2,1);
  BLUEGREEN_(2,1);
  WHITE_(2,1);
  GREEN_(2,2);
  RED_(2,2);
  BLUE_(2,2);
  YELLOW_(2,2);
  BLUEGREEN_(2,2);
  WHITE_(2,2);
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

