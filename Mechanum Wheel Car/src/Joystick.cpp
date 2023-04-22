#include <Joystick.h>

Joystick::Joystick(){
    setPositionX(MIDDLE);
    setPositionY(MIDDLE);
    hasPositionXChanged_ = false;
    hasPositionYChanged_ = false;
}

Position Joystick::getPositionByValue(Axis axis, int value){
    if(value > 200){
        return axis == X_Axis ? LEFT : BOTTOM;
    }
    if(value < 60){
        return axis == X_Axis ? RIGHT : TOP;
    }

    return MIDDLE;
}

bool Joystick::isInPosition(Position positionX, Position positionY){
    return positionX_ == positionX && positionY_ == positionY;
}

bool Joystick::isCentered(){
    return positionX_ == MIDDLE && positionY_ == MIDDLE;
}

Position Joystick::getPositionX() {
    return positionX_;
}

Position Joystick::getPositionY(){
    return positionY_;
}

void Joystick::setPositionX(Position value){
    if(value == TOP || value == BOTTOM){
        return;
    }
    
    if(value != getPositionX()) {
        Serial.println("SET_X");
        hasPositionXChanged_ = true;
        positionX_ = value;
    } else {
        hasPositionXChanged_ = false;
    }
}

void Joystick::setPositionY(Position value){
    if(value == LEFT || value == RIGHT){
        return;
    }

    if(value != getPositionY()) {
        Serial.println("SET_Y");
        hasPositionYChanged_ = true;
        positionY_ = value;
    } else {
        hasPositionYChanged_ = false;
    }
}

bool Joystick::hasPositionChanged(){
    return hasPositionXChanged_ || hasPositionYChanged_;
}

bool Joystick::isButtonDown() {
    return isButtonDown_;
}

void Joystick::setButtonDown(bool isButtonDown) {
    isButtonDown_ = isButtonDown;
}

