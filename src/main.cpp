#include <Arduino.h>
//#include<Firebase_ESP_Client.h>
//#include "firebase.h"
//#include "addons/TokenHelper.h"
#include <WiFiMulti.h>

#define WIFI_SSID "Converge_2.4GHz_KcH9Sk"
#define WIFI_PASSWORD "GKkZKYKA"
//#define API_KEY "AIzaSyDUB8w_0fsAuj8kv3aJEqgErY5RtPobKUc"

const byte FLOW_SENSOR_PIN = 27;   // Connect sensor output to GPIO27 (you can change)
volatile int pulseCount = 0;
unsigned long oldTime = 0;

// For YF-S201: ~4.5 pulses/sec per L/min
float calibrationFactor = 4.5;  

// Threshold value
const float FLOW_THRESHOLD = 1.0; // L/min


void IRAM_ATTR pulseCounter() {
  pulseCount++;
}

WiFiMulti wifiMulti;

void setup() {
  Serial.begin(921600);
  pinMode(LED_BUILTIN, OUTPUT);

  wifiMulti.addAP(WIFI_SSID, WIFI_PASSWORD);

  while (wifiMulti.run() != WL_CONNECTED){
    delay(100);
  }
  Serial.println("Connected");

   pinMode(FLOW_SENSOR_PIN, INPUT_PULLUP);

  // Attach interrupt
  attachInterrupt(digitalPinToInterrupt(FLOW_SENSOR_PIN), pulseCounter, FALLING);

  Serial.println("ESP32 Water Flow Monitoring Started...");
 
}

void loop() {
  digitalWrite(LED_BUILTIN, WiFi.status() == WL_CONNECTED);



  unsigned long currentTime = millis();

  if (currentTime - oldTime > 5000) {   // update every 5 sec
    detachInterrupt(digitalPinToInterrupt(FLOW_SENSOR_PIN));

    float flowRate = ((1000.0 / (currentTime - oldTime)) * pulseCount) / calibrationFactor;

    oldTime = currentTime;
    pulseCount = 0;

    Serial.print("Flow Rate: ");
    Serial.print(flowRate, 2);
    Serial.println(" L/min");

    if (flowRate < FLOW_THRESHOLD) {
      Serial.println("⚠️ ALERT: Water flow below 1 L/min!");
      // You can also trigger LED/Buzzer/Send to Firebase here
    } else {
      Serial.println("✅ Flow is good.");
    }

    attachInterrupt(digitalPinToInterrupt(FLOW_SENSOR_PIN), pulseCounter, FALLING);
  }
}


