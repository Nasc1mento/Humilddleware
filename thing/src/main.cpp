#include <Arduino.h>
#include <WiFi.h>
#include <esp_http_client.h>
#include "wifi_info.h"
#include "humilddleware.h"

#define uS_TO_S_FACTOR                 1000000
#define HUMILDDLEWARE_BROKER_IP       "192.168.0.111"
#define HUMILDDLEWARE_BROKER_PORT      8889
#define MANAGING_SYSTEM_ADDRESS       "http://192.168.0.111"
#define MANAGING_SYSTEM_PORT           8080

unsigned int update_interval       = 10;
RTC_DATA_ATTR int sleep_counter    = 0;
char buf_from_mg[200];

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


int get_distance() {
  return random(0, 101);
}

esp_err_t _http_event_handler(esp_http_client_event_t *evt) {
    switch (evt->event_id) {
    case HTTP_EVENT_ON_DATA:
      strncpy(buf_from_mg, (char*)evt->data, evt->data_len);
      break;
    return ESP_OK;
    }
}

void check_adaptation() {
  if (!WiFi.isConnected()) {
      Serial.println("Reconectando ao Wi-Fi...");
      WiFi.reconnect();
      delay(1000);
    }

  esp_http_client_config_t config = {
    .url = MANAGING_SYSTEM_ADDRESS,
    .event_handler = _http_event_handler,
  };

  esp_http_client_handle_t client = esp_http_client_init(&config);
  esp_err_t ret = esp_http_client_perform(client);

  if (ret == ESP_OK) {
    sscanf(buf_from_mg, "%d", &update_interval);
  }

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
    // Invocation to_recv = listen("topico");
    // printf("OP:%i\nTPC:%s\nMSG:%s\n",to_recv.op, to_recv.tpc, to_recv.msg);
  }
  // check_adaptation();
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
