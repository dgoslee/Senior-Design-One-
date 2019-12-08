#include <RH_ASK.h>
#include <SPI.h> 

String str_ID;
String str_humid;
String str_temp;
String str_smoke;
String str_co;
String str_out;

 
// Create Amplitude Shift Keying Object
RH_ASK rf_driver(2000,12);
 
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
    uint8_t buf[30];
    uint8_t buflen = sizeof(buf);
    // Check if received packet is correct size
    if (rf_driver.recv(buf, &buflen))
      { 
      // Convert received data into string
      str_out = String((char*)buf);
      // Split string into two values
      for (int i = 0; i < str_out.length(); i++) {
      
        if (str_out.substring(i, i+1) == ",") {
        str_ID = str_out.substring(0,i);
        str_temp = str_out.substring(11,i+12);
        str_smoke = str_out.substring(17,i+19) ;
        str_co = str_out.substring(i+20);
        str_humid = str_out.substring(5,i+6);
        break;
          }
     
      }
      Serial.print(" ");
      Serial.print(str_ID);
      Serial.print(" ");
      Serial.print(str_humid);
      Serial.print(" ");
      Serial.print(str_temp);
      Serial.print(" "); 
      Serial.print(str_smoke) ;
      Serial.print(" "); 
      Serial.println(str_co) ;
      }   
}
    
