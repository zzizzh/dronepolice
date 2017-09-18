
int data_p[] = {14, 15, 16, 17, 18, 19, 2, 3};
//int xclock_p = 4;
int pclock_p = 5;
int vsynch_p = 6;
int href_p = 7;

// 읽는 방법
// frameready[!writingframe] 의 값이 1일 때,
// pixel[!writingframe] 의 640x480 픽셀 데이터가 사용가능한 상태가 됨

int pclockprev = 0;
int pclock = 0;
int href = 0;
int vsynch = 0;
int vsynchprev = 0;
int framevalid = 0;
int frameready[2] = {0,};
int writingframe = 0;

int frame_num = 0;

int hptr = 0;
int vptr = 0;
byte pixel[2][480][640];
int readB = 0;

void setup()
{
  Serial.begin(9600);
  // configure data pins as input
  for (int i = 0; i < 8; i++)
    pinMode(data_p[i], INPUT);
  // configure rest input pins
  //pinMode(xclock_p, OUTPUT);
  pinMode(pclock_p, INPUT);
  pinMode(href_p, INPUT);
  pinMode(vsynch_p, INPUT);

  //softAnalogWrite(xclock_p, 128, 8000000); 
}

void loop()
{
  vsynchprev = vsynch;
  vsynch = digitalRead(vsynch_p);
  Serial.print("vsynchprev : ");
  Serial.println(vsynchprev);
  Serial.print("vsynch : ");
  Serial.println(vsynch);
  
  href = digitalRead(href_p);

  pclockprev = pclock;
  pclock = digitalRead(pclock_p);
  Serial.print("pclockprev : ");
  Serial.println(pclockprev);
  Serial.print("pclock : ");
  Serial.println(pclock);
  
  if(!vsynchprev && vsynch)
  {
    framevalid = 0;
    writingframe ^= 1;
    frameready[writingframe] = 0;
    frameready[!writingframe] = 1;

    Serial.print(readB);
    readB = 0;
    Serial.println(" bytes frame reading complete");
  }
  else if(vsynchprev && !vsynch) framevalid = 1;

  if(framevalid && href && !pclockprev && pclock)
  {
    pixel[writingframe][vptr][hptr++] = readDataSignal();
    readB++;
    if(hptr == 640)
    {
      hptr = 0;
      if(++vptr) framevalid = 0;
    }
  }
}


byte readDataSignal()
{
  byte result = 0;
  for (int i = 0; i < 8; i++)
    result = result << 1 | digitalRead(data_p[i]);
  return result;
}
