#include <dht11.h>

#define DHT11PIN 30
#define DHT11_READING_INTERVALL 5000

class DHT11Sensor {
    public:
        DHT11Sensor();
        int getTemperature();
        int getHumidity();
        void update();

    private:
        unsigned long lastRead_;
        dht11 dht11_;
        void read();


};
