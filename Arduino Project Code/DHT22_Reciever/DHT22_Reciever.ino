#include <RH_ASK.h>
// Include dependant SPI Library 
#include <SPI.h> 

String str_humid;
String str_temp;
String str_analog;
String str_out;
 
// Create Amplitude Shift Keying Object
RH_ASK rf_driver;
 
void setup()
{

    // Initialize ASK Object
    rf_driver.init();
    // Setup Serial Monitor
    Serial.begin(9600);

  
}
 
void loop()
{
    // Set buffer to size of expected message
    uint8_t buf[11];
    uint8_t buflen = sizeof(buf);
    // Check if received packet is correct size
    if (rf_driver.recv(buf, &buflen))
    {
      
      // Message received with valid checksum
      // Get values from string
      
      // Convert received data into string
      str_out = String((char*)buf);
      
      // Split string into two values
      for (int i = 0; i < str_out.length(); i++) {
      if (str_out.substring(i, i+1) == ",") {
      str_humid = str_out.substring(0, i);
      str_temp = str_out.substring(i+1);
      break;
      }
    }
      
      // Print values to Serial Monitor
      Serial.print("Humidity: ");
      Serial.print(str_humid);
      Serial.print("  - Temperature: ");
      Serial.println(str_temp);
      Serial.print("  - Smoke(PPM: ");
      Serial.print(str_analog); 
               
    }
}
