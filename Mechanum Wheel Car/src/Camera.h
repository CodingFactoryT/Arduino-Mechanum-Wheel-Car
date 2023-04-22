#include <Servo.h>
#include <Arduino.h>

#define CAMERA_SERVOPIN 8
#define CAMERA_CENTERPOSITION 90

class Camera {
    public:
        Camera();
        void returnToCenter();
        void moveRight();
        void moveLeft();
        void setSpeed(int value);
        
    private:
        int speed_;
        Servo cameraServo_;
        double currentPosition_;
        void updatePosition(int value);
};