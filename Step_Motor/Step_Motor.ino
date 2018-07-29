//步進馬達Step Motor(28BYJ-48 5V DC)
//參考http://www.codedata.com.tw/social-coding/mblock-arduino-16-stepper/


#include<Stepper.h>
//步進馬達所需函式庫

#define STEPS 2048
//28BYJ-48的步進角為(5.625/64)度,所以一圈所需步數為360/(5.625/64)=4096步
//但由於使用<Stepper.h>這個函式庫,所以必須設為2048,條件是速度不能設太快

Stepper mystepper(STEPS,8,10,9,11);
//Stepper(int steps,pin1,pin2,pin3,pin4)
//steps:一圈所需步數 ex.steps=100,一步等於3.6度,轉一圈需100步
//如果28BYJ-48的接線順序由IN1,IN2,IN3,IN4分別接至8,9,10,11將導致馬達只有一個轉向
//Sol_1:將Arduino上9,10接線對調
//Sol_2:建立Stepper時9與10互調(此採用Sol_2)

void setup() 
{
      mystepper.setSpeed(10);
      //設定馬達每分鐘轉幾圈(>0),太大可能會趕不上
}

void loop()
{
      mystepper.step(1024);   //正半圈
      delay(1000);
      mystepper.step(-1024);  //反半圈
      delay(1000);
      mystepper.step(2048);   //正一圈
      delay(1000);
      mystepper.step(-2048);  //反一圈
      delay(1000);
      mystepper.step(6144);   //正三圈
      delay(1000);
      mystepper.step(-6144);  //反三圈
      delay(1000);
}
