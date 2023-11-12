#include "LightSensor.h"
#include <Arduino.h>

LightSensor::LightSensor()
{
    pinMode(LIGHT_SENSOR_PIN, INPUT);
    lastRead_ = millis() - LIGHT_SENSOR_READING_INTERVALL - 1;
    Serial.println("Light-Sensor initialized");
}

int LightSensor::getLightIntensity()
{
    return lightIntensity_;
}

void LightSensor::read()
{
    lightIntensity_ = map(analogRead(LIGHT_SENSOR_PIN), 0, 1023, 0, 255);
    lastRead_ = millis();
}

void LightSensor::update()
{
    if (millis() - lastRead_ > LIGHT_SENSOR_READING_INTERVALL)
    {
        read();
    }
}