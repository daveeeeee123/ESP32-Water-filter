#include <Arduino.h>
//#include<Firebase_ESP_Client.h>
//#include "firebase.h"
//#include "addons/TokenHelper.h"
#include <WiFiMulti.h>

#define WIFI_SSID "Converge_2.4GHz_KcH9Sk"
#define WIFI_PASSWORD "GKkZKYKA"
//#define API_KEY "AIzaSyDUB8w_0fsAuj8kv3aJEqgErY5RtPobKUc"

WiFiMulti wifiMulti;

void setup() {
  Serial.begin(921600);
  pinMode(LED_BUILTIN, OUTPUT);

  wifiMulti.addAP(WIFI_SSID, WIFI_PASSWORD);

  while (wifiMulti.run() != WL_CONNECTED){
    delay(100);
  }
  Serial.println("Connected");
 
}

void loop() {
  digitalWrite(LED_BUILTIN, WiFi.status() == WL_CONNECTED);

}


