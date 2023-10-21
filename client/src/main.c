#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include <stdio.h>

void app_main() {
    for (;;) {
        printf("ESPinhos\n");
        vTaskDelay(1000 / portTICK_PERIOD_MS);
    }
}