
#include <Wire.h>
#include <avr/io.h>
#include <util/delay.h>
#include <TimerOne.h>
#include <avr/interrupt.h>

#define TMR1 0  //Timer1 used for 8Mhz PWM Output

void setup()
{
  Serial.begin(9600);
  
 delay(100);
  
 pinMode(9, OUTPUT); // output pin for OCR2B

  TCCR1B |= (1 << CS10);  //selecting prescaler 0b001 (Tclk/1)
  TCCR1B &= ~((1<<CS12) | (1<<CS11));    // turn off CS12 and CS11 bits
  TCCR1A |= ((1<<WGM11) | (1<<WGM10));  //Configure timer 1 for TOP mode (with TOP = OCR1A)
  TCCR1B |= ((1<<WGM13) | (1<<WGM12));
  TCCR1A |= (1 << COM1A0); // Enable timer 1 Compare Output channel A in toggle mode 
  TCCR1A &= ~(1 << COM1A1);
  TCNT1 = 0;
  OCR1A = TMR1;

  delay(100);
  Wire.begin();
  
  
   byte prev;
  prev = read_reg(byte(0x12));
  write_reg(byte(0x12), prev & byte(0x42) | byte(0x05));
  prev = read_reg(byte(0x11));
  write_reg(byte(0x11), prev & byte(0x80) | byte(0x01));
  prev = read_reg(byte(0x6B));
  write_reg(byte(0x6B), prev & byte(0x3F) | byte(0x80));
  delay(100);
}

void loop()
{
  Serial.print("0x12 : ");
  Serial.println(read_reg(18));

  Serial.print("0x6B : ");
  Serial.println(read_reg(0x6B));

  Serial.print("0x11 : ");
  Serial.println(read_reg(17));

  Serial.print("0x15 : ");
  Serial.println(read_reg(0x15));

  Serial.println("==========================");

  delay(2000);
  
}

void write_reg(byte addr, byte data)
{
  delay(10);
  Wire.beginTransmission(33);
  Wire.write(addr); 
  Wire.write(0);
  Wire.write(data);
  Wire.endTransmission(1);
}

byte read_reg(byte addr)
{
  delay(10);
  Wire.beginTransmission(33);
  Wire.write(addr);
  Wire.endTransmission(1);
  
  Wire.requestFrom(33, 2, 1);
  Wire.read();
  return Wire.read();
}

