
#include <Wire.h>
#include <ESP8266WiFi.h>
//#include <BlynkSimpleEsp8266.h>
#include "MAX30100_PulseOximeter.h"
//#include <SimpleTimer.h>
#include <ESP8266WiFi.h>
//#include <BlynkSimpleEsp8266.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x3F, 16, 2);

//char auth[] = "6497f4ca052e43e3817c1e7157926730";             // You should get Auth Token in the Blynk App.
char ssid[] = "Oneplus 10R";                                     // Your WiFi credentials.
char pass[] = "arkamanna";

#define REPORTING_PERIOD_MS     3000
//SimpleTimer timer;

PulseOximeter pox;
uint32_t tsLastReport = 0;

void onBeatDetected()
{
  ;
}

void setup()
{
  Serial.begin(9600);
  Wire.begin(D2, D1);
  lcd.init();
  lcd.backlight();
  lcd.setCursor(3, 0);
  lcd.print("Welcome To");
  lcd.setCursor(0, 1);
  lcd.print("JustDoElectronic");
  delay(3000);
  lcd.clear();
  lcd.setCursor(6, 0);
  lcd.print("IoT");
  lcd.setCursor(1, 1);
  lcd.print("Pulse Oximeter");
  delay(3000);
  lcd.clear();
  Serial.begin(115200);
//  Blynk.begin(auth, ssid, pass);
  Serial.print("Initializing pulse oximeter..");


  // Initialize the PulseOximeter instance
  // Failures are generally due to an improper I2C wiring, missing power supply
  // or wrong target chip
  if (!pox.begin()) {
    Serial.println("FAILED");
    for (;;);
  } else {
    Serial.println("SUCCESS");
    digitalWrite(1, HIGH);
  }
  pox.setIRLedCurrent(MAX30100_LED_CURR_24MA);

  // Register a callback for the beat detection
  pox.setOnBeatDetectedCallback(onBeatDetected);

//  timer.setInterval(1000L, getSendData);
}

void loop()
{

//  timer.run(); // Initiates SimpleTimer
//  Blynk.run();
  // Make sure to call update as fast as possible
  pox.update();
  if (millis() - tsLastReport > REPORTING_PERIOD_MS) {


    // to computer serial monitor
    Serial.print("BPM: ");
    Serial.print(pox.getHeartRate());
    //blue.println("\n");

    Serial.print("    SpO2: ");
    Serial.print(pox.getSpO2());
    Serial.print("%");
    Serial.println("\n");

    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("BPM: ");
    lcd.setCursor(10, 0);
    lcd.print(pox.getHeartRate());
    lcd.setCursor(0, 1);
    lcd.print("SpO2:");
    lcd.setCursor(10, 1);
    lcd.print(pox.getSpO2());
    lcd.setCursor(14, 1);
    lcd.print("%");

//    Blynk.virtualWrite(V2, pox.getHeartRate() );
//    Blynk.virtualWrite(V3, pox.getSpO2());

//    tsLastReport = millis();

  }

}

void getSendData()
{
  ;
}
