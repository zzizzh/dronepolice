int sensorPin = 2;             // PIR Motion Sensor Pin
int sensorState = 0;           //Store the PIR Motion Sensor State
  
void setup() {
  pinMode(sensorPin, INPUT);      // The Sensor is an input device
  Serial.begin(9600);
}
  
void loop(){
  sensorState = digitalRead(sensorPin);  //Read the sensor state
  
  if (sensorState == HIGH) {       //If the sensor state is HIGH, turn on the LED
    Serial.println("1");
  }
  else {                               //otherwise turn off the LED
    //Serialrite(ledPin, LOW);
  }
}
