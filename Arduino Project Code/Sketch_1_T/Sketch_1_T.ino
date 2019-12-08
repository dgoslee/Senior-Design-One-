// Include RadioHead Amplitude Shift Keying Library
#include <RH_ASK.h> 
#include <SPI.h>  
#include "DHT.h";

#define DHTPIN 7       // DHT-22 Output 
#define DHTTYPE DHT22   // DHT Type

float redLED = 3; // red LED pin
float greenLED = 2; // green LED pin
float buzzer = 4; //Piezo Buzzer pin 
float hum;    // Stores humidity value in percent
float temp;   // Stores temperature value in Celcius
float smokeA0 = A5 ; // Stores Smoke value in PPM 
float co = A2 ;  // Stores CO value in PPM
float MQ2_Thresh = 500; // MQ-2 Threshold
float MQ7_Thresh = 900; // MQ-7 Thresholdc
float ID;

String str_humid ;
String str_temp ;
String str_smoke ;
String str_co ; 
String str_ID ;
String str_out;
 
// Create Amplitude Shift Keying Object
RH_ASK rf_driver;
// Initialize DHT sensor for normal 16mhz Arduino
DHT dht(DHTPIN, DHTTYPE);
 
void setup() {
  // Initialize ASK Object
  rf_driver.init();
  dht.begin();

  pinMode(buzzer, OUTPUT);
  pinMode(redLED, OUTPUT);
  pinMode(greenLED,OUTPUT);
  pinMode(smokeA0, INPUT);
  pinMode(co, INPUT);
}
void loop()
{
    delay(2000); 
    hum = dht.readHumidity();  // Get Humidity value
    temp = dht.readTemperature();  // Get Temperature value
    float smoke =  analogRead(smokeA0) ; // Get Smoke value 
    float co = analogRead(A2) ; // Get CO value
    const float ID = 5                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                  .0;
    if (smoke > MQ2_Thresh || co > MQ7_Thresh) 
    {
      digitalWrite(redLED, HIGH); // Light Red LED
      digitalWrite(greenLED, LOW); // Delight Green LED
      tone(buzzer, 1000, 200); // Activate buzzer
    }
    else
    {
      digitalWrite(redLED, LOW); //Delight Red LED
      digitalWrite(greenLED, HIGH); //Light Green LED
      noTone(buzzer); //No buzzer Tone
    }
    // Assign String Values
    str_humid = String(hum);
    str_temp = String(temp);
    str_smoke = String(smoke); 
    str_co = String(co) ;
    str_ID = String(ID);
    // Combine Strings into single output string. 
    str_out = str_ID + "," + str_humid + "," + str_temp + "," + str_smoke + "," + str_co ;
    // Compose output character
    static char *msg = str_out.c_str();
    
    rf_driver.send((uint8_t *)msg, strlen(msg));
    rf_driver.waitPacketSent();
    
}
