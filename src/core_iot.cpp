#include "core_iot.h"

// ----------- CONFIGURE THESE! -----------
const char* coreIOT_Server = "app.coreiot.io";  
const char* coreIOT_Token = "149tqod7svz0sns23mhs";   // Device Access Token
const int   mqttPort = 1883;
// ----------------------------------------

WiFiClient espClient;
PubSubClient client(espClient);


void reconnect() {
  // Loop until we're reconnected
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    // Attempt to connect (username=token, password=empty)
    if (client.connect("IOT_DEVICE_1", coreIOT_Token, NULL)) {
      Serial.println("connected to CoreIOT!");
      client.subscribe("v1/devices/me/rpc/request/+");
      Serial.println("Subscribed to v1/devices/me/rpc/request/+");
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      delay(5000);
    }
  }
}


void callback(char* topic, byte* payload, unsigned int length) {
  Serial.print("Message arrived [");
  Serial.print(topic);
  Serial.println("] ");

  // Allocate a temporary buffer for the message
  char message[length + 1];
  memcpy(message, payload, length);
  message[length] = '\0';
  Serial.print("Payload: ");
  Serial.println(message);

  // Parse JSON
  StaticJsonDocument<256> doc;
  DeserializationError error = deserializeJson(doc, message);

  if (error) {
    Serial.print("deserializeJson() failed: ");
    Serial.println(error.c_str());
    return;
  }

  const char* method = doc["method"];
  if (strcmp(method, "setStateLED") == 0) {
    // Check params type (could be boolean, int, or string according to your RPC)
    // Example: {"method": "setValueLED", "params": "ON"}
    const char* params = doc["params"];

    if (strcmp(params, "ON") == 0) {
      Serial.println("Device turned ON.");
      //TODO

    } else {   
      Serial.println("Device turned OFF.");
      //TODO

    }
  } else {
    Serial.print("Unknown method: ");
    Serial.println(method);
  }
}


void setup_coreiot(){

  // Wait for WiFi connection using semaphore
  Serial.print("Waiting for WiFi connection...");
  while (xSemaphoreTake(wifiConnectedSemaphore, pdMS_TO_TICKS(100)) != pdTRUE) {
    Serial.print(".");
  }
  // Give back semaphore immediately to keep it available
  xSemaphoreGive(wifiConnectedSemaphore);
  Serial.println(" Connected!");

  client.setServer(coreIOT_Server, mqttPort);
  client.setCallback(callback);

}

void coreiot_task(void *pvParameters){

    setup_coreiot();

    while(1){

        if (!client.connected()) {
            reconnect();
        }
        client.loop();

        // Read latest sensor data from queue (peek without removing)
        SensorData latestData;
        if (xQueueReceive(sensorDataQueue, &latestData, 0) == pdTRUE) {
            // Sample payload, publish to 'v1/devices/me/telemetry'
            String payload = "{\"temperature\":" + String(latestData.temperature) + 
                           ",\"humidity\":" + String(latestData.humidity) + "}";
            
            client.publish("v1/devices/me/telemetry", payload.c_str());
            Serial.println("Published payload: " + payload);
        } else {
            Serial.println("No sensor data available in queue");
        }

        vTaskDelay(5000);  
    }
}