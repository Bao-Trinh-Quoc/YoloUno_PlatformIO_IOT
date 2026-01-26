#ifndef __GLOBAL_H__
#define __GLOBAL_H__
#include <Arduino.h>
#include <freertos/FreeRTOS.h>
#include <freertos/semphr.h>
#include <freertos/queue.h>

extern int global_var;
extern int led_state;

// Sensor data structure for queue communication
struct SensorData {
  float temperature;
  float humidity;
  unsigned long timestamp;
};

// RTOS Primitives
extern QueueHandle_t sensorDataQueue;           
extern SemaphoreHandle_t wifiConnectedSemaphore; 
// WiFi credentials
extern String ssid;
extern String password;
extern String wifi_ssid;
extern String wifi_password;

#define SENSOR_QUEUE_LENGTH 10
#define SENSOR_QUEUE_ITEM_SIZE sizeof(SensorData)

#endif