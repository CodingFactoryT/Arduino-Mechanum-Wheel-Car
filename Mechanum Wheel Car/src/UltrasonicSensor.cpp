#include "UltrasonicSensor.h"

UltrasonicSensor::UltrasonicSensor(int triggerPin, int echoPin, int maxDistance) : 
    ultrasonicSensor_(triggerPin, echoPin, maxDistance)
{
    distanceCM_ = 1000;
}

unsigned int UltrasonicSensor::getDistanceCM(){
    return distanceCM_;
}

void UltrasonicSensor::update(){
    if(lastRead_ + ULTRASONIC_READING_INTERVALL < millis()){
        distanceCM_ = read();
        lastRead_ = millis();
    }
}

unsigned long UltrasonicSensor::read(){
    return ultrasonicSensor_.ping_cm();
}