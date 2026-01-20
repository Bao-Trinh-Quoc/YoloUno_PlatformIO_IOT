#include <Arduino.h>
#include "led_blinky.h"
#include "neo_blinky.h"
#include "temp_hum_monitor.h"

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  xTaskCreate(led_blinky, "Task LED Control", 2048, NULL, 2, NULL);
  xTaskCreate(neo_blinky, "Task Neo Blink", 2048, NULL, 2, NULL);
  xTaskCreate(temp_hum_monitor, "Task TEMP HUMI Monitor", 2048, NULL, 2, NULL);
}

void loop() {
  // Serial.println("Hello Custom Board");
  // delay(1000);
}