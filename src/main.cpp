#include <Arduino.h>
#include "Bot.h"
#include "WiFi.h"
#include "Sensors.h"

bool Default = false;
float HumidityDefault, TemperatureDefault;
bool ActiveWater = false;
bool waterSensor;

void setup() {
  Serial.begin(9600);
  ConnectWiFi();

  bot.setChatID(1954532198);
  dht.begin(); 
  bot.sendMessage("Готов к работе");
}

void loop() {
  bot.tick();
  delay(2000);

  if(!Default){
    HumidityDefault = dht.readHumidity();
    TemperatureDefault = dht.readTemperature();
    Default = true;
  }

  GetTempAndHum(HumidityDefault, TemperatureDefault);
  WaterSensor();
  MoveSensor();
  FireSensor();
}


