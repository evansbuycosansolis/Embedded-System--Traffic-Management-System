#include <TM1637Display.h>
#define CLK 2
#define DIO 3
TM1637Display display(CLK, DIO);

int red=7;
int yellow=12;
int green= 11;
int Red1=10;
int Yellow1=9;
int Green1= 8;

  
  int Lane1[] = {7,12,11}; // Lane 1 Red, Yellow and Green
  int Lane2[] = {10,9,8};// Lane 2 Red, Yellow and Green
  int Lane3[] = {7,12,11};// Lane 3 Red, Yellow and Green
  int Lane4[] = {10,9,8};// Lane 4 Red, Yellow and Green
  
  int i=300;
  int j=600;
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
  void   ultrasonic1();
  void   ultrasonic4();
  void   timer1();
   void  timer2();
  
  void setup() 
  {
  Serial.begin(9600);
   pinMode(trigPin4, OUTPUT); // Sets the trigPin as an Output
   pinMode(echoPin4, INPUT); // Sets the echoPin as an Input
   pinMode(trigPin1, OUTPUT); // Sets the trigPin as an Output
   pinMode(echoPin1, INPUT); // Sets the echoPin as an Input
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
   // ultrasonic1();
   // ultrasonic4();
   // timer1();
  }
  


void loop() 
 {
//lanes();
int i=600;
  display.print(i);
  delay(100);
  i--;
  
  
 }

//=========================================
// traffic lights
//=========================================
void lanes(){
  
    digitalWrite(Lane1[2], HIGH);
  digitalWrite(Lane3[0], HIGH);
  digitalWrite(Lane4[0], HIGH);
  digitalWrite(Lane2[0], HIGH);
  delay(60000);
  digitalWrite(Lane1[2], LOW);
  digitalWrite(Lane3[0], LOW);
  digitalWrite(Lane1[1], HIGH);
  digitalWrite(Lane3[1], HIGH);
  delay(30000);
  digitalWrite(Lane1[1], LOW);
  digitalWrite(Lane3[1], LOW);
  digitalWrite(Lane1[0], HIGH);
  digitalWrite(Lane3[2], HIGH);
  delay(60000);
  digitalWrite(Lane3[2], LOW);
  digitalWrite(Lane4[0], LOW);
  digitalWrite(Lane3[1], HIGH);
  digitalWrite(Lane4[1], HIGH);
  delay(30000);
  digitalWrite(Lane3[1], LOW);
  digitalWrite(Lane4[1], LOW);
  digitalWrite(Lane3[0], HIGH);
  digitalWrite(Lane4[2], HIGH);
  delay(60000);
  digitalWrite(Lane4[2], LOW);
  digitalWrite(Lane2[0], LOW);
  digitalWrite(Lane4[1], HIGH);
  digitalWrite(Lane2[1], HIGH);
  delay(30000);
  digitalWrite(Lane4[1], LOW);
  digitalWrite(Lane2[1], LOW);
  digitalWrite(Lane4[0], HIGH);
  digitalWrite(Lane2[2], HIGH);
  delay(60000);
  digitalWrite(Lane1[0], LOW);
  digitalWrite(Lane2[2], LOW);
  digitalWrite(Lane1[1], HIGH);
  digitalWrite(Lane2[1], HIGH);
  delay(30000);
  digitalWrite(Lane2[1], LOW);
  digitalWrite(Lane1[1], LOW);
  }



 //=========================================
// ultrasonic sensor2
//=========================================
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
if (distance1 <= 15){
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
    if (counter4>15){
    timer2();
    }
  }
}
//=========================================
// ultrasonic sensor 1
//=========================================
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
if (distance4 <= 15){
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
  if (counter4 >15){
    delay (40000);
    }
    
  }
}
}
//=========================================
// timer2
//=========================================
void timer2()
{
  int i=600;
  display.print(i);
  delay(100);
  i--;
}

//=========================================
// timer1
//=========================================
void timer1()
{
  int i=300;
  display.print(i);
  delay(100);
  i--;
}



//=========================================
// timer1
//=========================================

void lane1(){
  digitalWrite (red, HIGH);
  digitalWrite (yellow, LOW);
  digitalWrite (green, LOW);
  for (int x=0; x=30; x--){
    display.print(x);
    delay (1000);
    }

  digitalWrite (red, LOW);
  digitalWrite (yellow, HIGH);
  delay(4000);
  digitalWrite (yellow, LOW);
  digitalWrite (green, HIGH);
  for (int x=0; x=30; x--){
    display.print(x);
    delay (1000);
    }

  }

