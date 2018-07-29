#define trigpin 3
#define echopin 4
#define button 11
#define led 8
int distance();

void setup() {
    pinMode(trigpin,OUTPUT);
    pinMode(echopin,INPUT);
    pinMode(button,INPUT_PULLUP);
    pinMode(led,OUTPUT);
}

void loop() {
    int dist;
    dist=distance();
    boolean butt=digitalRead(button);
    if(!butt){
      if(dist<50){
        //buzzer on
        digitalWrite(led,HIGH);
        delay(500);
      }
      else{
        //buzzer off
        digitalWrite(led,LOW);
        delay(500);
      }
    }
    else{
      //buzzer off
      digitalWrite(led,LOW);
    }
}

int distance(){
  float time;
  float dist;
  digitalWrite(trigpin,HIGH); 
  delayMicroseconds(10);
  digitalWrite(trigpin,LOW);
  time=pulseIn(echopin,HIGH);
  return time/58.82;
}

