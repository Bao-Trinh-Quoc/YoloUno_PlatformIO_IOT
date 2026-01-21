#include <Arduino.h>
#include "led_blinky.h"
#include "neo_blinky.h"
#include "temp_hum_monitor.h"
#include "mainserver.h"

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  // Wait for USB Serial to be ready
  delay(1000);

  xTaskCreate(led_blinky, "Task LED Control", 2048, NULL, 2, NULL);
  xTaskCreate(neo_blinky, "Task Neo Blink", 2048, NULL, 2, NULL);
  // xTaskCreate(temp_hum_monitor, "Task TEMP HUMI Monitor", 2048, NULL, 2, NULL);
  xTaskCreate(main_server_task, "Task Main Server", 8192, NULL, 2, NULL);
}

void loop() {
  // Serial.println("Hello Custom Board");
  // delay(1000);
}

