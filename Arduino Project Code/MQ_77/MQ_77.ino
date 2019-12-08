#include <Adafruit_Sensor.h>
#include <DHT.h>
#include <DHT_U.h>  
#include <VirtualWire.h>

#define DHTPIN 2 // Defines pin number to which the sensor is connected
#define DHTType DHT22

int analogMQ7 = A2;      
int MQ7sensorValue = 0;   // value read from the sensor
int smokeA0 = A5;
int TX_PIN = 11 ; 
int TX_ID = 3 ; 
int temp ; 

DHT_Unified dht(DHTPIN, DHTType);

struct roverRemoteData// Data Structure 
{
int    TX_ID;      // Initialize a storage place for the outgoing TX ID
int    Sensor1Data;// Initialize a storage place for the first integar DHT11
//int    Sensor2Data;// Initialize a storage place for the Second integar that you wish to Send (Ultrasonic)  
int    Sensor3Data;// Initialize a storage place for the Third integar that you wish to Send  (Gas sensor)
//int    Sensor4Data;// Initialize a storage place for the Forth integar that you wish to Send  (PIR)
int    Sensor5Data;//Initialize a storage place for the Forth integar that you wish to Send (temperature)
int    Sensor6Data;//Initialize a storage place for the Forth integar that you wish to Send (humidity)

};

void setup() {

  dht.begin() ;
  sensor_t sensor;
  dht.temperature().getSensor(&sensor);
  
  pinMode(smokeA0, INPUT);
  pinMode(analogMQ7, INPUT);
  Serial.begin(9600);
  vw_setup(2000);// Setup and Begin communication over the radios at 2000bps( MIN Speed is 1000bps MAX 4000bps)
  vw_set_tx_pin(TX_PIN);// Set Tx Pin
  
}

void loop() {

  struct roverRemoteData payload;// In this section is where you would load the data that needs to be sent.
  
  // If you want to read a analog pin and transmit its value you can do it as follows by removing the "//" 
  payload.TX_ID = TX_ID; // Set the Radio Address
  
  int analogSensor0 = analogRead(smokeA0);
  int analogSensor1 = analogRead(analogMQ7) ; 
  sensors_event_t event;
  int chk = dht.temperature().getEvent(&event);
  payload.Sensor1Data=chk;
  payload.Sensor5Data=event.temperature;
  payload.Sensor6Data= event.relative_humidity;
  payload.Sensor3Data = analogSensor0 ;// MQ-2 sensor
   // payload.Sensor4Data =digitalRead(inputPin);//Gas sensor
  vw_send((uint8_t *)&payload, sizeof(payload)); // Send the data 
  vw_wait_tx();// Wait for all data to be sent 
  
} 
  
