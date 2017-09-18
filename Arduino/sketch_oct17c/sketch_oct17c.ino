
int PIN_IR = 19;
char flag;
int setval;
int PWM[4] = {10, 11, 12, 13};
int r[4] = {150, 150, 150, 150};

int minval = 100;
int maxval = 200;

void setup() 
{
  Serial.begin(9600);
  Serial1.begin(9600);
  
  for(int i = 0; i < 4; i++)
  {
    pinMode(PWM[i], OUTPUT);
    softAnalogWrite(PWM[i], 150);
  }
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
    int selected = -1;
    flag = Serial.read();
    setval = Serial.parseInt();
    switch(flag)
    {
      case '1': selected = 1; break;
      case '2': selected = 2; break;
      case '3': selected = 3; break;
      case '4': selected = 4; break;
      case 'a': selected = 0; break;
      case 's': startDrone(); break;
      case 'q': terminateDrone(); break;
    }

    if(selected != -1)
    {
      if(selected == 0)
      {
        for(int i = 0; i < 4; i++)
        {
          softAnalogWrite(PWM[i], setval);
          Serial.print(i + 1);
          Serial.print(" : ");
          Serial.println(setval);
        }
      }
      else
      {
        softAnalogWrite(PWM[selected-1], setval);
        Serial.print(selected);
        Serial.print(" : ");
        Serial.println(setval);
      }
    }
  }

  //if(digitalRead(PIN_IR) == HIGH) Serial.println("Detected");
}

  void startDrone()
  {
      Serial.println("pitch : ");
      for(int i = 0; i < 50; i++)
      {
        softAnalogWrite(PWM[0], 149 - i);
        delay(20);
        Serial.print(149 - i);
        Serial.print((i+1)%10 ? " " : "\n");
      }
      for(int i = 0; i < 50; i++)
      {
        softAnalogWrite(PWM[2], 149 - i);
        delay(20);
        Serial.print(149 - i);
        Serial.print((i+1)%10 ? " " : "\n");
      }
      Serial.println("시동 완료, 모터가 돌기 시작하면, pitch를 중립으로 하고 throttle을 조작하십시오.");
  }
  
  void terminateDrone()
  {
      Serial.println("pitch : ");
      for(int i = 0; i < 50; i++)
      {
        softAnalogWrite(PWM[0], 149 - i);
        delay(20);
        Serial.print(149 - i);
        Serial.print((i+1)%10 ? " " : "\n");
      }
      for(int i = 0; i < 50; i++)
      {
        softAnalogWrite(PWM[2], 151 + i);
        delay(20);
        Serial.print(151 + i);
        Serial.print((i+1)%10 ? " " : "\n");
      }
      Serial.println("시동이 꺼졌습니다.");
  }
