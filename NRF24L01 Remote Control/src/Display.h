#include <LiquidCrystal_I2C.h>
#include <Communicator.h>

#define COLLISSION_WARNING_DISTANCE 30

enum CarSide {
    FRONT,
    RIGHT,
    BACK,
    LEFT
};

class Display {
    public:
        Display();
        void updateTemperature(uint8_t* value);
        void updateHumidity(uint8_t* value);
        void updateLightIntensity(uint8_t* value);
        void updateCollisionWarnings(uint8_t distanceFront, uint8_t distanceRight, uint8_t distanceBack, uint8_t distanceLeft);
        void updateConnectionLostWarning(bool isConnectionAvailable);
    
    private:
        LiquidCrystal_I2C lcd_;
        uint8_t* lastTemperature_;
        uint8_t* lastHumidity_;
        uint8_t* lastLightIntesity_;
        bool lastConnectionAvailable_;
        bool isFrontSideCollisionWarningActive_;
        bool isRightSideCollisionWarningActive_;
        bool isBackSideCollisionWarningActive_;
        bool isLeftSideCollisionWarningActive_;

        void drawTemperatureSymbol();
        void drawHumiditySymbol();
        void drawLightbulbSymbol();
        void drawCarSymbol();
        void updateCollisionWarning(uint8_t distance, CarSide carSide);
};