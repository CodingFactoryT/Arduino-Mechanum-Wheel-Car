#include <Arduino.h>
#include <Display.h>

#define Joystick1X A3
#define Joystick1Y A2
#define Joystick1SW 8
#define Joystick2X A7
#define Joystick2Y A6
#define Joystick2SW 6
#define NRF24CE 9
#define NRF24CSN 10
#define Potentiometer A1
#define Buzzer A0
#define ModePin1 4
#define ModePin2 2
#define LED_R 3
#define LED_G 5
#define LED_B 7

enum CurrentMode {
    A,
    B,
    C
};

CurrentMode lastMode = A;
CurrentMode currentMode;
int pin1_mode = 0;
int pin2_mode = 0;

void updateMode(bool updateModeWithTone){
    pin1_mode = digitalRead(ModePin1);
    pin2_mode = digitalRead(ModePin2);

    if(pin1_mode == 0 && pin2_mode == 1) {
        currentMode = A;
    } else if(pin1_mode == 1 && pin2_mode == 0){
        currentMode = B;

    } else {
        currentMode = C;

    }

    if(lastMode != currentMode) {
        if(updateModeWithTone) {
            tone(Buzzer, 600, 125);
        }
        lastMode = currentMode;
    }
}

Communicator* communicator = nullptr;
Display* display = nullptr;

void setup() {
    Serial.begin(9600);
    pinMode(LED_R, OUTPUT);
    digitalWrite(LED_R, HIGH); 

    //tone(Buzzer, 600, 125);

    communicator = new Communicator();
    display = new Display();

    pinMode(Joystick1X, INPUT);
    pinMode(Joystick1Y, INPUT);
    pinMode(Joystick1SW, INPUT_PULLUP);
    pinMode(Joystick2X, INPUT);
    pinMode(Joystick2Y, INPUT);
    pinMode(Joystick2SW, INPUT_PULLUP);
    pinMode(Potentiometer, INPUT);
    pinMode(Buzzer, OUTPUT);
    pinMode(ModePin1, INPUT_PULLUP);
    pinMode(ModePin2, INPUT_PULLUP);
    pinMode(LED_G, OUTPUT);
    pinMode(LED_B, OUTPUT);

    //tone(Buzzer, 700, 125);
    delay(250);

    digitalWrite(LED_R, LOW);
    analogWrite(LED_G, 32);

    updateMode(false);

    //tone(Buzzer, 800, 125);
    delay(125);
    noTone(Buzzer);
}

void loop() {
    updateMode(true);
    uint8_t dataToSend[PAYLOAD];
    
    dataToSend[0] = analogRead(Joystick1X) / 4;
    dataToSend[1] = analogRead(Joystick1Y) / 4;
    dataToSend[2] = 1 - digitalRead(Joystick1SW);
    dataToSend[3] = analogRead(Joystick2X) /4;
    dataToSend[4] = analogRead(Joystick2Y) /4;
    dataToSend[5] = 1 - digitalRead(Joystick2SW);
    dataToSend[6] = analogRead(Potentiometer) /4;
    dataToSend[7] = currentMode;

    communicator->send(dataToSend);
    delay(30);
    uint8_t* receivedData = communicator->getReceivedData();

    if(communicator->isConnectionAvailable()) {
        communicator->printReceivedData();
        display->updateCollisionWarnings(*receivedData, *(receivedData + 1), *(receivedData + 2), *(receivedData + 3));
        display->updateTemperature(receivedData + 4);
        display->updateHumidity(receivedData + 5);
        display->updateLightIntensity(receivedData + 6);
    }

    communicator->updateConnectionLost();
    display->updateConnectionLostWarning(communicator->isConnectionAvailable());

    delay(50);
}