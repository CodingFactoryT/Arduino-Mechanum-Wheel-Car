#include <Display.h>
#include <CustomSymbols.h>

Display::Display() : lcd_(0x27,20,4) {
    lcd_.init();
    lcd_.backlight();

    drawCarSymbol();
    drawTemperatureSymbol();
    drawHumiditySymbol();
    drawLightbulbSymbol();

    *lastTemperature_ = 0;    //set values so the following update methods 
    *lastHumidity_ = 0;        //display the "--" symbol for each value
    *lastLightIntesity_ = 0;
    lastConnectionAvailable_ = true;    //has to be set to true the "!" is displayed in the beginning correctly

    isFrontSideCollisionWarningActive_ = false;
    isRightSideCollisionWarningActive_ = false;
    isBackSideCollisionWarningActive_ = false;
    isLeftSideCollisionWarningActive_ = false;
}

void Display::updateTemperature(uint8_t* value) {
    if(value == nullptr) {
        if(lastTemperature_ != nullptr) {
            lcd_.setCursor(17, 0);
            lcd_.print("--");
            lastTemperature_ = nullptr;
            Serial.println("TEMPERATURE UPDATED NULLPTR");
        }
        return;
    }

    if(*lastTemperature_ != *value) {
        String prevChars = *value < 10 ? " " : "";
        lcd_.setCursor(17, 0);
        lcd_.print(prevChars + String(*value));
        *lastTemperature_ = *value;
        //Serial.println("TEMPERATURE UPDATED VALUE");
    }
}

void Display::updateHumidity(uint8_t* value) {
    if(value == nullptr) {
        if(lastHumidity_ != nullptr) {
            lcd_.setCursor(17, 1);
            lcd_.print("--");
            lastHumidity_ = nullptr;
            Serial.println("HUMIDITY UPDATED NULLPTR");
        }
        return;
    }

    if(*lastHumidity_ != *value) {
        String prevChars = *value < 10 ? " " : "";
        lcd_.setCursor(17, 1);
        lcd_.print(prevChars + String(*value));
        *lastHumidity_ = *value;
        //Serial.println("HUMIDITY UPDATED VALUE");
    }
}

void Display::updateLightIntensity(uint8_t* value) {
    if(value == nullptr) {
        if(lastLightIntesity_ != nullptr) {
            lcd_.setCursor(17, 3);
            lcd_.print("---");
            lastLightIntesity_ = nullptr;
            Serial.println("LIGHTINTENSITY UPDATED NULLPTR");
        }
        return;
    }

    if(*lastLightIntesity_ != *value) {
        String prevChars = *value >= 100 ? "" : (*value >= 10 ? " " : "  ");
        lcd_.setCursor(17, 3);
        lcd_.print(prevChars + String(*value));
        *lastLightIntesity_ = *value;
        //Serial.println("LIGHTINTENSITY UPDATED VALUE");
    }
}

void Display::updateCollisionWarnings(uint8_t distanceFront, uint8_t distanceRight, uint8_t distanceBack, uint8_t distanceLeft) {
    updateCollisionWarning(distanceFront, FRONT);
    updateCollisionWarning(distanceRight, RIGHT);
    updateCollisionWarning(distanceBack, BACK);
    updateCollisionWarning(distanceLeft, LEFT);
}

void Display::updateCollisionWarning(uint8_t distance, CarSide carSide) {
    bool isCollisionWarningActive = distance < COLLISSION_WARNING_DISTANCE;

    switch(carSide) {
        case FRONT:
            if(isFrontSideCollisionWarningActive_ != isCollisionWarningActive) {
                lcd_.setCursor(1,0);
                lcd_.print(isCollisionWarningActive ? "--" : "  ");
                isFrontSideCollisionWarningActive_ = isCollisionWarningActive;
                Serial.println("FRONT_SIDECOLLISIONALARM UPDATED");
            }
            break;

        case RIGHT:
            if(isRightSideCollisionWarningActive_ != isCollisionWarningActive) {
                String symbolToPrint = isCollisionWarningActive ? "|" : " ";
                lcd_.setCursor(3,1);
                lcd_.print(symbolToPrint);
                lcd_.setCursor(3,2);
                lcd_.print(symbolToPrint);
                isRightSideCollisionWarningActive_ = isCollisionWarningActive;
                Serial.println("RIGHT_SIDECOLLISIONALARM UPDATED");            
            }
            break;

        case BACK:
            if(isBackSideCollisionWarningActive_ != isCollisionWarningActive) {
                lcd_.setCursor(1,3);
                lcd_.print(isCollisionWarningActive ? "--" : "  ");
                isBackSideCollisionWarningActive_ = isCollisionWarningActive;
                Serial.println("BACK_SIDECOLLISIONALARM UPDATED");            
            }
            break;

        case LEFT:
            if(isLeftSideCollisionWarningActive_ != isCollisionWarningActive) {
                String symbolToPrint = isCollisionWarningActive ? "|" : " ";
                lcd_.setCursor(0,1);
                lcd_.print(symbolToPrint);
                lcd_.setCursor(0,2);
                lcd_.print(symbolToPrint);
                isLeftSideCollisionWarningActive_ = isCollisionWarningActive;
                Serial.println("LEFT_SIDECOLLISIONALARM UPDATED");            
            }
            break;
    }
}

void Display::drawTemperatureSymbol() {
    lcd_.createChar(0, temperature_symbol);
    lcd_.setCursor(16, 0);
    lcd_.write(0);
    lcd_.setCursor(19, 0);
    lcd_.print("C");
}

void Display::drawHumiditySymbol() {
    lcd_.createChar(1, humidity_symbol);
    lcd_.setCursor(16, 1);
    lcd_.write(1);
    lcd_.setCursor(19, 1);
    lcd_.print("%");
}

void Display::drawLightbulbSymbol() {
    lcd_.createChar(2, lightbulb_symbol);
    lcd_.setCursor(16,3);
    lcd_.write(2);
}

void Display::drawCarSymbol() {
    lcd_.createChar(3, car_symbol_top_left);
    lcd_.setCursor(1,1);
    lcd_.write(3);

    lcd_.createChar(4, car_symbol_top_right);
    lcd_.setCursor(2,1);
    lcd_.write(4);

    lcd_.createChar(5, car_symbol_bottom_left);
    lcd_.setCursor(1,2);
    lcd_.write(5);

    lcd_.createChar(6, car_symbol_bottom_right);
    lcd_.setCursor(2,2);
    lcd_.write(6);
}

void Display::updateConnectionLostWarning(bool isConnectionAvailable) {
    if(isConnectionAvailable && !lastConnectionAvailable_) {
        lcd_.setCursor(0,0);
        lcd_.print(" ");
        lastConnectionAvailable_ = true;
        Serial.println("CONNECTION AVAILABLE UPDATED");
    } else if(!isConnectionAvailable && lastConnectionAvailable_) {
        lcd_.setCursor(0,0);
        lcd_.print("!");

        updateTemperature(nullptr); //reset sensor values
        updateHumidity(nullptr);
        updateLightIntensity(nullptr);
        updateCollisionWarning(COLLISSION_WARNING_DISTANCE+1, FRONT);   //reset collision warning system
        updateCollisionWarning(COLLISSION_WARNING_DISTANCE+1, RIGHT);
        updateCollisionWarning(COLLISSION_WARNING_DISTANCE+1, BACK);
        updateCollisionWarning(COLLISSION_WARNING_DISTANCE+1, LEFT);
        
        lastConnectionAvailable_ = false;
        Serial.println("CONNECTION AVAILABLE UPDATED");
    }
}
