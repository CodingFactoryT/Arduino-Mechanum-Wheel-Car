#include <Camera.h>

Camera::Camera() {
    pinMode(CAMERA_SERVOPIN, OUTPUT);  
    cameraServo_.attach(CAMERA_SERVOPIN);
    returnToCenter();
    Serial.println("Camera initialized");
}

void Camera::moveRight() {
    updatePosition(currentPosition_ + speed_);
}

void Camera::moveLeft() {
    updatePosition(currentPosition_ - speed_);
}

void Camera::updatePosition(int value) {
    if (value < 0) {
		value = 0;
    } else if (value > 180) {
		value = 180;
    }

    if(currentPosition_ != value) {
        cameraServo_.write(value);
        currentPosition_ = value;
        delay(10);
    }
}

void Camera::returnToCenter() {
    if(currentPosition_ != CAMERA_CENTERPOSITION) {
        cameraServo_.write(CAMERA_CENTERPOSITION);
        currentPosition_ = CAMERA_CENTERPOSITION;
    }
}

void Camera::setSpeed(int value) {
    if(value < 0) {
        value = 0;
    } else if(value > 255) {
        value = 255;
    }

    speed_ = map(value, 0, 255, 1, 15);
}