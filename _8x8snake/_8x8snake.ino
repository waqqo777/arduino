#include <SoftwareSerial.h>
SoftwareSerial BTSerial(10,11);
//from pin2 to pin9 >>> from R1 to R8
//from pin12 to pin19 >>> from C1 to C8
//R>>>HIGH and C>>>LOW then LED lighten
int i=2,j=12,con=8,del=500,ran_i,ran_j,score=0,up=60,mat[8][8],result=0;
void reset();
void LED(int a,int b);
void DIRECTION(int x);
void ran();
void del_time();
void setup() 
{
  BTSerial.begin(9600);
  int count1,count2;
  for(count1=2;count1<10;count1++)
    pinMode(count1,OUTPUT);
  for(count2=12;count2<20;count2++)
    pinMode(count2,OUTPUT);
  reset();
  LED_on(i,j);
  delay(del);
  for(count1=0;count1<8;count1++)
  {
    for(count2=0;count2<8;count2++)
    {
      mat[count1][count2]=0;
    }
  }
  mat[0][0]=1;
}

void loop() {
  char input;
  /*if(ran_i==i&&ran_j==j)
  {
    ran();
    score++;
    Serial.print("Your score is ");
    Serial.println(score);
  }*/
  input=BTSerial.read();
  switch(input)
  {
    case '8':
      if(con!=2&&con!=8)
      {
        con=8;
        DIRECTION(con);
      }
      else
        DIRECTION(con);
      break;
    case '2':
      if(con!=8&&con!=2)
      {
        con=2;
        DIRECTION(con);
      }
      else
        DIRECTION(con);
      break;
    case '4':
      if(con!=6&&con!=4)
      {
        con=4;
        DIRECTION(con);
      }
      else
        DIRECTION(con);
      break;
    case '6':
      if(con!=4&&con!=6)
      {
        con=6;
        DIRECTION(con);
      }
      else
        DIRECTION(con);
      break;
    case '0':
      DIRECTION(con);
      break;
    case '1':
      del=100;
      break;
    case '3':
      del=300;
      break;
    case '5':
      del=500;
      break;
  }
}

void reset()
{
  int count;
  for(count=2;count<10;count++)
  {
    digitalWrite(count,LOW);
    digitalWrite(count+10,HIGH);
  }
}

void LED_on(int a,int b)
{
  reset();
  digitalWrite(a,HIGH);
  digitalWrite(b,LOW);
}

void DIRECTION(int x)
{
  int count1,count2,t=0;
  switch(x)
  {
    case 8:
      while(1)
      {
        t=0;
        j++;
        if(j>19)
          j-=8;
        else if(j<12)
          j+=8;
        LED_on(i,j);
        if(mat[i-2][j-12]==0)
          mat[i-2][j-12]=1;
        else if(mat[i-2][j-12]==1)
          mat[i-2][j-12]=0;
        for(count1=0;count1<8;count1++)
        {
          for(count2=0;count2<8;count2++)
          {
            if(mat[count1][count2]==1)
              t++;
            if(t==64)
            {
              result=1;
              BTSerial.print(result);
            }
          }
        }
        delay(del);
        //del_time();
        if(BTSerial.available()>0)
          break;
      }
      break;
    case 6:
      while(1)
      {
        t=0;
        i++;
        if(i>9)
          i-=8;
        else if(i<2)
          i+=8;
        LED_on(i,j);
        if(mat[i-2][j-12]==0)
          mat[i-2][j-12]=1;
        else if(mat[i-2][j-12]==1)
          mat[i-2][j-12]=0;
        for(count1=0;count1<8;count1++)
        {
          for(count2=0;count2<8;count2++)
          {
            if(mat[count1][count2]==1)
              t++;
            if(t==64)
            {
              result=1;
              BTSerial.print(result);
            }
          }
        }
        delay(del);
        //del_time();
        if(BTSerial.available()>0)
          break;
      }
      break;
    case 2:
      while(1)
      {
        t=0;
        j--;
        if(j>19)
          j-=8;
        else if(j<12)
          j+=8;
        LED_on(i,j);
        if(mat[i-2][j-12]==0)
          mat[i-2][j-12]=1;
        else if(mat[i-2][j-12]==1)
          mat[i-2][j-12]=0;
        for(count1=0;count1<8;count1++)
        {
          for(count2=0;count2<8;count2++)
          {
            if(mat[count1][count2]==1)
              t++;
            if(t==64)
            {
              result=1;
              BTSerial.print(result);
            }
          }
        }
        delay(del);
        //del_time();
        if(BTSerial.available()>0)
          break;
      }
      break;
    case 4:
      while(1)
      {
        t=0;
        i--;
        if(i>9)
          i-=8;
        else if(i<2)
          i+=8;
        LED_on(i,j);
        if(mat[i-2][j-12]==0)
          mat[i-2][j-12]=1;
        else if(mat[i-2][j-12]==1)
          mat[i-2][j-12]=0;
        for(count1=0;count1<8;count1++)
        {
          for(count2=0;count2<8;count2++)
          {
            if(mat[count1][count2]==1)
              t++;
            if(t==64)
            {
              result=1;
              BTSerial.print(result);
            }
          }
        }
        delay(del);
        //del_time();
        if(BTSerial.available()>0)
          break;
      }
      break;
  }
}

void ran()
{
  do
  {
    ran_i=random(2,9);
    ran_j=random(12,19);
  }while(ran_i==i||ran_j==j);
  LED_on(ran_i,ran_j);
}

/*void del_time()
{
  int ran=0;
  ran=random(1,up);
  if(ran==up-1&&del>50)
  {
    del-=50;
    up=30000/del;
  }
}*/

