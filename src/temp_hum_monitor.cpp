#include "temp_hum_monitor.h"
DHT20 dht20;

void temp_hum_monitor(void *pvParamaters) {
    Serial.begin(115200);
    Wire.begin(11, 12);
    dht20.begin();

    while (1) {
        int ret = dht20.read();
        if (ret == DHT20_OK) {
            float temp = dht20.getTemperature();
            float humi = dht20.getHumidity();
            Serial.print("Temperature: ");
            Serial.print(temp);
            Serial.print(" °C, Humidity: ");
            Serial.print(humi);
            Serial.println(" %");
        } else {
            Serial.print("DHT20 Read Error: ");
            Serial.println(ret);
        }

        vTaskDelay(2000);
    }
}