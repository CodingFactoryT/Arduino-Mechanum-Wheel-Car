#define LIGHT_SENSOR_PIN A0
#define LIGHT_SENSOR_READING_INTERVALL 2000

class LightSensor
{
public:
    LightSensor();
    int getLightIntensity();
    void update();

private:
    unsigned long lastRead_;
    int lightIntensity_;
    void read();
};
