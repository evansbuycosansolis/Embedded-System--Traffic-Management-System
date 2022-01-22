
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



void setup()
{
  Serial.begin(9600);
  tm1637.set(BRIGHT_TYPICAL);//BRIGHT_TYPICAL = 2,BRIGHT_DARKEST = 0,BRIGHTEST = 7;
  tm1637.init();
  Timer1.initialize(10000);//timing for 10ms
  Timer1.attachInterrupt(TimingISR);//declare the interrupt serve routine:TimingISR
  Timer1.attachInterrupt(TimingISR1);//declare the i  
  
  tm16371.set(BRIGHT_TYPICAL);//BRIGHT_TYPICAL = 2,BRIGHT_DARKEST = 0,BRIGHTEST = 7;
  tm16371.init();
 
 
  Timer1.attachInterrupt(TimingISR1);//declare the interrupt serve routine:TimingISR  
 
}
void loop()
{
 
  if(Update == ON)
  {
    TimeUpdate();
    tm1637.display(TimeDisp);
    TimeUpdate1();
    tm16371.display(TimeDisp);
    
     
  }
}
//************************************************
void TimingISR()
{
  microsecond_10 ++;
  Update = ON;
  if(microsecond_10 == 100){
    second --;
    if(second == 0)
    {
      second = 30;
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
