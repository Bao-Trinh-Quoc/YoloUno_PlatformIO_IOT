#include "temp_hum_monitor.h"
#include "global.h"

DHT20 dht20;
LiquidCrystal_I2C lcd(0x21, 16, 2);

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

            // Update global variables
            global_temp = temp;
            global_humi = humi;

            Serial.print("Temperature: ");
            Serial.print(temp);
            Serial.print(" °C, Humidity: ");
            Serial.print(humi);
            Serial.println(" %");

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

        vTaskDelay(2000);
    }
}