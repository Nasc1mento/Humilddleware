#include <Arduino.h>
#include <WiFi.h>
#include "wifi_info.h"
#include "humilddleware.h"

#define uS_TO_S_FACTOR                 1000000
#define HUMILDDLEWARE_BROKER_IP       "192.168.0.111"
#define HUMILDDLEWARE_BROKER_PORT      8889
#define MANAGING_SYSTEM_ADDRESS       "192.168.0.111"
#define MANAGING_SYSTEM_PORT           8080

unsigned int update_interval       = 10;
RTC_DATA_ATTR int sleep_counter    = 0;

struct Payload {
  unsigned int distance;
  time_t timestamp;
};

typedef struct Payload Payload;

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
  while ((start(HUMILDDLEWARE_BROKER_IP, HUMILDDLEWARE_BROKER_PORT)) != HUMILDDLEWARE_OK) {
    delay(500);
    Serial.print("*");
  }
}

void executor(int sleepTime){
  Serial.println(sleepTime);
  update_interval = sleepTime;
}

int get_distance() {
  return random(0, 101);
}

void execute() {
  Payload payload;

  struct tm timeinfo;
  time(&payload.timestamp);
  localtime_r(&payload.timestamp, &timeinfo);

  payload.distance = get_distance();

  char msg[MSG_LEN];
  uint8_t ret =  sprintf(msg, "{distance: %i, timestamp: %d}", payload.distance, payload.timestamp);

  if (ret > 0 && ret < MSG_LEN) {
    Invocation to_send = invocation("topico", msg);
    publish(to_send);
  
    Invocation to_recv = listen("topico");
    printf("OP:%i\nTPC:%s\nMSG:%s\n",to_recv.op, to_recv.tpc, to_recv.msg);
  }
}

void check_adaptation() {
  if (!WiFi.isConnected()) {
      Serial.println("Reconectando ao Wi-Fi...");
      WiFi.reconnect();
      delay(1000);
    }

    // TODO: Connect to managing system, get duty cycle and call executor
}

void sleep() {
  ++sleep_counter;
  esp_sleep_enable_timer_wakeup(update_interval * uS_TO_S_FACTOR);
  Serial.flush(); 
  esp_deep_sleep_start(); 
}

void setup() {
  Serial.begin(9600);
  Serial.setTimeout(2000);

  while(!Serial) { }

  wifi_connect();
  humilddleware_connect();

  execute();

  sleep();
  
}

void loop() {}
