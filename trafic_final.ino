//  Author:Frankie.Chu
//  Date:9 April,2012
//
//  This library is free software; you can redistribute it and/or
//  modify it under the terms of the GNU Lesser General Public
//  License as published by the Free Software Foundation; either
//  version 2.1 of the License, or (at your option) any later version.
//
//  This library is distributed in the hope that it will be useful,
//  but WITHOUT ANY WARRANTY; without even the implied warranty of
//  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
//  Lesser General Public License for more details.
//
//  You should have received a copy of the GNU Lesser General Public
//  License along with this library; if not, write to the Free Software
//  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
//
//  Modified record:
//
/*******************************************************************************/
#include <EEPROM.h>
#include <TimerOne.h>
#include <avr/pgmspace.h>
#include "TM1637.h"
#define ON 1
#define OFF 0

int8_t TimeDisp[] = {0x00,0x00,0x00,0x00};
unsigned char ClockPoint = 1;
unsigned char Update;
unsigned char microsecond_10 = 0;
unsigned char second;
unsigned char _microsecond_10 = 0;
unsigned char _second;
unsigned int eepromaddr;
boolean Flag_ReadTime;

#define CLK 2//pins definitions for TM1637 and can be changed to other ports        
#define DIO 3
TM1637 tm1637(CLK,DIO);


//=======================================
// Ultrasonic Sensors Declarations
//=======================================
const int trigPin4 = 6;
const int echoPin4 = 13;
const int trigPin1 = 1;
const int echoPin1 = 0;
int counter4 = 0;
int currentState4 = 0;
int previousState4 = 0;
int counter1 = 0;
int currentState1 = 0;
int previousState1 = 0;

//=======================================
// LED Traffic Lights Declarations
//=======================================
int GREEN_1and3 = 11;
int YELLOW_1and3  = 12;
int RED_1and3  = 7;
int GREEN_2and4 = 8;
int YELLOW_2and4  = 9;
int RED_2and4 = 10;

int DELAY_GREEN_1and3 = 5000;
int DELAY_YELLOW_1and3 = 2000;
int DELAY_RED_1and3 = 5000;
int DELAY_GREEN_2and4 = 5000;
int DELAY_YELLOW_2and4 = 2000;
int DELAY_RED_2and4 = 5000;
int greenLightDuration1 = 50;
int redLightDuration1 = 50;
int greenLightDuration2 = 50;
int redLightDuration2 = 50;
int forCondition = 1;
int forCondition2 = 1;



void setup()
{
  Serial.begin(9600);
  tm1637.set(BRIGHT_TYPICAL);//BRIGHT_TYPICAL = 2,BRIGHT_DARKEST = 0,BRIGHTEST = 7;
  tm1637.init();
  Timer1.initialize(10000);//timing for 10ms
  Timer1.attachInterrupt(TimingISR);//declare the interrupt serve routine:TimingISR  
  second = 15;
}
void loop()
{
  
  if(Update == ON)
  {
// ultrasonic1();
// changeLights1();
   digitalWrite(GREEN_2and4, HIGH);
   digitalWrite(YELLOW_2and4, HIGH);
   digitalWrite(RED_2and4, HIGH);
   
   digitalWrite(GREEN_1and3, HIGH);
   digitalWrite(YELLOW_1and3, HIGH);
   digitalWrite(RED_1and3, HIGH);
  
    TimeUpdate();
    tm1637.display(TimeDisp);
  }
}


void changeLights2(){

  
    if(second == 0) {

      if(forCondition2 == 1) {
        digitalWrite(GREEN_2and4, LOW);
        digitalWrite(YELLOW_2and4, HIGH);
        Serial.println("Yellow On");
        forCondition2 = 2;
        delay(300);
        second = 4;
      }
      else if(forCondition2 == 2) {
        digitalWrite(YELLOW_2and4, LOW);
        digitalWrite(RED_2and4, HIGH);
        Serial.println("Red on");
        forCondition2 = 3;
        second = 15;
        delay(500);
      }

      else if(forCondition2 == 3) {
        digitalWrite(YELLOW_2and4, LOW);
        digitalWrite(RED_2and4, LOW);
        digitalWrite(GREEN_2and4, HIGH);
        Serial.println("Green on");
        forCondition2 = 1;
        second = 15;
        delay(300);
      }
         
   }

   
}


void changeLights1(){

  
     if(second == 0) {
  
        if(forCondition == 1) {
          digitalWrite(GREEN_1and3, LOW);
          digitalWrite(YELLOW_1and3, HIGH);
          Serial.println("Yellow On");
          forCondition = 2;
          delay(300);
          second = 4;
        }
        else if(forCondition == 2) {
          digitalWrite(YELLOW_1and3, LOW);
          digitalWrite(RED_1and3, HIGH);
          Serial.println("Red on");
          forCondition = 3;
          second = 15;
          delay(500);
        }
  
        else if(forCondition == 3) {
          digitalWrite(YELLOW_1and3, LOW);
          digitalWrite(RED_1and3, LOW);
          digitalWrite(GREEN_1and3, HIGH);
          Serial.println("Green on");
          forCondition = 1;
          second = 15;
          delay(300);
        }
         
   }

   
}

void ultrasonic4() {
  long duration4, distance4;
  digitalWrite(trigPin4, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin4, HIGH);
delayMicroseconds(10);
digitalWrite(trigPin4, LOW);
duration4 = pulseIn(echoPin4, HIGH);
distance4= duration4*0.034/2;
Serial.print("Distance: ");
Serial.println(distance4);

if (distance4 <= 10){
 currentState4 = 1;
 }
 else {
 currentState4 = 0;
 }
 delay(300);
 if(currentState4 != previousState4){
if(currentState4 == 1){
  counter4 = counter4 + 1;
  delay(500);
  Serial.println(counter4);
  }
}

}


void ultrasonic1() {
  long duration1, distance1;
  digitalWrite(trigPin1, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin1, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin1, LOW);
  duration1 = pulseIn(echoPin1, HIGH);
  distance1= duration1*0.034/2;
  Serial.print("Distance: ");
  Serial.println(distance1);

if (distance1 <= 5){
 currentState1 = 1;
 }
 else {
 currentState1 = 0;
 }
 delay(100);
 if(currentState1 != previousState1){
    if(currentState1 == 1){
    counter1 = counter1 + 1;
    Serial.println(counter1);
    }
}
}



//************************************************
void TimingISR()
{
  microsecond_10 ++;
  Update = ON;
  if(microsecond_10 == 100){
    second --;
    microsecond_10 = 0;  
  }

  ClockPoint = (~ClockPoint) & 0x01;
  if(Flag_ReadTime == 0)
  {
    _microsecond_10 = microsecond_10;
    _second = second;
  }
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
void stopwatchStart()//timer1 on
{
  Flag_ReadTime = 0;
  TCCR1B |= Timer1.clockSelectBits; 
}
void stopwatchPause()//timer1 off if [CS12 CS11 CS10] is [0 0 0].
{
  TCCR1B &= ~(_BV(CS10) | _BV(CS11) | _BV(CS12));
}

void stopwatchReset()
{
  stopwatchPause();
  Flag_ReadTime = 0;
  _microsecond_10 = 0;
  _second = 0;
  microsecond_10 = 0;
  second = 0;
  Update = ON;
}

void saveTime()
{
  EEPROM.write(eepromaddr ++,microsecond_10);
  EEPROM.write(eepromaddr ++,second);
}
void readTime()
{
  Flag_ReadTime = 1;
  if(eepromaddr == 0)
  {
    Serial.println("The time had been read");
    _microsecond_10 = 0;
    _second = 0;
  }
  else{
  _second = EEPROM.read(-- eepromaddr);
  _microsecond_10 = EEPROM.read(-- eepromaddr);
  Serial.println("List the time");
  }
  Update = ON;
}
