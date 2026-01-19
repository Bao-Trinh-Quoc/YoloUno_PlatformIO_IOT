#include "led_blinky.h"

void led_blinky(void *pvParameters) {
    pinMode(LED_GPIO, OUTPUT); // Initialize LED pin
    int ledState = 0;
    while(1) {
        if (ledState == 0) {
            digitalWrite(LED_GPIO, HIGH); // Turn ON LED
        } else {
            digitalWrite(LED_GPIO, LOW); // Turn OFF LED
        }
        ledState = 1 - ledState;
        Serial.println("LED State Changed");
        vTaskDelay(500);
    }
}