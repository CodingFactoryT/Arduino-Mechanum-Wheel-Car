#include "DHT11Sensor.h"

DHT11Sensor::DHT11Sensor() : dht11_() {
    Serial.println("DHT11-Sensor initialized");
    lastRead_ = millis() - DHT11_READING_INTERVALL - 1;
}

int DHT11Sensor::getHumidity(){
    return dht11_.humidity;
}

int DHT11Sensor::getTemperature(){
    return dht11_.temperature;
}

void DHT11Sensor::read(){
    dht11_.read(DHT11PIN);
    lastRead_ = millis();
}

void DHT11Sensor::update(){
    if(lastRead_ + DHT11_READING_INTERVALL < millis()){
        read();
    }
}