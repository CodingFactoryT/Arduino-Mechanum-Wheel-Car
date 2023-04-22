#include <NewPing.h>

#define ULTRASONIC_READING_INTERVALL 100

class UltrasonicSensor {
    public:
        UltrasonicSensor(int triggerPin, int echoPin, int maxDistance);

        unsigned int getDistanceCM();
        void update();

    private:
        unsigned long distanceCM_;
        unsigned long lastRead_;
        
        NewPing ultrasonicSensor_;

        unsigned long read();
};