#include<ESP8266WiFi.h>



WiFiClient client;
WiFiServer server(80); //80 is port number

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  WiFi.begin("POCO X2", "cb089fe710fb");
  while (WiFi.status() != WL_CONNECTED){
    delay(200);
    Serial.print("..");
  }
  Serial.println();
  Serial.println("NodeMCU is connected!");
  Serial.println(WiFi.localIP());
  server.begin();
  pinMode(LED_BUILTIN, OUTPUT);
  }


void loop() {
  client = server.available(); //Gets a client that is connected to the server and has data available for reading.
  if(client == 1){
    String request = client.readStringUntil('\n');
    Serial.println(request);
    request.trim(); // to remove garbage values
    digitalWrite(LED_BUILTIN, LOW);
    if(request == "GET /led%20on HTTP/1.1"){
      digitalWrite(LED_BUILTIN, LOW);
      
    }
    if(request == "GET /led%20off HTTP/1.1"){
      digitalWrite(LED_BUILTIN,HIGH);
         }

 }

}
