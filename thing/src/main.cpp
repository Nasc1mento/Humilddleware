#include <Arduino.h>
#include <WiFi.h>
#include <esp_http_client.h>
#include "wifi_config.h"
#include "humilddleware.h"

#define uS_TO_S_FACTOR                 1000000
#define HUMILDDLEWARE_BROKER_IP       "192.168.0.111"
#define HUMILDDLEWARE_BROKER_PORT      8889
#define MANAGING_SYSTEM_ADDRESS       "http://192.168.0.111:8080/adaptation"

unsigned int duty_cycle                = 10;
RTC_DATA_ATTR int sleep_counter        = 0;
HC hc;

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
  do {
    hc = start(HUMILDDLEWARE_BROKER_IP, HUMILDDLEWARE_BROKER_PORT);
    delay(500);
    Serial.print("*");
  } while (hc.status != HUMILDDLEWARE_OK);
}


int get_distance() {
  return random(0, 101);
}

esp_err_t _http_event_handler(esp_http_client_event_t *evt) {
    switch (evt->event_id) {
    case HTTP_EVENT_ON_DATA:
      strncpy(buf_from_mg, (char*)evt->data, evt->data_len);
      break;
    };
    return ESP_OK;

}

void check_adaptation(const int distance) {
  if (!WiFi.isConnected()) {
      Serial.println("Reconectando ao Wi-Fi...");
      WiFi.reconnect();
      delay(1000);
    }

  char url[100];
  snprintf(url, sizeof(url), "%s?distance=%d", MANAGING_SYSTEM_ADDRESS, distance);

  esp_http_client_config_t config = {
    .url = url,
    .event_handler = _http_event_handler,
    
  };
  
  esp_http_client_handle_t client = esp_http_client_init(&config);
  esp_err_t ret = esp_http_client_perform(client);

  if (ret == ESP_OK) {
    sscanf(buf_from_mg, "%d", &duty_cycle); 
  }
  Serial.print("Duty_cicle: ");
  Serial.println(duty_cycle);
}

void execute() {
  Payload payload;

  struct tm timeinfo;
  time(&payload.timestamp);
  localtime_r(&payload.timestamp, &timeinfo);

  payload.distance = get_distance();

  char msg[MSG_LEN];
  uint8_t ret =  sprintf(msg, "/distance: %i, timestamp: %d/", payload.distance, payload.timestamp);

  if (ret > 0 && ret < MSG_LEN) {
    Invocation to_send = invocation("topico", msg);
    publish(&hc, &to_send);
  }
  check_adaptation(payload.distance);
}

void sleep() {
  ++sleep_counter;
  esp_sleep_enable_timer_wakeup(duty_cycle * uS_TO_S_FACTOR);
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
