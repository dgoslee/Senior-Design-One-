int redLed = 12;
int greenLed = 11;
int whiteLed = 7;
int buzzer = 10;
int smokeA0 = A5;
int AOUTpin = A4;
int DOUTpin = 8;

 int sensorThres = 400;

 

void setup() {

// Output setups, LED, buzzer, motor

pinMode(redLed, OUTPUT);
pinMode(greenLed, OUTPUT);
pinMode(whiteLed, OUTPUT);
pinMode(buzzer, OUTPUT);
pinMode(smokeA0, INPUT);
pinMode(DOUTpin, INPUT);
Serial.begin(115200);

}

void loop() {

// Defining the read intergers for the input

int analogSensor = analogRead(smokeA0);
int value = analogRead(AOUTpin);
int limit = digitalRead(DOUTpin);

 

//Output of serial print and LED, buzzer, motor

Serial.print("Pin A0: ");
Serial.println(analogSensor);
Serial.print("CO value: ");
Serial.println(value);
Serial.print("Limit: ");
Serial.println(limit);
delay(100);

if (analogSensor > sensorThres && value > 100) // Both triggered

{

digitalWrite(redLed, HIGH);
digitalWrite(greenLed, HIGH);
digitalWrite(whiteLed, LOW);
tone(buzzer, 1000, 600);
delay(100);
tone(buzzer, 5000, 600);

}

else if (analogSensor < sensorThres && value > 100) // MQ-7 triggered

{

digitalWrite(redLed, HIGH);
digitalWrite(greenLed, LOW);
digitalWrite(whiteLed, LOW);
tone(buzzer, 1000, 600);
delay(100);
tone(buzzer, 5000, 600);

}

else if (analogSensor > sensorThres && value < 100) // MQ-2 triggered

{

digitalWrite(redLed, LOW);
digitalWrite(greenLed, HIGH);
digitalWrite(whiteLed, LOW);

tone(buzzer, 1000, 600);
delay(100);
tone(buzzer, 5000, 600);

digitalWrite(redLed, LOW);
digitalWrite(redLed, HIGH);

}

else if  (analogSensor < sensorThres && value < 100) // Neutral setup

{

digitalWrite(redLed, LOW);
digitalWrite(greenLed, LOW);
digitalWrite(whiteLed, HIGH);
noTone(buzzer);

}

}
