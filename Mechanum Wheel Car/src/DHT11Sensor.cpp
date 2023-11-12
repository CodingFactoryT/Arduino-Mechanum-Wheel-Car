#include "DHT11Sensor.h"

DHT11Sensor::DHT11Sensor() : dht11_()
{
    lastRead_ = millis() - DHT11_READING_INTERVALL - 1;
    Serial.println("DHT11-Sensor initialized");
}

int DHT11Sensor::getHumidity()
{
    return humidity_;
}

int DHT11Sensor::getTemperature()
{
    return temperature_;
}

void DHT11Sensor::read()
{
    dht11_.read(DHT11PIN);
    temperature_ = dht11_.temperature;
    humidity_ = dht11_.humidity;
    lastRead_ = millis();
}

void DHT11Sensor::update()
{
    if (millis() - lastRead_ > DHT11_READING_INTERVALL)
    {
        read();
    }
}