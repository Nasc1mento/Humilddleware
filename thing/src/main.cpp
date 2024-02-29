#include <Arduino.h>
#include <WiFi.h>
#include "wifi_info.h"
#include "humilddleware.h"

#define uS_TO_S_FACTOR 1000000  /* Conversion factor for micro seconds to seconds */
#define TIME_TO_SLEEP  10   

RTC_DATA_ATTR int bootCount = 0;

void wifi_connect() {
  WiFi.begin(SSID, PASSWORD);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print("*");
  }

  Serial.print("\nIP address: ");
  Serial.println(WiFi.localIP());
}

void humilddleware_connect() {
  Config config = {.duty_cicle = 60};
  while ((start("192.168.0.111", 8889)) != HUMILDDLEWARE_OK) {
    delay(500);
    Serial.print("*");
  }
}

void execute() {
  int distance = random(0, 101);
  char msg[30];
  sprintf(msg, "{distance: %i}", distance);
  Invocation to_send = invocation("topico", msg);
  publish(to_send);
  Invocation to_recv = listen("topico");
}

void setup() {
  Serial.begin(9600);
  Serial.setTimeout(2000);

  while(!Serial) { }

  ++bootCount;

  wifi_connect();
  humilddleware_connect();

  execute();


  esp_sleep_enable_timer_wakeup(TIME_TO_SLEEP * uS_TO_S_FACTOR);
  Serial.flush(); 
  esp_deep_sleep_start(); 
}

void loop() {}



