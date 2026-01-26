#ifndef __GLOBAL_H__
#define __GLOBAL_H__
#include <Arduino.h>

extern int global_var;
extern float global_temp;
extern float global_humi;
extern int led_state;

extern String ssid;
extern String password;
extern String wifi_ssid;
extern String wifi_password;
extern boolean isWifiConnected;

#endif