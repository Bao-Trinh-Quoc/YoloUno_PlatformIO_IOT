#include "global.h"

// General purpose variables
int global_var = 0;
int led_state = 0;

// RTOS Primitives 
QueueHandle_t sensorDataQueue = NULL;
SemaphoreHandle_t wifiConnectedSemaphore = NULL;

// WiFi credentials
String ssid = "ESP32 Cutie";
String password = "12345678";
String wifi_ssid = "abcde";
String wifi_password = "123456789";