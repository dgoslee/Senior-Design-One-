/*******
 
 All the resources for this project:
 https://www.hackster.io/Aritro

*******/

int redLed = 12; // red LED pin
int greenLed = 11; // green LED pin
int buzzer = 10; // Piezo Buzzer pin
int smokeA0 = A5; // MQ-2 analog output pin
// Your threshold value
int sensorThres = 18;

void setup() {
  pinMode(redLed, OUTPUT);
  pinMode(greenLed, OUTPUT);
  pinMode(buzzer, OUTPUT);
  pinMode(smokeA0, INPUT);
  Serial.begin(9600);
}

void loop() {
  int analogSensor = analogRead(smokeA0);

  Serial.print("Pin A0: ");
  Serial.println(analogSensor);
  // Checks if it has reached the threshold value
  if (analogSensor > sensorThres)
  {
    digitalWrite(redLed, HIGH);  // Will light red LED if threshold value is reached.
    digitalWrite(greenLed, LOW); // Will not light green LED if threshold value is reached. 
    tone(buzzer, 1000, 200); // Will activate buzzer if threshold value is reached. 
  }
  else
  {
    digitalWrite(redLed, LOW); // Will not light red LED.
    digitalWrite(greenLed, HIGH); // Will light green LED.
    noTone(buzzer); // Buzzer will not be activated.  
  }
  delay(100);
}
