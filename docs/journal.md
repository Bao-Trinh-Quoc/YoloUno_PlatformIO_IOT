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

control the LED from webserver (maybe just need to do with the onboard led)

Make the webserver look better () (this is optional should do this when we have all the functions working)

