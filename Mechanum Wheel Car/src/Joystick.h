#include <Arduino.h>

enum Axis {
    X_Axis,
    Y_Axis
};

enum Position {
    MIDDLE,
    TOP,
    RIGHT,
    BOTTOM,
    LEFT
};

class Joystick {
    public:
        Joystick();
        static Position getPositionByValue(Axis axis, int value);
        bool isInPosition(Position positionX, Position positionY);
        bool isCentered();
        bool hasPositionChanged();
        bool isButtonDown();
        Position getPositionX();
        Position getPositionY();
        void setPositionX(Position value);
        void setPositionY(Position value);
        void setButtonDown(bool isButtonDown);
        
    private:
        Position positionX_;
        Position positionY_;
        bool isButtonDown_;
        bool hasPositionXChanged_;
        bool hasPositionYChanged_;
};