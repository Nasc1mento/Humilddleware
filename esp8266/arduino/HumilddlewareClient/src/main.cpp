#include <WiFi.h>
#include "ClientProxy.h"
#include "Configuration.h"

ClientProxy cp;

void setup(void) {
    Serial.begin(112500);
    WiFi.begin(ssid, password);
    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print("*");
    }

    Serial.print(WiFi.localIP());
    cp.connect(host, port);
}

void loop() {
    cp.subscribe("topic1");
}