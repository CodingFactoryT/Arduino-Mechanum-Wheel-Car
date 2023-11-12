#include <Arduino.h>
#include <Communicator.h>
#include <DHT11Sensor.h>
#include <UltrasonicSensor.h>
#include <Camera.h>
#include <LightSensor.h>

#define MOTOR_A_EN 12
#define MOTOR_A_IN1 22
#define MOTOR_A_IN2 23

#define MOTOR_B_EN 11
#define MOTOR_B_IN1 25 // A  B
#define MOTOR_B_IN2 24 //
                       // C  D
#define MOTOR_C_EN 10
#define MOTOR_C_IN1 28
#define MOTOR_C_IN2 29

#define MOTOR_D_EN 9
#define MOTOR_D_IN1 27
#define MOTOR_D_IN2 26

#define ULTRASONIC_FRONT_TRIG 38
#define ULTRASONIC_FRONT_ECHO 39
#define ULTRASONIC_BACK_TRIG 42
#define ULTRASONIC_BACK_ECHO 43
#define ULTRASONIC_LEFT_TRIG 44
#define ULTRASONIC_LEFT_ECHO 45
#define ULTRASONIC_RIGHT_TRIG 40
#define ULTRASONIC_RIGHT_ECHO 41

#define ULTRASONIC_MAX_DISTANCE 100

#define LIGHT_SENSOR A0

enum Motor
{
    MOTOR_A,
    MOTOR_B,
    MOTOR_C,
    MOTOR_D
};

enum MotorDirection
{
    FORWARD,
    REVERSE,
    STOP
};

class Car
{
public:
    Communicator communicator_;
    UltrasonicSensor ultrasonicSensorFront_;
    UltrasonicSensor ultrasonicSensorBack_;
    UltrasonicSensor ultrasonicSensorLeft_;
    UltrasonicSensor ultrasonicSensorRight_;
    DHT11Sensor dht11Sensor_;
    Camera camera_;
    LightSensor lightSensor_;

    Car();
    void stopAllMotors();
    void update();

private:
    int speed;
    void updateMotorDirections(Joystick joystick1, Joystick joystick2);
    void initMotors();
    void driveMotor(Motor motor, MotorDirection direction);
    void sendSensorData();
};