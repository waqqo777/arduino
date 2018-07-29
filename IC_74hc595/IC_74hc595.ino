//74hc595

//MSBFIRST(most significant bit first)
//最先輸出的會是number（是個uint8_t，有8個bits，第7個bit是MSB，第0個bit是LSB）的第7個bit
//LSBFIRST(least significant bit first)，那麼最先輸出的會是第0個bit

//ic腳位介紹
//Pin 1~7（Q1~Q7）、Pin 15（Q0）依序接到8個LED
//Pin 8（GND），接地
//Pin 9（Q7" ），用於串聯多個74hc595 
//Pin 10（MR） ，此不使用此功能，所以接到5V
//Pin 11（SH_CP），clockpin
//Pin 12（ST_CP），latchpin
//Pin 13（OE），此不使用此功能，所以接地
//Pin 14（DS），datapin
//Pin 16（Vcc） ，接5V

//參考 http://yehnan.blogspot.tw/2012/02/arduino_19.html
//參考 https://www.youtube.com/watch?v=jGeAw5_8VJo

#define latchPin 6  //ic pin12(SH_CP)
#define clockPin 5  //ic pin11(ST_CP)
#define dataPin 7  //ic pin14(DS)
//以下為2顆74hc595相關接法
//第一顆74hc595的pin9接至第二顆74hc595的pin14(即dataPin)
//第二顆74hc595的clockpin和latchpin接至第一顆的相同位置
//三顆以上以此類推

void setup() {
  Serial.begin(9600);
  pinMode(latchPin, OUTPUT);
  pinMode(clockPin, OUTPUT);
  pinMode(dataPin, OUTPUT);
}
void loop() {
  uint16_t number;
  uint8_t highbyte;  //第二顆
  uint8_t lowbyte;  //第一顆
  for (int i = 0; i < 16; i++) {
    // 送出資料前，將LatchPin設為LOW，鎖定輸出的資料。
    digitalWrite(latchPin, LOW);

    number = 0;  // 所有bit清為0，代表全部LED都不亮。
    bitSet(number, i);   // 十進位轉二進位

    highbyte = (number >> 8) & 0xFF;
    lowbyte = number & 0xFF;
    //(highbyte,lowbyte)=
    //(0,1)(0,2)(0,4)(0,8)(0,16)(0,32)(0,64)(0,128)
    //(1,0)(2,0)(4,0)(8,0)(16,0)(32,0)(64,0)(128,0)
    /*Serial.println(highbyte);
    Serial.println(lowbyte);
    Serial.println("-");*/
    
    // 利用shiftOut()送出資料
    // 僅一顆 -> shiftOut(dataPin, clockPin, MSBFIRST, number); 
    shiftOut(dataPin, clockPin, MSBFIRST, highbyte);
    shiftOut(dataPin, clockPin, MSBFIRST, lowbyte);
    //若改為LSBFIRST則顛倒
    //shiftOut()一次只能輸出8 bits的資料
    
    // 送出資料結束，將LatchPin設為HIGH，更新輸出腳位。 
    digitalWrite(latchPin, HIGH);
    delay(500);
  }
}

