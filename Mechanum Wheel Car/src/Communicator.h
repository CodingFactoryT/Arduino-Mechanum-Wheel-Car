#include <Joystick.h>
#include <SPI.h>
#include <Mirf.h>
#include <MirfHardwareSpiDriver.h>

#define NRFCEPIN 49
#define NRFCSNPIN 53

#define PAYLOAD sizeof(uint8_t) * 10    //PAYLOAD is 10 uint_8 values
#define CHANNEL 76
#define CONNECTION_LOST_WARNING 500

class Communicator {
    public:
        Joystick joystick1_;
        Joystick joystick2_;

        Communicator();
        void send(uint8_t data[]);
        uint8_t* getReceivedData();
        unsigned long getSaveStopTimer();
        
    private:
        unsigned long saveStopTimer_;
        bool isDataReady();
        uint8_t receivedData_[PAYLOAD];
};