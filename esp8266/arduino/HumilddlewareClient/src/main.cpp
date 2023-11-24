#include <WiFi.h>
#include "ClientProxy.h"

const char ssid[] = "Fabi_MauricioWeb";
const char password[] = "19602019";

const char host[16] = "192.168.0.121";
uint16_t port = 4444;

ClientProxy cp;

void setup(void) {
    Serial.begin(112500);
    WiFi.begin(ssid, password);
    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print("*");
    }

    Serial.println("");
    Serial.println("WiFi connection Successful");
    Serial.print("The IP Address of ESP8266 Module is: ");
    Serial.print(WiFi.localIP());
    cp.connect(host, port);
}

void loop() {
    cp.subscribe("topic1"); // loop infinito
}