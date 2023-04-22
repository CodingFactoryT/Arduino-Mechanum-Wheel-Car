#include <Car.h>

Car::Car() : 
    ultrasonicSensorFront_(ULTRASONIC_FRONT_TRIG, ULTRASONIC_FRONT_ECHO, ULTRASONIC_MAX_DISTANCE),
    ultrasonicSensorBack_(ULTRASONIC_BACK_TRIG, ULTRASONIC_BACK_ECHO, ULTRASONIC_MAX_DISTANCE),
    ultrasonicSensorLeft_(ULTRASONIC_LEFT_TRIG, ULTRASONIC_LEFT_ECHO, ULTRASONIC_MAX_DISTANCE),
    ultrasonicSensorRight_(ULTRASONIC_RIGHT_TRIG, ULTRASONIC_RIGHT_ECHO, ULTRASONIC_MAX_DISTANCE),
    camera_()
{
    initMotors();
    stopAllMotors();
    speed = 255;
    Serial.println("Car initialized");
}

void Car::initMotors(){
    pinMode(MOTOR_A_EN, OUTPUT);
    pinMode(MOTOR_A_IN1, OUTPUT);
    pinMode(MOTOR_A_IN2, OUTPUT);
    pinMode(MOTOR_B_EN, OUTPUT);
    pinMode(MOTOR_B_IN1, OUTPUT);
    pinMode(MOTOR_B_IN2, OUTPUT);
    pinMode(MOTOR_C_EN, OUTPUT);
    pinMode(MOTOR_C_IN1, OUTPUT);
    pinMode(MOTOR_C_IN2, OUTPUT);
    pinMode(MOTOR_D_EN, OUTPUT);
    pinMode(MOTOR_D_IN1, OUTPUT);
    pinMode(MOTOR_D_IN2, OUTPUT);
}

void Car::driveMotor(Motor motor, MotorDirection direction){
    bool in1 = LOW;
    bool in2 = LOW;
    
    if(direction == FORWARD) {
        in1 = HIGH;
        in2 = LOW;
    } else if (direction == REVERSE) {
        in1 = LOW;
        in2 = HIGH;
    }   //if none of the if-statements triggered, the direction is 
        //STOP and both pins are set to LOW as they were initialized

    if(direction == STOP) {
        speed = 0;
    }

    switch(motor){
        case MOTOR_A:
            analogWrite(MOTOR_A_EN, speed);
            if(in1 == HIGH) {   //prevents both pins from being HIGH by first writing the LOW Pin
                digitalWrite(MOTOR_A_IN2, in2);
            }

            digitalWrite(MOTOR_A_IN1, in1);
            digitalWrite(MOTOR_A_IN2, in2);
        break;

        case MOTOR_B:
            if(in1 == HIGH) {
                digitalWrite(MOTOR_B_IN2, in2);
            }

            analogWrite(MOTOR_B_EN, speed);
            digitalWrite(MOTOR_B_IN1, in1);
            digitalWrite(MOTOR_B_IN2, in2);
        break;

        case MOTOR_C:
            if(in1 == HIGH) {
                digitalWrite(MOTOR_C_IN2, in2);
            }

            analogWrite(MOTOR_C_EN, speed);
            digitalWrite(MOTOR_C_IN1, in1);
            digitalWrite(MOTOR_C_IN2, in2);
        break;

        case MOTOR_D:
            if(in1 == HIGH) {
                digitalWrite(MOTOR_D_IN2, in2);
            }
            
            analogWrite(MOTOR_D_EN, speed);
            digitalWrite(MOTOR_D_IN1, in1);
            digitalWrite(MOTOR_D_IN2, in2);
        break;
    }
}

void Car::updateMotorDirections(Joystick joystick1, Joystick joystick2){
    Position joy1X = joystick1.getPositionX();
    Position joy1Y = joystick1.getPositionY();
    Position joy2X = joystick2.getPositionX();
    Position joy2Y = joystick2.getPositionY();

    MotorDirection directionAandD = FORWARD;    //automatically handles state if joy2Y is TOP and joy2X is MIDDLE
    MotorDirection directionBandC = FORWARD;

    bool areAllJoysticksInMiddle = true;

    if(joystick2.hasPositionChanged()) {
        areAllJoysticksInMiddle = false;

        switch(joy2Y) {
            case TOP: {
                if(joy2X == LEFT) {
                    directionAandD = STOP;
                } else if(joy2X == RIGHT) {
                    directionBandC = STOP;
                }
                driveMotor(MOTOR_A, directionAandD);
                driveMotor(MOTOR_B, directionBandC);
                driveMotor(MOTOR_C, directionBandC);
                driveMotor(MOTOR_D, directionAandD);
            } break;

            case MIDDLE: {
                MotorDirection directionAandC = REVERSE;    //automatically handles state if joy2X is LEFT
                MotorDirection directionBandD = FORWARD;
                if(joy2X == RIGHT) {
                    directionAandC = FORWARD;
                    directionBandD = REVERSE;
                }
                driveMotor(MOTOR_A, directionAandC);
                driveMotor(MOTOR_B, directionBandD);
                driveMotor(MOTOR_C, directionAandC);
                driveMotor(MOTOR_D, directionBandD);
            } break;       

            case BOTTOM: {
                directionAandD = REVERSE;    //automatically handles state if joy2X is MIDDLE
                directionBandC = REVERSE;
                if(joy2X == LEFT) {
                    directionBandC = STOP;
                } else if(joy2X == RIGHT) {
                    directionAandD = STOP;
                }
                driveMotor(MOTOR_A, directionAandD);
                driveMotor(MOTOR_B, directionBandC);
                driveMotor(MOTOR_C, directionBandC);
                driveMotor(MOTOR_D, directionAandD);
            } break;

            case RIGHT: //fallthrough
            case LEFT:
                Serial.println("ERROR: Joystick´s y-axis has a value from the x-axis");
                break;
        }
    } else if(joystick1.hasPositionChanged()){
        areAllJoysticksInMiddle = false;

        if(joy1Y == MIDDLE) {
            directionAandD = REVERSE;    //automatically handles state if joy1X is LEFT
            directionBandC = FORWARD;
            if(joy1X == RIGHT) {
                directionAandD = FORWARD;
                directionBandC = REVERSE;
            }
            driveMotor(MOTOR_A, directionAandD);
            driveMotor(MOTOR_B, directionBandC);
            driveMotor(MOTOR_C, directionBandC);
            driveMotor(MOTOR_D, directionAandD);
        } 
    }

    if(joy1Y == TOP && joy1X == MIDDLE) {
        camera_.moveLeft();
    } else if(joy1Y == BOTTOM && joy1X == MIDDLE) {
        camera_.moveRight();
    }

    if(communicator_.joystick1_.isButtonDown()) {
        camera_.returnToCenter();
    }

    if(joystick1.isInPosition(MIDDLE, MIDDLE) && joystick2.isInPosition(MIDDLE, MIDDLE) && !areAllJoysticksInMiddle) {
        stopAllMotors();
        areAllJoysticksInMiddle = true;
    }
}

void Car::stopAllMotors(){
    driveMotor(MOTOR_A, STOP);
    driveMotor(MOTOR_B, STOP);
    driveMotor(MOTOR_C, STOP);
    driveMotor(MOTOR_D, STOP);
    Serial.println("All motors stopped");
}

void Car::update(){
    uint8_t* data = communicator_.getReceivedData();

    communicator_.joystick1_.setPositionX(Joystick::getPositionByValue(X_Axis, *data));
    communicator_.joystick1_.setPositionY(Joystick::getPositionByValue(Y_Axis, *(data + 1)));
    communicator_.joystick1_.setButtonDown(*(data + 2));
    communicator_.joystick2_.setPositionX(Joystick::getPositionByValue(X_Axis, *(data + 3)));
    communicator_.joystick2_.setPositionY(Joystick::getPositionByValue(Y_Axis, *(data + 4)));
    communicator_.joystick2_.setButtonDown(*(data + 5));
    speed = map(*(data + 6), 0, 255, 100, 255);

    camera_.setSpeed(*(data + 6));

    if(communicator_.getSaveStopTimer() + CONNECTION_LOST_WARNING > millis()) {     //check if the remote responded in the last 500 milliseconds
        updateMotorDirections(communicator_.joystick1_, communicator_.joystick2_);
    } else {
        stopAllMotors();
        Serial.println("NO DATA AVAILABLE");
    }

    sendSensorData();
}

void Car::sendSensorData() {
    uint8_t dataToSend[PAYLOAD];

    dht11Sensor_.update();
    ultrasonicSensorFront_.update();
    ultrasonicSensorRight_.update();
    ultrasonicSensorBack_.update();
    ultrasonicSensorLeft_.update();

    dataToSend[0] = ultrasonicSensorFront_.getDistanceCM();
    dataToSend[1] = ultrasonicSensorRight_.getDistanceCM();
    dataToSend[2] = ultrasonicSensorBack_.getDistanceCM();
    dataToSend[3] = ultrasonicSensorLeft_.getDistanceCM();
    dataToSend[4] = dht11Sensor_.getTemperature();
    dataToSend[5] = dht11Sensor_.getHumidity();

    communicator_.send(dataToSend);  

    /* Serial.print(dataToSend[0]);
    Serial.print("|");Serial.print(dataToSend[1]);
    Serial.print("|");Serial.print(dataToSend[2]);
    Serial.print("|");Serial.print(dataToSend[3]);
    Serial.print("|");Serial.print(dataToSend[4]);
    Serial.print("|");Serial.print(dataToSend[5]);
    Serial.print("|"); */
}