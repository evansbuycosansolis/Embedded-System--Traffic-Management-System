
#include <TimerOne.h>
//#include <avr/pgmspace.h>
#include "TM1637.h"
#define ON 1
#define OFF 0

int8_t TimeDisp[] = {0x00,0x00,0x00,0x00};
unsigned char ClockPoint = 1;
unsigned char Update;
unsigned char Update1;
unsigned char microsecond_10 = 0;
unsigned char second=60;
unsigned char _microsecond_10 = 0;
unsigned char _second=60;
//unsigned int eepromaddr;
//boolean Flag_ReadTime;

#define CLK 14//pins definitions for TM1637 and can be changed to other ports        
#define DIO 18
TM1637 tm1637(CLK,DIO);
#define CLK1 17//pins definitions for TM1637 and can be changed to other ports        
#define DIO1 19
TM1637 tm16371(CLK1,DIO1);


int Lane1[] = {3,2,1}; // Lane 1 Red, Yellow and Green
int Lane2[] = {6,5,4};// Lane 2 Red, Yellow and Green
int Lane3[] = {9,8,7};// Lane 3 Red, Yellow and Green
int Lane4[] = {12,11,10};// Lane 4 Red, Yellow and Green


void setup() 
{
  for (int i = 0; i < 3; i++)
  {
    pinMode(Lane1[i], OUTPUT); 
    pinMode(Lane2[i], OUTPUT);
    pinMode(Lane3[i], OUTPUT);
    pinMode(Lane4[i], OUTPUT);
  }
  for (int i = 0; i < 3; i++)
  {
    digitalWrite(Lane1[i], LOW); 
    digitalWrite(Lane2[i], LOW);
    digitalWrite(Lane3[i], LOW);
    digitalWrite(Lane4[i], LOW);
  }
  Serial.begin(9600);
  tm1637.set(BRIGHT_TYPICAL);//BRIGHT_TYPICAL = 2,BRIGHT_DARKEST = 0,BRIGHTEST = 7;
  tm1637.init();
  Timer1.initialize(10000);//timing for 10ms
  Timer1.attachInterrupt(TimingISR);//declare the interrupt serve routine:TimingISR
  Timer1.attachInterrupt(TimingISR1);//declare the i  
  
  tm16371.set(BRIGHT_TYPICAL);//BRIGHT_TYPICAL = 2,BRIGHT_DARKEST = 0,BRIGHTEST = 7;
  tm16371.init();
 
 
  Timer1.attachInterrupt(TimingISR1);//declare the interrupt serve routine:TimingISR  
  if(Update == ON)
  {
    TimeUpdate();
    tm1637.display(TimeDisp);
    TimeUpdate1();
    tm16371.display(TimeDisp);
    
     
  }
}

void loop() {

  digitalWrite(Lane1[2], HIGH);
  digitalWrite(Lane3[0], HIGH);
  digitalWrite(Lane4[0], HIGH);
  digitalWrite(Lane2[0], HIGH);
delay(20000);
  digitalWrite(Lane1[2], LOW);
  digitalWrite(Lane3[0], LOW);
  digitalWrite(Lane1[1], HIGH);
  digitalWrite(Lane3[1], HIGH);
delay(20000);
  digitalWrite(Lane1[1], LOW);
  digitalWrite(Lane3[1], LOW);
  digitalWrite(Lane1[0], HIGH);
  digitalWrite(Lane3[2], HIGH);
delay(20000);
  digitalWrite(Lane3[2], LOW);
  digitalWrite(Lane4[0], LOW);
  digitalWrite(Lane3[1], HIGH);
  digitalWrite(Lane4[1], HIGH);
delay(20000);
  digitalWrite(Lane3[1], LOW);
  digitalWrite(Lane4[1], LOW);
  digitalWrite(Lane3[0], HIGH);
  digitalWrite(Lane4[2], HIGH);
delay(20000);
  digitalWrite(Lane4[2], LOW);
  digitalWrite(Lane2[0], LOW);
  digitalWrite(Lane4[1], HIGH);
  digitalWrite(Lane2[1], HIGH);
delay(20000);
  digitalWrite(Lane4[1], LOW);
  digitalWrite(Lane2[1], LOW);
  digitalWrite(Lane4[0], HIGH);
  digitalWrite(Lane2[2], HIGH);
delay(20000);
  digitalWrite(Lane1[0], LOW);
  digitalWrite(Lane2[2], LOW);
  digitalWrite(Lane1[1], HIGH);
  digitalWrite(Lane2[1], HIGH);
delay(20000);
  digitalWrite(Lane2[1], LOW);
  digitalWrite(Lane1[1], LOW);
 }
 void TimingISR()
{
  microsecond_10 ++;
  Update = ON;
  if(microsecond_10 == 100){
    second --;
    if(second == 0)
    {
      second = 60;
    }
    microsecond_10 = 0;  
    
  }
  ClockPoint = (~ClockPoint) & 0x01;
   _microsecond_10 = microsecond_10;
    _second = second;
}
void TimingISR1()
{
  microsecond_10 ++;
  Update = ON;
  if(microsecond_10 == 100){
    second --;
    if(second == 0)
    {
      second = 60;
    }
    microsecond_10 = 0;  
    
  }
  ClockPoint = (~ClockPoint) & 0x01;
   _microsecond_10 = microsecond_10;
    _second = second;
}
void TimingISR2()
{
  microsecond_10 ++;
  Update = ON;
  if(microsecond_10 == 100){
    second --;
    if(second == 0)
    {
      second = 60;
    }
    microsecond_10 = 0;  
    
  }
  ClockPoint = (~ClockPoint) & 0x01;
   _microsecond_10 = microsecond_10;
    _second = second;
}
void TimingISR3()
{
  microsecond_10 ++;
  Update = ON;
  if(microsecond_10 == 100){
    second --;
    if(second == 0)
    {
      second = 60;
    }
    microsecond_10 = 0;  
    
  }
  ClockPoint = (~ClockPoint) & 0x01;
   _microsecond_10 = microsecond_10;
    _second = second;
}
void TimeUpdate(void)
{
  if(ClockPoint)tm1637.point(POINT_ON);//POINT_ON = 1,POINT_OFF = 0;
  else tm1637.point(POINT_ON); 
  TimeDisp[2] = _microsecond_10 / 10;
  TimeDisp[3] = _microsecond_10 % 10;
  TimeDisp[0] = _second / 10;
  TimeDisp[1] = _second % 10;
  Update = OFF;
}
void TimeUpdate1(void)
{
  if(ClockPoint)tm16371.point(POINT_ON);//POINT_ON = 1,POINT_OFF = 0;
  else tm16371.point(POINT_ON); 
  TimeDisp[2] = _microsecond_10 / 10;
  TimeDisp[3] = _microsecond_10 % 10;
  TimeDisp[0] = _second / 10;
  TimeDisp[1] = _second % 10;
  Update = OFF;
}
