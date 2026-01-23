#include "led_blinky.h"
#include "global.h"


void led_blinky(void *pvParameters) {
    pinMode(LED_GPIO, OUTPUT); // Initialize LED pin
    
    while (1) {
        // digitalWrite(LED_GPIO, HIGH);
        // vTaskDelay(500 / portTICK_PERIOD_MS);
        // digitalWrite(LED_GPIO, LOW);
        // vTaskDelay(500 / portTICK_PERIOD_MS);
        digitalWrite(LED_GPIO, led_state);
    }
}