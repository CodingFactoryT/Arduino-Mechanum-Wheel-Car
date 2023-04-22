#include <SPI.h>
#include <Mirf.h>
#include <MirfHardwareSpiDriver.h>

#define NRFCEPIN 9
#define NRFCSNPIN 10

#define PAYLOAD sizeof(uint8_t) * 10    //PAYLOAD is 10 uint_8 values
#define CHANNEL 76
#define CONNECTION_LOST_WARNING 500

class Communicator {
    public:
        Communicator();
        void send(uint8_t data[]);
        uint8_t* getReceivedData();
        unsigned long getConnectionLostTimer();
        uint8_t getTemperature();
        uint8_t getHumidity();
        uint8_t getUltrasonicSensorFront();
        uint8_t getUltrasonicSensorRight();
        uint8_t getUltrasonicSensorBack();
        uint8_t getUltrasonicSensorLeft();
        void printReceivedData();
        bool isConnectionAvailable();
        void updateConnectionLost();
    private:
        unsigned long connectionLostTimer_;
        bool isDataReady();
        bool isConnectionAvailable_;
        uint8_t receivedData_[PAYLOAD];
};