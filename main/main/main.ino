#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h> 
 
ESP8266WebServer server(80);

const String agentType = "SHA-0.2.0";
bool relayState = true;
 
void setup() {
  Serial.begin(9600);
  WiFi.begin("hawaiinet1", "POK99MNB");
  pinMode(2, OUTPUT);
 
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
  }
 
  server.on("/", handleRootPath);   
  server.on("/api", handleApiPath);
  
  server.begin();                   
}
 
void loop() {
  server.handleClient();
}

void handleRootPath() {
  server.send(200, "text/plain", "Agent type: " + agentType  + " IP address: " + WiFi.localIP());
}

void handleApiPath() {
  relayState = !relayState;
  digitalWrite(2, relayState);

  const int state = relayState ? HIGH : LOW;
  const String stateOutput = relayState ? "on" : "off";
  
  server.send(200, "text/plain", stateOutput);
}

