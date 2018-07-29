//伺服馬達Servo Motor(Tower Pro SG90)
//Servo預設脈衝寬度為544~2400µs
//Tower Pro SG90則為500~2400µs
#include<Servo.h>

Servo myservo;

void setup() {
    myservo.attach(9,500,2400);   
    //修正脈衝寬度
    //servo.attach(pin,min,max)
    myservo.write(90);
    //設定一開始位置
    delay(3000); 
}

//此採直接以脈衝寬度控制
//使用writeMicroseconds()要注意範圍不可超過,不然可能損壞馬達
void loop(){
    int i;
    for(i=500;i<=2400;i+=100){
        myservo.writeMicroseconds(i);
        delay(300);
    }
    for(i=2400;i>=500;i-=i){
        myservo.writeMicroseconds(i);
        delay(300);
    }
}
/*
一開始僅須設定腳位,不必修正脈衝寬度
再以角度控制馬達旋轉,但上限為180度
void loop() {
    int i;
    for(i=0;i<=180;i++){
      myservo.write(i);
      delay(25);
    }
    for(i=180;i>=0;i--){
      myservo.write(i);
      delay(25);
    }
}
*/
