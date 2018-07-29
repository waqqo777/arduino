const int c1=2;
const int c2=3;
const int c3=4;
const int c4=5;
const int c5=6;
const int c6=7;
const int c7=8;
const int c8=9;
const int r1=10;
const int r2=11;
const int r3=12;
const int r4=13;
const int r5=14;
const int r6=15;
const int r7=16;
const int r8=17;
void setup() 
{
  int i;
  for(i=2;i<18;i++)
  {
    pinMode(i,OUTPUT);
  }
}

void loop() 
{
  int i,j;
  reset();
  for(i=2;i<10;i++)
  {
    for(j=10;j<18;j++)
    {
      digitalWrite(i,LOW);
      digitalWrite(j,HIGH);
      delay(150);
      reset();
    }
  }
}

void reset()
{
  int i;
  for(i=2;i<10;i++)
  {
    digitalWrite(i,HIGH);
    digitalWrite(i+8,LOW);
  }
}

