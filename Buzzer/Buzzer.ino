//蜂鳴器buzzer
//各音階的頻率已經定義在<pitches.h>
//參考https://github.com/programmermagazine/201306/blob/master/source/article1.md
//tone(腳位,頻率,持續時間);
//tone(腳位,頻率?);  >>>???
//noTone(腳位);  >>>???

//#include<pitches.h>
void setup() {
    pinMode(8,OUTPUT);
}

//手機鈴聲
void loop() {
    for(int i=0;i<10;i++){
        tone(8,1000);
        delay(50);
        tone(8,500);
        delay(50);
    }
    noTone(8);
    delay(2000);
}

