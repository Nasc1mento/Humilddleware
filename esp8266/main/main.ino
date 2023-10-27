#include <ESP8266WiFi.h>
#include "ClientProxy.h"


const char *ssid = "";
const char *password = "";


const char *host = "192.168.0.117";
const char *port = "4444";

ClientProxy cp;

void setup(void)
{ 
  Serial.begin(9600);
  // Connect to WiFi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) 
  {
     delay(500);
     Serial.print("*");
  }
  
  Serial.println("");
  Serial.println("WiFi connection Successful");
  Serial.print("The IP Address of ESP8266 Module is: ");
  Serial.print(WiFi.localIP());
  cp.connect(host, port);
}

void loop() 
{
  cp.publish("topic1", "mensagem1");
  delay(1000);
}