
#include <Arduino.h>
#if defined(ESP8266)
#include <ESP8266WiFi.h>
#elif defined(ESP32)
#include <WiFi.h>
#endif

#include "Humilddleware.h"

const char ssid[] = "Fabi_MauricioWeb";
const char password[] = "19602019";

void wifi_connect();

void setup(void) {
    Serial.begin(112500);
    wifi_connect();
    Humilddleware::connect("192.168.0.121", 4444);
}

void loop() {
    Humilddleware::proxy()->publish("topic1", "message1");
    delay(1000);
}

void wifi_connect() {
    WiFi.begin(ssid, password);
    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print("*");
    }

    Serial.print("\nIP address: ");
    Serial.println(WiFi.localIP());
}
    