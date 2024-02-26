
#include <Arduino.h>
#if defined(ESP8266)
#include <ESP8266WiFi.h>
#elif defined(ESP32)
#include <WiFi.h>
#endif

#include "wifi_info.h"
#include "humilddleware.h"

void wifi_connect() {
  WiFi.begin(SSID, PASSWORD);
  while (WiFi.status() != WL_CONNECTED) {
      delay(500);
      Serial.print("*");
  }

  Serial.print("\nIP address: ");
  Serial.println(WiFi.localIP());
}

void setup(void) {


  Serial.begin(9600);
  wifi_connect();
  Config config = {.duty_cicle = 60};
  start(config);
}

void loop() {
  Invocation invocation = {.op = PUBLISH,.tpc = "topico", .msg = "mensagem" };
  publish(invocation);


  delay(1000);
}

