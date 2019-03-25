// Include RadioHead Amplitude Shift Keying Library
#include <RH_ASK.h>
// Include dependant SPI Library 
#include <SPI.h> 
//#include <VirtualWire.h>
 
// Include DHT Libraries from Adafruit
// Dependant upon Adafruit_Sensors Library
#include "DHT.h";
 
// Define Constants
 
#define DHTPIN 7       // DHT-22 Output Pin connection
#define DHTTYPE DHT22   // DHT Type is DHT 22 (AM2302)
 
// Define Variables
 
float hum;    // Stores humidity value in percent
float temp;   // Stores temperature value in Celcius
float smoke; // Stores smoke value PPM
 
// Define output strings
 
String str_humid;
String str_temp;
String str_out;
String str_smoke;

int redLed = 9;
int greenLed = 11;
int buzzer = 10;
float smokeA0 = A5;
// Your threshold value
int sensorThres = 200;
 
// Create Amplitude Shift Keying Object
RH_ASK rf_driver;
 
// Initialize DHT sensor for normal 16mhz Arduino
DHT dht(DHTPIN, DHTTYPE);
 
void setup() {
 
  // Initialize ASK Object
  rf_driver.init();
  // Start DHT Sensor
  dht.begin();

  pinMode(redLed, OUTPUT);
  pinMode(greenLed, OUTPUT);
  pinMode(buzzer, OUTPUT);
  pinMode(smokeA0, INPUT);
 
}
 
void loop()
{
 
  delay(2000);  // Delay so DHT-22 sensor can stabalize
   
    smoke = analogRead(smokeA0);
    hum = dht.readHumidity();  // Get Humidity value
    temp= dht.readTemperature();  // Get Temperature value
    
    // Convert Humidity to string
    str_humid = String(hum);
    
    // Convert Temperature to string
    str_temp = String(temp);

    // Convert Smoke PPM to String 
    str_smoke = String(smoke) ; 
 
    // Combine Humidity and Temperature    
    
    str_out = str_humid + "," + str_temp + "," + str_smoke;
    
    // Compose output character
    static char *msg = str_out.c_str();
    
    rf_driver.send((uint8_t *)msg, strlen(msg));
    rf_driver.waitPacketSent();

    if (smoke > sensorThres)
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
  
}
