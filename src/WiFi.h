#include <Arduino.h>

#define WIFI_SSID "honor9a"
#define WIFI_PASS "12345678"

void ConnectWiFi() {
  delay(2000);
  Serial.begin(9600);
  Serial.println();
  WiFi.begin(WIFI_SSID, WIFI_PASS);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
    if (millis() > 15000) ESP.restart();
  }
  Serial.println("Connected");
}