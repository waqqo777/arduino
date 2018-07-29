//超聲波感測器Ultrasonic Sensor
#define trigpin 7
#define echopin 8
int distance();

void setup() {
    Serial.begin(9600);
    pinMode(trigpin,OUTPUT);
    pinMode(echopin,INPUT);
}

void loop() {
    int dist=0;
    dist=distance();
    Serial.println(dist);
    if(dist<20){
      //Serial.println("RED");
      delay(100);
    }
    else if(20<=dist&&dist<50){
      //Serial.println("YELLOW");
      delay(100);
    }
    else{
      //Serial.println("GREEN");
      delay(100);
    }  
}

int distance(){
  float time;
  float dist;
  digitalWrite(trigpin,HIGH); delayMicroseconds(10);
  digitalWrite(trigpin,LOW);
  time=pulseIn(echopin,HIGH);
  return time/58.82;  //一秒鐘約0.034m=1/29.41，來回再/2
}

