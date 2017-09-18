
#include <Wire.h>

void setup()
{
  delay(500);

  pinMode(10, OUTPUT);
  softAnalogWrite(10, 128, 24000000);
  delay(100);
  
  pinMode(14, OUTPUT);
  digitalWrite(14, LOW);
  digitalWrite(14, HIGH);
  delay(100);
  
  Wire.begin();
  Serial.begin(9600);
  
  /*
  delay(500);
  
   select_page(0);
   delay(10);
   write_reg(byte(0x65), byte(0xa0), byte(0x00)); // Bypass PLL
   delay(10);
   select_page(1);
   delay(10);
   write_reg(byte(0xC3), byte(0x05), byte(0x01)); // MCU reset
   delay(10);
   select_page(0);
   delay(10);
   write_reg(byte(0x0D), byte(0x00), byte(0x21)); // soft reset
   delay(10);
   write_reg(byte(0x0D), byte(0x00), byte(0x00)); // disable soft reset
   delay(10);
  //select_page(0);
  //write_reg(byte(0x05), byte(0xFFFF), byte(0xFFEF));*/
}

void loop()
{
  while(!Serial.available());
  while(Serial.available()) Serial.read();
  int16_t result = read_reg(0);
  // Output results
  Serial.println("Result Read");
  Serial.print("  Hex: ");
  Serial.print("0x");
  Serial.println(result, HEX);
  Serial.print("  Decimal: ");
  Serial.println(result);
  Serial.println();
}

void select_page(int page)
{
  delay(5);
  Wire.beginTransmission(byte(0x5D));
  Wire.write(240);
  Wire.write(0);
  Wire.write(page);
  Wire.endTransmission(1);
}

void write_reg(byte addr, byte msb, byte lsb)
{
  delay(5);
  Wire.beginTransmission(byte(0x5D)); // transmit to device 93, Camera Module
  Wire.write(addr);   //register address 8bit, decimal    
  Wire.write(msb);  //msb
  Wire.write(lsb);  //lsb
  Wire.endTransmission(1);    // stop transmitting
}

int16_t read_reg(byte addr)
{
  delay(5);
  Wire.beginTransmission(93);
  Wire.write(addr);
  Wire.endTransmission(1);
  
  int a = Wire.requestFrom(93, 2, 1);   //request value form device 93, 2 bytes with stop bit
  Serial.println(a);
  int16_t result = ((Wire.read() << 8) | Wire.read());  //read 16 bits
  
  return result;
}

