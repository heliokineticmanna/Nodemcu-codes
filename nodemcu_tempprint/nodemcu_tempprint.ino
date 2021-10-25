#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
#include <StringSplitter.h>

LiquidCrystal_I2C lcd(0x3F,16,2);  // set the LCD address to 0x27 for a 16 chars and 2 line display

const char *host = "api.thingspeak.com";
const int httpPort = 80;  
const char* url1 = "/apps/thinghttp/send_request?api_key=5YOYUUYPTIWTVEUN"; 
WiFiClient client;
HTTPClient http; 

String Temp;

void setup() 
{
  // put your setup code here, to run once:
  lcd.init();                      // initialize the lcd 
  lcd.backlight();
   
  Serial.begin(9600);
  WiFi.begin("POCO X2", "cb089fe710fb");
  while(WiFi.status() != WL_CONNECTED)
  {
    delay(200);
    Serial.print("..");
  }
  Serial.println();
  Serial.println("NodeMCU is connected!");
  Serial.println(WiFi.localIP());
}

void loop() 
{
  http.begin(client,host,httpPort,url1); 
  int httpCode = http.GET();
  String data = http.getString();
  Serial.println(httpCode);
  Serial.println("***************        Data Read        ***************");
  Serial.println(data);
  
  data.remove(0,100);
  data.remove(data.length()-16, data.length());
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Kolkata");
  lcd.setCursor(0,1);
  lcd.print("Temp: " + (String) data + " C");
  delay(3000);
  
}
