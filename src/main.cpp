#include <Arduino.h>
#include "led_blinky.h"
#include "neo_blinky.h"
#include "temp_hum_monitor.h"
#include "mainserver.h"
#include "tinyml.h"
#include "core_iot.h"
#include "global.h"

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  // Wait for USB Serial to be ready
  vTaskDelay(1000 / portTICK_PERIOD_MS);

  //  RTOS primitives
  sensorDataQueue = xQueueCreate(SENSOR_QUEUE_LENGTH, SENSOR_QUEUE_ITEM_SIZE);
  wifiConnectedSemaphore = xSemaphoreCreateBinary();
  
  if (sensorDataQueue == NULL || wifiConnectedSemaphore == NULL) {
    Serial.println("Failed to create RTOS primitives!");
    while(1); // Halt
  }
  
  Serial.println("RTOS primitives initialized successfully");

  xTaskCreate(led_blinky, "Task LED Control", 2048, NULL, 2, NULL);
  xTaskCreate(neo_blinky, "Task Neo Blink", 2048, NULL, 2, NULL);
  xTaskCreate(temp_hum_monitor, "Task TEMP HUMI Monitor", 4096, NULL, 2, NULL);
  xTaskCreate(main_server_task, "Task Main Server", 8192, NULL, 2, NULL);
  // xTaskCreate(tiny_ml_task, "Task TinyML", 2048, NULL, 2, NULL);
  xTaskCreate(coreiot_task, "Task CoreIOT MQTT", 4096, NULL, 2, NULL);
}

void loop() {
  // Serial.println("Hello Custom Board");
  // delay(1000);
}

