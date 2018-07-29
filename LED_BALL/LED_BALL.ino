//p -> positive
//n -> negative

/////正面朝上/////
//--p1--p2--n1--//  
//-arduino_nano-//  
/////焊點朝下/////

////////////////O
// p1_0 | p2_6 //
// p1_1 | p2_7 //
// p1_2 | n1_0 //
// p1_3 | n1_1 //
// p1_4 | n1_2 //
// p1_5 | n1_3 //
// p1_6 | n1_4 //
// p1_7 | n1_5 //
// p2_0 | n1_6 //
// p2_1 | n1_7 //
// p2_2 | n8   //
// p2_3 | n9   // 
// p2_4 | n10  //
// p2_5 | n11  //
/////////////////

//ball
//上到下 -> p1_0 ~ p1_7 ~ p2_0 ~ p2_7
//以上到下那條為基準往左繞一圈  -> n1_0 ~ n1_7 ~ n8 ~ n11

#define latch_p 12
#define clock_p 11
#define data_p 10
//74hc595 negative -> 1~8
#define latch_n 8
#define clock_n 7
#define data_n 9
#define n8 6
#define n9 5
#define n10 4
#define n11 3
//delay
#define ddtick  __asm__("nop\n\t"); 
#define dd4tick  __asm__("nop\n\t""nop\n\t""nop\n\t""nop\n\t"); 
// the Macro dd4tick will delay 0.25us exactly on 16MHz Arduino
#define delayOneUs()  { dd4tick; dd4tick; dd4tick; dd4tick; }

void setup() {
  Serial.begin(9600);
  for(int i=3;i<13;i++)
    pinMode(i,OUTPUT);
}

//set
void latch_set(int);  //0 -> LOW, 1 -> HIGH
void p_set(int,int);  //a -> up, b -> down
void n_set(int,int);  //a -> n0~n7, b -> n8~n11
void set(int,int,int,int);  //totally control
void dark(int);  //dark delay how long
void bright(int); //bright delay how long
//first int t -> run how many times
void mode_a(int,int);  //alternating, 0 -> no twinkling, 1 -> twinkling
void mode_b(int,int);  //0 -> counterclockwise, 1 -> clockwise, 2 -> both (up to down)
void mode_c(int);  //lighten all LED in order
void mode_d(int,int);  //two circles 0 -> dark, 1 -> lighten
void mode_e(int);  //around
void mode_f(int,int);  //0 -> top to bottom, 1 -> top to bottom to top
void mode_g(int);  //random
void mode_h(int,int);  //grid 0~2
void mode_i(int);  //random and run around
void mode_j(int,int);  //0 -> cram all LED in order from bottom to top, 1 -> distinguish all LED in order from top to bottom
void mode_k(int,int);  //0 -> cram all LED in clockwise, 1 -> distinguish all LED in counterclockwise
void mode_l(int,int);  //randomly to run around (fail)
//
void mode_random();  //run a mode at random

void loop() {
  int i;
  mode_c(1);
  mode_k(1,1);
  mode_e(4);
  mode_k(1,0);
  mode_a(6,0);
  mode_a(3,1);
  mode_h(5,0);
  mode_b(4,0);
  mode_b(4,1);
  mode_b(5,2);
  for(i=0;i<3;i++)
  {
    mode_h(1,1);
    mode_h(1,2);
  }
  mode_i(1);
  mode_g(4);
  mode_j(1,1);
  mode_d(6,1);
  mode_f(1,0);
  mode_j(1,0);
  mode_f(1,1);
  mode_f(1,0);
  mode_j(1,0);
  mode_d(4,0);
  for(i=0;i<3;i++)
  {
    mode_f(1,1);
    mode_f(1,0);
  }
  mode_l(1);
 
  //while(1)
  //  mode_random();
}

void latch_set(int state)
{
  if(state==0)
  {
      digitalWrite(latch_p,LOW);
      digitalWrite(latch_n,LOW);
  }
  else if(state==1)
  {
      digitalWrite(latch_p,HIGH);
      digitalWrite(latch_n,HIGH);  
  }
}

void p_set(int a,int b)
{
  shiftOut(data_p,clock_p,MSBFIRST,b);
  shiftOut(data_p,clock_p,MSBFIRST,a);
}

void n_set(int a,int b)
{
  shiftOut(data_n,clock_n,MSBFIRST,a);
  if(b/8<1)
    digitalWrite(n8,LOW);
  else
    digitalWrite(n8,HIGH);
  if((b/4)%2==0)
    digitalWrite(n9,LOW);
  else
    digitalWrite(n9,HIGH);
  if((b/2)%2==0)
    digitalWrite(n10,LOW);
  else
    digitalWrite(n10,HIGH);
  if(b%2==0)
    digitalWrite(n11,LOW);
  else
    digitalWrite(n11,HIGH);
  /*  8  9 10 11
   0  0  0  0  0
   1  0  0  0  1
   2  0  0  1  0
   3  0  0  1  1
   .  .  .  .  .
  14  1  1  1  0
  15  1  1  1  1
 */
}

void set(int p_up,int p_down,int n_front,int n_back)
{
  //p_up -> 正極上半球(0~255)
  //p_down -> 正極下半球(0~255)
  //n_front -> n0~n7(0~255)
  //n_back -> n8~n11(0~15)
  latch_set(0);
  p_set(p_up,p_down);
  n_set(n_front,n_back);
  latch_set(1);
}

void dark(int t)
{
  set(0,0,255,15);
  delay(t);
}

void bright(int t)
{
  set(255,255,0,0);
  delay(t);
}

void mode_a(int t,int mode)
{
  int i,j,j_tmp,del;
  if(mode==0)
  {
    j_tmp=80;
    del=1;
  }
  else if(mode==1)
  {
    j_tmp=6;
    del=20;
  }
  for(i=0;i<t;i++)
  {
    for(j=0;j<j_tmp;j++)
    {
      set(85,85,85,10);
      delay(del);
      set(170,170,170,5);
      delay(del);
    }
    for(j=0;j<j_tmp;j++)
    {
      set(170,170,85,10);
      delay(del);
      set(85,85,170,5);
      delay(del);
    }
  }
}

void mode_b(int t,int mode)
{
  int i=0,j,p1,p2,cnt=0;
  for(j=0;j<t;j++)
  {
    for(i=0;i<24;i+=2)
    {
      for(cnt=0;cnt<5;cnt++)
      {
        p1=pow(2,i%24)+pow(2,(i+1)%24)+0.5;
        if(p1>255||p1<1)
          p1=0;
        p2=pow(2,(i-8)%24)+pow(2,(i-7)%24)+0.5;
        if(p2>255||p2<1)
          p2=0;
        if(mode==0||mode==2)
        {
          set(p1,p2,254,15);
          delayMicroseconds(1);
        }
        if(mode==1||mode==2)
        {
          set(p1,p2,255,14);
          delayMicroseconds(1);
        }
        p1=pow(2,(i+2)%24)+pow(2,(i+3)%24)+0.5;
        if(p1>255||p1<1)
          p1=0;
        p2=pow(2,(i-6)%24)+pow(2,(i-5)%24)+0.5;
        if(p2>255||p2<1)
          p2=0;
        if(mode==0||mode==2)
        {
          set(p1,p2,253,15);
          delayMicroseconds(1);
        }
        if(mode==1||mode==2)
        {
          set(p1,p2,255,13);
          delayMicroseconds(1);
        }
        p1=pow(2,(i+4)%24)+pow(2,(i+5)%24)+0.5;
        if(p1>255||p1<1)
          p1=0;
        p2=pow(2,(i-4)%24)+pow(2,(i-3)%24)+0.5;
        if(p2>255||p2<1)
          p2=0;
        if(mode==0||mode==2)
        {
          set(p1,p2,251,15);
          delayMicroseconds(1);
        }
        if(mode==1||mode==2)
        {
          set(p1,p2,255,11);
          delayMicroseconds(1);
        }
        p1=pow(2,(i+6)%24)+pow(2,(i+7)%24)+0.5;
        if(p1>255||p1<1)
          p1=0;
        p2=pow(2,(i-2)%24)+pow(2,(i-1)%24)+0.5;
        if(p2>255||p2<1)
          p2=0;
        if(mode==0||mode==2)
        {
          set(p1,p2,247,15);
          delayMicroseconds(1);
        }
        if(mode==1||mode==2)
        {
          set(p1,p2,255,7);
          delayMicroseconds(1);
        }
        p1=pow(2,(i+8)%24)+pow(2,(i+9)%24)+0.5;
        if(p1>255||p1<1)
          p1=0;
        p2=pow(2,i%24)+pow(2,(i+1)%24)+0.5;
        if(p2>255||p2<1)
          p2=0;
        if(mode==0||mode==2)
        {
          set(p1,p2,239,15);
          delayMicroseconds(1);
        }
        if(mode==1||mode==2)
        {
          set(p1,p2,127,15);
          delayMicroseconds(1);
        }
        p1=pow(2,(i+10)%24)+pow(2,(i+11)%24)+0.5;
        if(p1>255||p1<1)
          p1=0;
        p2=pow(2,(i+2)%24)+pow(2,(i+3)%24)+0.5;
        if(p2>255||p2<1)
          p2=0;
        if(mode==0||mode==2)
        {
          set(p1,p2,223,15);
          delayMicroseconds(1);
        }
        if(mode==1||mode==2)
        {
          set(p1,p2,191,15);
          delayMicroseconds(1);
        }
        p1=pow(2,(i+12)%24)+pow(2,(i+13)%24)+0.5;
        if(p1>255||p1<1)
          p1=0;
        p2=pow(2,(i+4)%24)+pow(2,(i+5)%24)+0.5;
        if(p2>255||p2<1)
          p2=0;
        if(mode==0||mode==2)
        {
          set(p1,p2,191,15);
          delayMicroseconds(1);
        }
        if(mode==1||mode==2)
        {
          set(p1,p2,223,15);
          delayMicroseconds(1);
        }
        p1=pow(2,(i+14)%24)+pow(2,(i+15)%24)+0.5;
        if(p1>255||p1<1)
          p1=0;
        p2=pow(2,(i+6)%24)+pow(2,(i+7)%24)+0.5;
        if(p2>255||p2<1)
          p2=0;
        if(mode==0||mode==2)
        {
          set(p1,p2,127,15);
          delayMicroseconds(1);
        }
        if(mode==1||mode==2)
        {
          set(p1,p2,239,15);
          delayMicroseconds(1);
        }
        p1=pow(2,(i+16)%24)+pow(2,(i+17)%24)+0.5;
        if(p1>255||p1<1)
          p1=0;
        p2=pow(2,(i+8)%24)+pow(2,(i+9)%24)+0.5;
        if(p2>255||p2<1)
          p2=0;
        if(mode==0||mode==2)
        {
          set(p1,p2,255,7);
          delayMicroseconds(1);
        }
        if(mode==1||mode==2)
        {
          set(p1,p2,247,15);
          delayMicroseconds(1);
        }
        p1=pow(2,(i+18)%24)+pow(2,(i+19)%24)+0.5;
        if(p1>255||p1<1)
          p1=0;
        p2=pow(2,(i+10)%24)+pow(2,(i+11)%24)+0.5;
        if(p2>255||p2<1)
          p2=0;
        if(mode==0||mode==2)
        {
          set(p1,p2,255,11);
          delayMicroseconds(1);
        }
        if(mode==1||mode==2)
        {
          set(p1,p2,251,15);
          delayMicroseconds(1);
        }
        p1=pow(2,(i+20)%24)+pow(2,(i+21)%24)+0.5;
        if(p1>255||p1<1)
          p1=0;
        p2=pow(2,(i+12)%24)+pow(2,(i+13)%24)+0.5;
        if(p2>255||p2<1)
          p2=0;
        if(mode==0||mode==2)
        {
          set(p1,p2,255,13);
          delayMicroseconds(1);
        }
        if(mode==1||mode==2)
        {
          set(p1,p2,253,15);
          delayMicroseconds(1);
        }
        p1=pow(2,(i+22)%24)+pow(2,(i+23)%24)+0.5;
        if(p1>255||p1<1)
          p1=0;
        p2=pow(2,(i+14)%24)+pow(2,(i+15)%24)+0.5;
        if(p2>255||p2<1)
          p2=0;
        if(mode==0||mode==2)
        {
          set(p1,p2,255,14);
          delayMicroseconds(1);
        }
        if(mode==1||mode==2)
        {
          set(p1,p2,254,15);
          delayMicroseconds(1);
        }
      }
    }
  }
}

void mode_c(int t)
{
  int i,j,cnt1,cnt2,p1=255,p2=255,n1=255,n2=15,n1_tmp=255,n2_tmp=255;
  for(cnt1=0;cnt1<t;cnt1++)
  {
    p1=255;
    p2=255;
    n1=255;
    n2=15;
    n1_tmp=255;
    n2_tmp=15;
    for(i=0;i<6;i++)
    {
      n1=255-pow(2,i);
      if(i<2)
        n1-=pow(2,i+6);
      if(i>1)
        n2-=pow(2,5-i);
      p1=0;
      p2=0;
      for(j=0;j<16;j++)
      {
        for(cnt2=0;cnt2<15;cnt2++)
        {
          if(i>0&&cnt2==0&&j==0)
          {
            n1_tmp-=pow(2,i-1);
            if(i==1||i==2)
              n1_tmp-=pow(2,i+5);
            if(i>2)
              n2_tmp-=pow(2,6-i);
          }
          set(255,255,n1_tmp,n2_tmp);
          delay(1);
          if(i%2==0&&cnt2==0)
          {
            if(j<8)
              p1+=pow(2,j)+0.5;
            else if(j>7)
              p2+=pow(2,j-8)+0.5;
          }
          else if(i%2==1&&cnt2==0)
          {
            if(j<8)
              p2+=pow(2,7-j)+0.5;
            else if(j>7)
              p1+=pow(2,15-j)+0.5;
          }
          set(p1,p2,n1,n2);
          delay(1);
        }
      }
    }
  }
}

void mode_d(int t,int mode)
{
  int i,j,k,cnt,p1[6],n1,n2;
  for(i=0;i<t;i++)
  {
    for(j=0;j<12;j++)
    {
      switch(j){
      case 0:
        p1[0]=192;
        p1[1]=96;
        p1[2]=24;
        p1[3]=24;
        p1[4]=6;
        p1[5]=3;
        break;
       case 1:
        p1[0]=96;
        p1[1]=192;
        p1[2]=48;
        p1[3]=48;
        p1[4]=12;
        p1[5]=6;
        break;
       case 2:
        p1[0]=48;
        p1[1]=96;
        p1[2]=96;
        p1[3]=96;
        p1[4]=24;
        p1[5]=12;
        break;
       case 3:
        p1[0]=24;
        p1[1]=48;
        p1[2]=192;
        p1[3]=192;
        p1[4]=48;
        p1[5]=24;
        break;
       case 4:
        p1[0]=12;
        p1[1]=24;
        p1[2]=96;
        p1[3]=96;
        p1[4]=96;
        p1[5]=48;
        break;
       case 5:
        p1[0]=6;
        p1[1]=12;
        p1[2]=48;
        p1[3]=48;
        p1[4]=192;
        p1[5]=96;
        break;
       case 6:
        p1[0]=3;
        p1[1]=6;
        p1[2]=24;
        p1[3]=24;
        p1[4]=96;
        p1[5]=192;
        break;
       case 7:
        p1[0]=6;
        p1[1]=3;
        p1[2]=12;
        p1[3]=12;
        p1[4]=48;
        p1[5]=96;
        break;
       case 8:
        p1[0]=12;
        p1[1]=6;
        p1[2]=6;
        p1[3]=6;
        p1[4]=24;
        p1[5]=48;
        break;
       case 9:
        p1[0]=24;
        p1[1]=12;
        p1[2]=3;
        p1[3]=3;
        p1[4]=12;
        p1[5]=24;
        break;
       case 10:
        p1[0]=48;
        p1[1]=24;
        p1[2]=6;
        p1[3]=6;
        p1[4]=6;
        p1[5]=12;
        break;
       case 11:
        p1[0]=96;
        p1[1]=48;
        p1[2]=12;
        p1[3]=12;
        p1[4]=3;
        p1[5]=6;
        break;
      }
      for(cnt=0;cnt<7;cnt++)
      {
        for(k=0;k<6;k++)
        {
          n1=255-pow(2,k);
          if(k>3)
          {
            n1-=pow(2,11-k);
            n2=15;
          }
          else if(k<4)  
            n2=15-pow(2,k);
          if(mode==0)
          {
            set(255-p1[k],255-p1[k],n1,n2);
            delay(2);
          }
          else if(mode==1)
          {
            set(p1[k],p1[k],n1,n2);
            delay(1);
          }
        }
      }
    }
  }
}

void mode_e(int t)
{
  int i,j,n1,n2,del=80;
  for(j=0;j<t;j++)
  {
    for(i=0;i<7;i++)
    {
      n1=255-pow(2,i);
      if(i==5)
        n1=95;
      else if(i==6)
        n1=191;
      n2=15-pow(2,i-1);
      if(n2<=0)
        n2=15;
      if(i==0)
        n2=15;
      set(255,255,n1,n2);
      delay(del);
    }
    for(i=5;i>0;i--)
    {
      n1=255-pow(2,i);
      if(i==5)
        n1=95;
      else if(i==6)
        n1=191;
      n2=15-pow(2,i-1);
      if(n2<=0)
        n2=15;
      if(i==0)
        n2=15;
      set(255,255,n1,n2);
      delay(del);
    }
  }
}

void mode_f(int t,int mode)
{
  int i,j,del=20;
  for(j=0;j<t;j++)
  {
    for(i=0;i<16;i++)
    {
      if(i<7)
      {
        set(pow(2,i)+pow(2,i+1)+0.5,0,0,0);
        delay(del);
      }
      else if(i==7)
      {
        set(128,1,0,0);
        delay(del);
      }
      else 
      {
        set(0,pow(2,i-8)+pow(2,i-7)+0.5,0,0);
        delay(del);
      }
    }
    if(mode==1)
    {
      for(i=14;i>0;i--)
      {
        if(i<7)
        {
          set(pow(2,i)+pow(2,i+1)+0.5,0,0,0);
          delay(del);
        }
        else if(i==7) 
        {
          set(128,1,0,0);
          delay(del);
        }
        else 
        {
          set(0,pow(2,i-8)+pow(2,i-7)+0.5,0,0);
          delay(del);
        }
      }
    }
  }
}

void mode_g(int t)
{
  int i,j,k,p1=0,p2=0,n1=0,n2=0,tmp;
  for(i=0;i<t;i++)
  {
    for(j=0;j<2;j++)
    {
      p1+=pow(2,random(0,8))+pow(2,random(8,16));
      p2+=pow(2,random(0,8))+pow(2,random(8,16));
      n1+=random(0,256);
      n2+=random(0,16);
    }
    p1%=256;
    p2%=256;
    n1%=256;
    n2%=256;
    for(k=0;k<6;k++)
    {
      n1+=pow(2,k);
      n2+=pow(2,k);
      while(1)
      {
        if(n1>255)
        {
          tmp=n1-256;
          n1%=256;
          n2+=tmp;
        }
        if(n2>15)
        {
          tmp=n2-16;
          n2%=16;
          n1+=tmp;
        }
        if(n1<256&&n2<16)
          break;
      } 
      set(p1-random(0,p1),p2-random(0,p2),n1,n2);
      delay(150);
    }
    p1=0;
    p2=0;
    n1=0;
    n2=0;
  }
}

void mode_h(int t,int mode)
{
  int i,j,k;
  for(i=0;i<t;i++)
  {
    if(mode==0)
    {
      for(k=0;k<5;k++)
      {
        for(j=0;j<20;j++)
        {
          set(15,15,204,3);
          delay(1);
          set(240,240,51,12);
          delay(1);
        }
        dark(20);
      }
      for(k=0;k<5;k++)
      {
        for(j=0;j<20;j++)
        {
          set(240,240,204,3);
          delay(1);
          set(15,15,51,12);
          delay(1);
        }
        dark(20);
      }
    }
    if(mode==1)
    {
      for(k=0;k<5;k++)
      {
        for(j=0;j<10;j++)
        {
          set(15,15,204,3);
          delay(1);
          set(240,240,51,12);
          delay(1);
          set(15,15,102,6);
          delay(1);
          set(240,240,153,9);
          delay(1);
        }
        dark(20);
      }
      for(k=0;k<5;k++)
      {
        for(j=0;j<10;j++)
        {
          set(240,240,204,3);
          delay(1);
          set(15,15,51,12);
          delay(1);
          set(240,240,102,6);
          delay(1);
          set(15,15,153,9);
          delay(1);
        }
        dark(20);
      }
    }
    if(mode==2)
    {
      for(k=0;k<5;k++)
      {
        for(j=0;j<10;j++)
        {
          set(15,15,204,3);
          delay(1);
          set(240,240,51,12);
          delay(1);
          set(240,240,102,6);
          delay(1);
          set(15,15,153,9);
          delay(1);
        }
        dark(20);
      }
      for(k=0;k<5;k++)
      {
        for(j=0;j<10;j++)
        {
          set(240,240,204,3);
          delay(1);
          set(15,15,51,12);
          delay(1);
          set(15,15,102,6);
          delay(1);
          set(240,240,153,9);
          delay(1);
        }
        dark(20);
      }
    }
  }
}

void mode_i(int t)
{
  int i,j,cnt=0,p1_a,p2_a,p1_b,p2_b,p1_c,p2_c,n1_a,n2_a,n1_b,n2_b,n1_c,n2_c;
  for(j=0;j<t;j++)
  {
    n1_a=255;
    n2_a=15;
    n1_b=255;
    n2_b=15;
    n1_c=255;
    n2_c=15;
    p1_a=pow(2,random(1,8))+pow(2,random(1,8))+pow(2,random(1,8))+pow(2,random(1,8))+0.5;
    p2_a=pow(2,random(1,8))+pow(2,random(1,8))+pow(2,random(1,8))+pow(2,random(1,8))+0.5;
    p1_b=pow(2,random(1,8))+pow(2,random(1,8))+pow(2,random(1,8))+pow(2,random(1,8))+0.5;
    p2_b=pow(2,random(1,8))+pow(2,random(1,8))+pow(2,random(1,8))+pow(2,random(1,8))+0.5;
    p1_c=pow(2,random(1,8))+pow(2,random(1,8))+pow(2,random(1,8))+pow(2,random(1,8))+0.5;
    p2_c=pow(2,random(1,8))+pow(2,random(1,8))+pow(2,random(1,8))+pow(2,random(1,8))+0.5;
    for(i=0;i<12;i++)
    {
      if(i<8)
        n1_a-=pow(2,i);
      else if(i>7)
        n2_a-=pow(2,11-i);
      if(i>3)
        n1_a+=pow(2,i-4)+0.5;
      if(i%3==0||i%3==1||i%3==2)
      {
        set(p1_a,p2_a,n1_a,n2_a);
        delay(15);
        set(p1_b,p2_b,n1_b,n2_b);
        delay(15);
        set(p1_c,p2_c,n1_c,n2_c);
        delay(15);
        set(p1_a,p2_a,n1_a,n2_a);
        delay(15);
      }
      if(i<4)
        n1_b-=pow(2,4+i);
      else if(i>3&&i<8)
        n2_b-=pow(2,7-i);
      else if(i>7)
        n1_b-=pow(2,i-8);
      if(i>3&&i<8)
        n1_b+=pow(2,i)+0.5;
      else if(i>7)
        n2_b+=pow(2,11-i)+0.5;
      if(i%3==1||i%3==2||i%3==0)
      {
        set(p1_a,p2_a,n1_a,n2_a);
        delay(15);
        set(p1_b,p2_b,n1_b,n2_b);
        delay(15);
        set(p1_c,p2_c,n1_c,n2_c);
        delay(15);
        set(p1_b,p2_b,n1_b,n2_b);
        delay(15);
      }
      if(i<4)
        n2_c-=pow(2,3-i);
      else if(i>3&&i<8)
      {
        n1_c-=pow(2,i-4);
        n2_c+=pow(2,7-i)+0.5;
      }
      else if(i>7)
      {
        n1_c-=pow(2,i-4);
        n1_c+=pow(2,i-8)+0.5;
      }
      if(i%3==2||i%3==0||i%3==1)
      {
        set(p1_a,p2_a,n1_a,n2_a);
        delay(15);
        set(p1_b,p2_b,n1_b,n2_b);
        delay(15);
        set(p1_c,p2_c,n1_c,n2_c);
        delay(15);
        set(p1_c,p2_c,n1_c,n2_c);
        delay(15);
      }
      set(p1_a,p2_a,n1_a,n2_a);
      delay(20);
      set(p1_b,p2_b,n1_b,n2_b);
      delay(20);
      set(p1_c,p2_c,n1_c,n2_c);
      delay(20);
      set(0,0,0,0);
      delay(10);
      set(255,255,0,0);
      delay(10);
    }
    if(i==11&&cnt<3)
    {
      cnt++;
      i=0;
    }
  }
}

void mode_j(int t,int mode)
{
  int i,j,p1,p2;
  for(i=0;i<t;i++)
  {
    if(mode==0)
    {
      p1=0;
      p2=0;
    }
    else if(mode==1)
    {
      p1=255;
      p2=255;
    }
    for(j=0;j<16;j++)
    {
      if(mode==0)
      {
        if(j<8)
          p2+=pow(2,7-j)+0.5;
        else if(j>7)
          p1+=pow(2,15-j)+0.5;
      }
      else if(mode==1)
      {
        if(j<8)
          p1-=pow(2,j);
        else if(j>7)
          p2-=pow(2,j-8);
      }
      set(p1,p2,0,0);
      delay(20);
    }
  }
}

void mode_k(int t,int mode)
{
  int i,j,p;
  for(i=0;i<t;i++)
  {
    p=255;
    if(mode==0)
    {
      dark(80);
      for(j=0;j<12;j++)
      {
        if(j<8)
        {
          p-=pow(2,j);
          set(255,255,p,15);
        }
        else if(j==8)
          set(255,255,0,7);
        else if(j==9)
          set(255,255,0,3);
        else if(j==10)
          set(255,255,0,1);
        else if(j==11)
          set(255,255,0,0);
        delay(80);
      }
    }
    else if(mode==1)
    {
      bright(80);
      for(j=0;j<11;j++)
      {
        if(j==0)
          set(255,255,0,1);
        else if(j==1)
          set(255,255,0,3);
        else if(j==2)
          set(255,255,0,7);
        else if(j>2)
        {
          p=0;
          for(int k=0;k<(10-j);k++)
            p+=pow(2,k)+0.5;
          set(255,255,255-p,15);
        }
        delay(80);
      }
    }
  }
}

void mode_l(int t)
{
  int i,j,k,l,tmp[192],ran,cnt=0,p1,p2,n1,n2,p_tmp,n_tmp;
  for(i=0;i<t;i++)
  {
    cnt=0;
    for(j=0;j<192;j++)
      tmp[j]=0;
    while(1)
    {
      if(cnt==16)
        break;
      cnt++;
      for(j=0;j<12;j++)
      {
        p1=0;
        p2=0;
        while(1)
        {
          ran=random(0,192);
          if(tmp[ran]==0)
          {
            tmp[ran]=1;
            break;
          }
        }
        for(k=0;k<192;k++)
        {
          if(tmp[k]==1&&k/16==j)
          {
            if(j<8)
            {
              n1=255-pow(2,j);
              n2=15;
            }
            else if(j>7)
            {
              n1=255;
              n2=15-pow(2,11-j);
            }
            if(k%16<8)
              p1+=pow(2,k%16)+0.5;
            else if(k%16>7)
              p2+=pow(2,k%16-8)+0.5;
          }
        }
        set(p1,p2,n1,n2);
        delay(1);
      }
    }
  }
}

void mode_random()
{
  int ran;
  ran=random(0,18);
  switch(ran)
  {
    case 0:
      mode_a(6,0);
      break;
    case 1:
      mode_a(6,1);
      break;
    case 2:
      mode_b(5,0);
      break;
    case 3:
      mode_b(5,1);
      break;
    case 4:
      mode_b(5,2);
      break;
    case 5:
      mode_c(1);
      break;
    case 6:
      mode_d(6,0);
      break;
    case 7:
      mode_d(6,1);
      break;
    case 8:
      mode_e(4);
      break;
    case 9:
      mode_f(5,0);
      break;
    case 10:
      mode_f(5,1);
      break;
    case 11:
      mode_g(5);
      break;
    case 12:
      mode_h(6,0);
      break;
    case 13:
      mode_h(6,1);
      break;
    case 14:
      mode_h(6,2);
      break;
    case 15:
      mode_i(2);
      break;
    case 16:
      mode_j(3,0);
      break;
    case 17:
      mode_j(3,1);
      break;
    case 18:
      mode_k(3,0);
      break;
    case 19:
      mode_k(3,1);
      break;
    case 20:
      mode_l(2);
      break;
  }
}
