#include <Arduino.h>
#include <Car.h>

Car *car = nullptr;

void setup()
{
    Serial.begin(9600);
    car = new Car();
    Serial.println("Setup completed");
}

void loop()
{
    car->update();
    delay(50);
}