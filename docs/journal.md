# 19/1
Add LED, neoled and restructure project to use multiple files

# 20/1
add DHT and LCD 
Doesnt matter if you plug to I2C1 or I2C2, just need to set address correctly

the LCD has weird address 0x21 eventhough its 16x2

# 21/1

What to do:
display the realtime temp and hum to the webserver v 

control the LED from webserver (maybe just need to do with the onboard led)

Make the webserver look better () (this is optional should do this when we have all the functions working)

Symptom
Early Serial.println() output (e.g. WiFi IP) does not appear unless a delay is added after Serial.begin()

Bug Note: ESP32-S3 Native USB Race Condition
Device: ESP32-S3 (Yolo Uno) using Native USB.

Symptom: Serial prints in setup() (like WiFi IP) are missing from the monitor.

Failed Fix: while(!Serial) does not work.

Root Cause: The chip's internal USB stack reports Serial = true immediately (at ~175ms) because the device is ready. However, the PC takes 1–2 seconds to detect the USB and open the Serial Monitor. The board prints into the void during this gap.

Solution: Use delay(2000); at the start of setup() to force the board to wait for the PC to catch up.

# 23/1
display the realtime temp and hum to the webserver v 

control the LED from webserver (maybe just need to do with the onboard led) v

Make the webserver look better () (this is optional should do this when we have all the functions working)

# 24/1

Objective: 
run tinyML task v
figure out how to train AI on python for microcontroller (for researching purpose)

 Time Series Forecasting - "The Weather Station that Predicts"
Your current model detects errors (Anomalies). A forecasting model predicts the future.

The Idea: Feed the model the last 10 minutes of temperature history. The model outputs the predicted temperature for the next minute.
Application: Predictive AC control. If the model predicts the room is about to get too hot, turn on the specific LED (representing a fan) before it happens.
Hardware: Uses your existing DHT20 sensor.
Model Type: LSTM (Long Short-Term Memory) or GRU (Gated Recurrent Units), though typically simplified to Dense layers for microcontrollers.

# 26/1

Main task:
try to connect to coreiot throught MQTT -- done
but the web UI is horrible, so i need to fix it later

seems like when connect to mqtt it cannot in the AP mode anymore