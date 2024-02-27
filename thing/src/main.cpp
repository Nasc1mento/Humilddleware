#include <Arduino.h>
#include <WiFi.h>
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
  start("192.168.0.111", 8889, config);
}

void loop() {

  Invocation to_send = {.op = PUBLISH,.tpc = "topico", .msg = "mensagem"};
  publish(to_send);
  Invocation to_recv = get_message("topico");
  delay(1000);
}

