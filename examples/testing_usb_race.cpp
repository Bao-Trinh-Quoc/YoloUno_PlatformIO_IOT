#include <Arduino.h>
#include "led_blinky.h"
#include "neo_blinky.h"
#include "temp_hum_monitor.h"
#include "mainserver.h"

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  // Wait for USB Serial to be ready
  // unsigned long start = millis();
  // while (!Serial && millis() - start < 3000) {
  //   delay(10);  
  // }
  // delay(1000);
 
  // Store Serial status BEFORE USB is ready
  bool results[30];
  unsigned long times[30];
  
  for (int i = 0; i < 30; i++) {
    times[i] = millis();
    results[i] = Serial;  // Store true/false
    delay(100);
  }
  
  // Now wait for USB and print all stored results
  delay(500);
  
  Serial.println("\n===== SERIAL STATUS TEST =====");
  for (int i = 0; i < 30; i++) {
    Serial.printf("Time: %lu ms, Serial: %s\n", 
                  times[i], 
                  results[i] ? "true" : "false");
  }
  Serial.println("===============================\n");
  
  xTaskCreate(led_blinky, "Task LED Control", 2048, NULL, 2, NULL);
  xTaskCreate(neo_blinky, "Task Neo Blink", 2048, NULL, 2, NULL);
  // xTaskCreate(temp_hum_monitor, "Task TEMP HUMI Monitor", 2048, NULL, 2, NULL);
  xTaskCreate(main_server_task, "Task Main Server", 8192, NULL, 2, NULL);
}

void loop() {
  // Serial.println("Hello Custom Board");
  // delay(1000);
}

