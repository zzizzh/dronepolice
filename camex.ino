
int data_p[] = {2,3,4,5,6,7,8,9};
int xclock_p = 10;
int pclock_p = 11;
int href_p = 12;
int vsynch_p = 13;

int lastPclock = 0;
int pclock;
int href;
int vsynch;
byte pixel;

void setup() {

  Serial.begin(9600);
  Serial.println("started");
  // configure data pins as input
  for (int i = 0; i < 8; i++) {
    pinMode(data_p[i], INPUT);
       n}
  // configure rest input pins
  pinMode(xclock_p, OUTPUT);
  pinMode(pclock_p, INPUT);
  pinMode(href_p, INPUT);
  pinMode(vsynch_p, INPUT);

}

int control = 0;

void loop() {
  
  // just take one snapshot (307200 = 600 * 480) {{{
  if (control >= 1920000) {
    return;
  }
  // }}}
  
  digitalWrite(xclock_p, HIGH);
  
  //Serial.println("clock written");

  vsynch = digitalRead(vsynch_p);
  href = digitalRead(href_p);
  pclock = digitalRead(pclock_p);
  
  if (vsynch == HIGH) return;
  if (href == LOW) return;
  if (!(lastPclock == HIGH && pclock == LOW)) {
    lastPclock = pclock;
    return;
  } else {
    lastPclock = pclock;
  }
  
  pixel = readByteFromDataInput();
  
  char s[10];
  sprintf(s, "%d ", pixel);
  
  Serial.println(s);

  if (control % 1600 == 0) {
    Serial.println("");
  }
  
  // just take one snapshot {{{
  control++;
  // }}}

  if (control >= 1920000) {
    Serial.println("finished");
  }

}

byte readByteFromDataInput() {
  byte result = 0;
  for (int i = 0; i < 8; i++) {
    result = result << 1 | digitalRead(data_p[i]);
  }
  return result;
}
