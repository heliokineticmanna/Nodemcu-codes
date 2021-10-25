#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>


ESP8266WebServer server(80); // 80 is the port number

const char* ssid = "POCO X2";
const char* password = "cb089fe710fb";
const char* ssid1 = "Honor 7X_98DD";
const char* password1 = "e47447ef";


String ledon,ledoff,led1on,led1off;

void Redon()
{
  digitalWrite(4, HIGH);
  server.send(200, "text/html", ledon);
}

void Redoff()
{
  digitalWrite(4, LOW);
  server.send(200, "text/html", ledoff);
}

void yellowon()
{
  digitalWrite(14, HIGH);
  server.send(200, "text/html", led1on);
}

void yellowoff()
{
  digitalWrite(14, LOW);
  server.send(200, "text/html", led1off);
}

void setup() {

  Serial.begin(9600);
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED){
    delay(200);
    Serial.print("..");
    
  }
  Serial.println();
  Serial.println("NodeMCU is connected!");
  Serial.println(WiFi.localIP());

  server.on("/led1on", Redon);
  server.on("/led1off", Redoff);
  server.on("/led2on", yellowon);
  server.on("/led2off", yellowoff);

  server.begin();

  pinMode(14, OUTPUT);//D5
  pinMode(4, OUTPUT);//D2

  digitalWrite(14, LOW);
  digitalWrite(4, LOW);

}

void loop()
{
  server.handleClient();
  delay(1);
}
