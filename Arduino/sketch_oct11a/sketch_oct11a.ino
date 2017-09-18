
#include <Wire.h>
#include <interrupt.h>  
#include <trace.h>  
  
#define MY_TRACE_PREFIX "ServoX86Lib"  
#define ERROR_FACTOR 1.1  

static int  (*pointer_write)(  int  handle,  const void  *buffer,  unsigned int  nbyte  ) = write;  

void setup()
{
  delay(500);
  Serial.begin(9600);
  
  pinMode(5, OUTPUT);
  softAnalogWrite(5, 128, 8000000);
  
  Wire.begin();
  /*
   select_page(0);
   delay(10);
   write_reg(byte(0x65), byte(0xa00)); // Bypass PLL
   delay(10);
   select_page(1);
   delay(10);
   write_reg(byte(0xc3), byte(0x0501)); // MCU reset
   delay(10);
   select_page(0);
   delay(10);
   write_reg(byte(0x0d), byte(0x0021)); // soft reset
   delay(10);
   write_reg(byte(0x0d), byte(0x0000)); // disable soft reset
   delay(10);
   */
  //select_page(0);
  //write_reg(byte(0x05), byte(0xFFFF), byte(0xFFEF));
}

void loop()
{
  while(!Serial.available());
  while(Serial.available()) Serial.read();
  int16_t result = read_reg(byte(0x00));
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

void write_reg(byte addr, byte data)
{
  delay(5);
  Wire.beginTransmission(byte(0x5D)); // transmit to device 93, Camera Module
  Wire.write(addr);   //register address 8bit, decimal    
  Wire.write(data >> 8);  //msb
  Wire.write(data & 255);  //lsb
  Wire.endTransmission(1);    // stop transmitting
}


int16_t read_reg(byte addr)
{
  delay(5);
  Wire.beginTransmission(byte(0x5D));
  Wire.write(addr);
  Wire.endTransmission(1);
  
  Wire.requestFrom(byte(0x5D), 2, 1);   //request value form device 93, 2 bytes with stop bit
  int16_t result = ((Wire.read() << 8) | Wire.read());  //read 16 bits
  
  return result;
}

void setPWM(int pin, int frequency, int duty_cycle)  
 {  
     int freqInNanoSec = (1.0/frequency) * 1000000000 * ERROR_FACTOR;  
       
     FILE *fp = NULL;  
     int ret = 0;  
     char export_value[16] = "";  
     char fs_path[50] = LINUX_PWM_EXPORT;  
  
     memset(fs_path, 0x00, sizeof(fs_path));  
     snprintf(fs_path, sizeof(fs_path), LINUX_PWM_PERIOD_FMT);  
  
     if (NULL == (fp = fopen(fs_path, "ab"))) {  
         trace_error("can't open handle to %s", fs_path);  
         return ;  
     }  
     rewind(fp);  
  
     memset(export_value, 0x0, sizeof(export_value));  
     snprintf(export_value, sizeof(export_value), "%u", freqInNanoSec);  
     fwrite(&export_value, sizeof(char), sizeof(export_value), fp);  
  
     fclose(fp);  
     /////////////////////////////////////////////////////////////  
     bool enable = 1;  
     //set the mux and open the handles  
     analogWrite(pin, 0);  
  
     int handle_enable = pin2pwmhandle_enable(pin);  
  
     lseek(handle_enable, 0, SEEK_SET);  
     ret = pointer_write(handle_enable, (const void*)&enable, sizeof(enable));  
     if (sizeof(enable) != ret) {  
         trace_error("can't write to enable\n");  
     }  
     /////////////////////////////////////////////////////////////       
    int value_duty = (1.0/frequency) * 1000000000 / (100.0/duty_cycle);  
      
    char value[16] = "";  
  
    value_duty *= ERROR_FACTOR;  
  
    int handle_duty = pin2pwmhandle_duty(pin);  
  
    memset(value, 0x0, sizeof(value));  
    snprintf(value, sizeof(value), "%u", (unsigned)value_duty);  
    lseek(handle_duty, 0, SEEK_SET);  
    ret = pointer_write(handle_duty, &value, sizeof(value));  
    if (sizeof(value) != ret) {  
         trace_error("can't write to duty_cycle\n");  
    }      
}
