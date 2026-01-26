#include "temp_hum_monitor.h"
#include "global.h"

DHT20 dht20;
LiquidCrystal_I2C lcd(0x21, 16, 2);
SensorData data;

void temp_hum_monitor(void *pvParamaters) {
    Wire.begin(11, 12);
    dht20.begin();

    // Init LCD
    lcd.begin();
    lcd.backlight();
    lcd.clear();

    while (1) {
        int ret = dht20.read();
        if (ret == DHT20_OK) {
            float temp = dht20.getTemperature();
            float humi = dht20.getHumidity();

            data.temperature = temp;
            data.humidity = humi;
            data.timestamp = millis();

            // Send sensor data to queue
            if (xQueueSend(sensorDataQueue, &data, 0) != pdPASS) {
                Serial.println("Sensor queue full, data dropped");
            }
            Serial.printf("Temperature: %.2f °C, Humidity: %.2f %%\n", temp, humi);

            lcd.setCursor(0, 0);
            lcd.print("TEMP: ");
            lcd.print(temp);
            lcd.print(" C");

            lcd.setCursor(0, 1);
            lcd.print("HUM: ");
            lcd.print(humi);
            lcd.print(" %");

        } else {
            Serial.print("DHT20 Read Error: ");
            Serial.println(ret);
        }

        vTaskDelay(5000);
    }
}