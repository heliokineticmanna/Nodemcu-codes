#include <CircularBuffer.h>
#include <MAX30100.h>
#include <MAX30100_BeatDetector.h>
#include <MAX30100_Filters.h>
#include <MAX30100_PulseOximeter.h>
#include <MAX30100_Registers.h>
#include <MAX30100_SpO2Calculator.h>

#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <StringSplitter.h>
#include "MAX30100_PulseOximeter.h"
//#define   BLYNK_PRINT Serial
//#include <Blynk.h>
#include <ESP8266WiFi.h>
//#include   <BlynkSimpleEsp8266.h>

LiquidCrystal_I2C lcd(0x3F,16,2); 
 
#include "Wire.h"

#define REPORTING_PERIOD_MS   3000

// PulseOximeter is the higher level interface to the sensor
// it   offers:
//  * beat detection reporting
//  * heart rate calculation
//   * SpO2 (oxidation level) calculation
//  3V3- Vin, GND-GND.
 
//char auth[] = "v60fhfJerBZAZzmYbwS2uSzs2Qvy6sjK";              // You should get Auth Token in the Blynk App.
char ssid[] = "Oneplus 10R";                                      // Your WiFi credentials.
char pass[] =   "arkamanna";
 
// Connections : SCL PIN - D1 , SDA PIN - D2 , INT PIN -   D0
PulseOximeter pox;
 
float BPM, SpO2;
uint32_t tsLastReport = 0;
   
// Callback (registered below) fired when a pulse is detected
 
void onBeatDetected()
{
     Serial.println("Beat!");
}
 
void setup()
{
    Serial.begin(115200);
    Wire.begin(D2, D1);
    lcd.init();                      // initialize the lcd 
    lcd.backlight();
     
    pinMode(16, OUTPUT);
//    Blynk.begin(auth, ssid, pass);
 
     Serial.print("Initializing Pulse Oximeter..");
    // Initialize the PulseOximeter   instance
    // Failures are generally due to an improper I2C wiring, missing   power supply
    // or wrong target chip
 
    if (!pox.begin()) {
         Serial.println("FAILED");
         lcd.print("FAILED");
        for(;;);
    } else {
        Serial.println("SUCCESS");
        lcd.print("Success");
        digitalWrite(1, HIGH);
        
     }

    // The default current for the IR LED is 50mA and it could be changed
     //   by uncommenting the following line. Check MAX30100_Registers.h for all   the
    //   available options.
    // pox.setIRLedCurrent(MAX30100_LED_CURR_7_6MA);

     // Register a callback for the beat detection
    pox.setOnBeatDetectedCallback(onBeatDetected);
   
}
 
void loop()
{
    pox.update();
//    Blynk.run();
 
     BPM = pox.getHeartRate();
    SpO2 = pox.getSpO2();
    
   if (millis()   - tsLastReport > REPORTING_PERIOD_MS)
    {
        Serial.print("Heart rate:");
        lcd.setCursor(0,0);  //col x row
        lcd.print("Heart Rate(BPM):");
        lcd.setCursor(0,1);
        lcd.print(BPM);
         Serial.print(BPM);
         delay(1000);
        Serial.print(" bpm / SpO2:");
        Serial.print(SpO2);
         Serial.println(" %");
         lcd.setCursor(0,0);  //col x row
        lcd.print("Oxygen Saturation:");
        lcd.setCursor(0,1);
        lcd.print(SpO2);
        lcd.print("%");
 
//        Blynk.virtualWrite(V7, BPM);
//         Blynk.virtualWrite(V8, SpO2);
 
        tsLastReport = millis();
     }
}
void getSendData()
{
  ;
}
