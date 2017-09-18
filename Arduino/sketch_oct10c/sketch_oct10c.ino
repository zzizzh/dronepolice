#include <SoftwareServo.h>

int PIN_IR = 19;
char a[5];
SoftwareServo s1;
SoftwareServo s2;
SoftwareServo s3;
SoftwareServo s4;
int r1;
int r2;
int r3;
int r4;

void setup() 
{
  Serial.begin(9600);
  Serial1.begin(9600);
  //pinMode(PIN_IR, INPUT);
  pinMode(10, OUTPUT);
  pinMode(11, OUTPUT);
  pinMode(12, OUTPUT);
  pinMode(13, OUTPUT);
  s1.attach(10);
  s2.attach(11);
  s3.attach(12);
  s4.attach(13);  
}

void loop()
{/*
  while(Serial1.available())
  {
    a = Serial1.read();
    Serial.print(a);
    if(a == 10) Serial.println();
  }*/
  
  if(Serial.available())
  {
    Serial.readBytes(a, 5);
    switch(a[0])
    {
      case '1':
      if(a[1] == '8') s1.write(r1 += 10);
      if(a[1] == '2') s1.write(r1 -= 10);
      Serial.print("1 : ");
      Serial.println(s1.read());
      break;
      
      case '2':
      if(a[1] == '8') s1.write(r2 += 10);
      if(a[1] == '2') s1.write(r2 -= 10);
      Serial.print("2 : ");
      Serial.println(s2.read());
      break;
      
      case '3':
      if(a[1] == '8') s2.write(r3 += 10);
      if(a[1] == '2') s2.write(r3 -= 10);
      Serial.print("3 : ");
      Serial.println(s3.read());
      break;
      
      case '4':
      if(a[1] == '8') s3.write(r4 += 10);
      if(a[1] == '2') s3.write(r4 -=10);
      Serial.print("4 : ");
      Serial.println(s4.read());
      break;
      
      case 'x':
      Serial.println("x wrote");
      s1.write(90);
      s2.write(90);
      s3.write(90);
      s4.write(90);
      break;
      
      case '?':
      
   if(s1.attached())
   {
     Serial.print("1 attached : ");
     Serial.println(s1.read());
   }
  else  Serial.println("1 not attached");
  if(s2.attached())
   {
     Serial.print("2 attached : ");
     Serial.println(s2.read());
   }
  else  Serial.println("2 not attached");
  if(s3.attached())
   {
     Serial.print("3 attached : ");
     Serial.println(s3.read());
   }
  else  Serial.println("3 not attached");
  if(s4.attached())
   {
     Serial.print("4 attached : ");
     Serial.println(s4.read());
   }
  else  Serial.println("4 not attached");
    }
  }
  
  //if(digitalRead(PIN_IR) == HIGH) Serial.println("Detected");
}

