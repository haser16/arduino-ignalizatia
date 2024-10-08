#include "Arduino.h"
#include "Bot.h"
#include "DHT.h"
#include "DHT_U.h"

#define DHTPIN D4
#define DHTTYPE DHT11

bool previousWaterState = false;
float previousHumidity = 0.0;
float previousTemperature = 0.0;
bool messageSent = false;
bool fireDetected = false; 

DHT dht(DHTPIN, DHTTYPE);

void GetTempAndHum(float humidityDefault, float temperatureDefault) {
    float currentHumidity = dht.readHumidity();
    float currentTemperature = dht.readTemperature();

    if (currentHumidity > humidityDefault && previousHumidity <= humidityDefault) {
        bot.sendMessage("❗️Возросла влажность❗️");
    } else if (currentHumidity <= humidityDefault && previousHumidity > humidityDefault) {
        bot.sendMessage("❕Влажность в норме❕");
    }
    previousHumidity = currentHumidity;

    if (currentTemperature > temperatureDefault && previousTemperature <= temperatureDefault) {
        bot.sendMessage("❗️Возросла температура❗️");
    } else if (currentTemperature <= temperatureDefault && previousTemperature > temperatureDefault) {
        bot.sendMessage("❕Температура в норме❕");
    }
    previousTemperature = currentTemperature;
}

bool WaterSensor() {
    int water = analogRead(A0);
    bool currentWaterState = water > 100;

    if (currentWaterState != previousWaterState) {
        if (currentWaterState) {
            bot.sendMessage("💧❗️Утечка воды❗️💧");
        } else {
            bot.sendMessage("💧❕Уровень воды в норме❕💧");
        }

        previousWaterState = currentWaterState;
    }

    return currentWaterState;
}

void MoveSensor() {
    int currentMoveState = digitalRead(D2);

    if (currentMoveState == HIGH && !messageSent) {
        bot.sendMessage("❗️Есть движение❗️");
        messageSent = true;
    } else if (currentMoveState == LOW) {
        messageSent = false;
    }
}

void FireSensor() {
    int FirePin = digitalRead(D3);

    if (!FirePin && !fireDetected) {
        bot.sendMessage("🔥❗️Огонь❗️🔥");
        fireDetected = true;
    } 
    else if (FirePin && fireDetected) {
        bot.sendMessage("🔥❕Огонь потух❕🔥");
        fireDetected = false;
    }
}