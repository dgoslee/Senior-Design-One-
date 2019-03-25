#include <Adafruit_Sensor.h>
#include <DHT.h>
#include <DHT_U.h> 
#include <RH_ASK.h> 
#include <SPI.h> 

#define dataPin 8 // Defines pin number to which the sensor is connected
#define dhtType DHT22

int analogMQ7 = A2;
int blueLed = 7;      
int MQ7sensorValue = 0;   // value read from the sensor
int redLed = 12;
int greenLed = 11;
int buzzer = 10;
int smokeA0 = A5;
// Your threshold value
int sensorThres = 25;


String str_humid;
String str_temp;
String str_out;

RH_ASK rf_driver;

DHT_Unified dht(dataPin, dhtType);

void setup() {

  dht.begin() ;
  rf_driver.init();
  sensor_t sensor;
  dht.temperature().getSensor(&sensor);
  
  pinMode(redLed, OUTPUT);
  pinMode(greenLed, OUTPUT);
  pinMode(buzzer, OUTPUT);
  pinMode(smokeA0, INPUT);
  Serial.println(F("MQ-7 Gas Sensor Instantiated"));
  pinMode(analogMQ7, INPUT);
  pinMode(blueLed, OUTPUT);
  Serial.begin(9600);
  
}

void loop() {
  
  int analogSensor = analogRead(smokeA0);
  sensors_event_t event;
  dht.temperature().getEvent(&event);
  
  Serial.print("MQ-2 Smoke Sensor: ");
  Serial.print(analogSensor);
  Serial.println(" PPM") ; 

  if (isnan(event.temperature)) {
    Serial.println(F("Error reading temperature!"));
  }
  else {
    Serial.print(F("Temperature: "));
    Serial.print(event.temperature);
    Serial.println(F("°C"));
  }
  // Get humidity event and print its value.
  dht.humidity().getEvent(&event);
  if (isnan(event.relative_humidity)) {
    Serial.println(F("Error reading humidity!"));
  }
  else {
    Serial.print(F("Humidity: "));
    Serial.print(event.relative_humidity);
    Serial.println(F("%"));
  }
    
  // Checks if it has reached the threshold value
  if (analogSensor > sensorThres)
  {
    digitalWrite(redLed, HIGH);
    digitalWrite(greenLed, LOW);
    tone(buzzer, 1000, 200);
  }
  else
  {
    digitalWrite(redLed, LOW);
    digitalWrite(greenLed, HIGH);
    noTone(buzzer);
  }
    
    analogWrite(analogMQ7, HIGH); // HIGH = 255
    // heat for 1 min
    delay(60000);
    // now reducing the heating power: turn the heater to approx 1,4V
    analogWrite(analogMQ7, 71.4); // 255x1400/5000
    // heat for 90 sec
    delay(90000);
    
  // B) reading    
    // CO2 via MQ7: we need to read the sensor at 5V, but must not let it heat up. So hurry!
    analogWrite(analogMQ7, HIGH); 
    delay(50); // Getting an analog read apparently takes 100uSec
    MQ7sensorValue = analogRead(analogMQ7);          
    
  // C) print the results to the serial monitor
    Serial.print("MQ-7 PPM: ");                       
    Serial.println(MQ7sensorValue);  
    
  // D) interpretation
    // Detecting range: 20ppm-2000ppm carbon monoxide
    // air quality-cases: < 200 perfect, 200 - 800 normal, > 800 - 1800 high, > 1800 abnormal
  
    if (MQ7sensorValue <= 200) 
    {
        Serial.println("Air-Quality: CO perfect");
        noTone(buzzer);
    }
    else if ((MQ7sensorValue > 200) || (MQ7sensorValue <= 800)) // || = or
    {
        Serial.println("Air-Quality: CO normal");
        noTone(buzzer);
    }
    else if ((MQ7sensorValue > 800) || (MQ7sensorValue <= 1800))
    {
        Serial.println("Air-Quality: CO high");
        tone(buzzer, 1000, 200);
    }
    else if (MQ7sensorValue > 1800) 
    {
        digitalWrite(blueLed, HIGH); // optical information in case of emergency
        Serial.println("Air-Quality: ALARM CO very high");
        delay(3000);
        digitalWrite(greenLed, LOW);
        tone(buzzer, 1000, 200);
    }
    else
    {
        Serial.println("MQ-7 - cant read any value - check the sensor!");
    }

    // Convert Humidity to string
    str_humid = String(event.relative_humidity);
    
    // Convert Temperature to string
    str_temp = String(event.temperature);
 
    // Combine Humidity and Temperature    
    
    str_out = str_humid + "," + str_temp ;
    
    // Compose output character
    static char *msg = str_out.c_str();
    
    rf_driver.send((uint8_t *)msg, strlen(msg));
    rf_driver.waitPacketSent();
}
