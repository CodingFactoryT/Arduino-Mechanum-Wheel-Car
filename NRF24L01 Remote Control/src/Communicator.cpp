#include <Communicator.h>

Communicator::Communicator() {
    Mirf.cePin = NRFCEPIN;
    Mirf.csnPin = NRFCSNPIN; 
    Mirf.spi = &MirfHardwareSpi;
    Mirf.init();
    
    Mirf.setRADDR((byte *)"MCNC");
    Mirf.setTADDR((byte *)"MCNR");

    Mirf.payload = PAYLOAD;
    Mirf.channel = CHANNEL;
    Mirf.config();

    connectionLostTimer_ = millis()- CONNECTION_LOST_WARNING;
    for(int i = 0; i < sizeof(receivedData_) / sizeof(receivedData_[0]); i++) {
        receivedData_[i] = 0;
    }

    isConnectionAvailable_ = false;
}

void Communicator::send(uint8_t data[]){
    Mirf.send(data);
    while(Mirf.isSending());
}

uint8_t* Communicator::getReceivedData(){
    if(!isDataReady()){
        Serial.println("NO DATA AVAILABLE");
        return receivedData_;
    }
    connectionLostTimer_ = millis();
    Mirf.getData(receivedData_);
    return receivedData_;
}

bool Communicator::isDataReady(){
    return Mirf.dataReady();
}

unsigned long Communicator::getConnectionLostTimer(){
    return connectionLostTimer_;
}

uint8_t Communicator::getTemperature() {
    return *getReceivedData();
}

uint8_t Communicator::getHumidity() {
    return *(getReceivedData() + 1);
}

uint8_t Communicator::getUltrasonicSensorFront() {
    return *(getReceivedData() + 2);
}

uint8_t Communicator::getUltrasonicSensorRight() {
    return *(getReceivedData() + 3);
}

uint8_t Communicator::getUltrasonicSensorBack() {
    return *(getReceivedData() + 4);
}

uint8_t Communicator::getUltrasonicSensorLeft() {
    return *(getReceivedData() + 5);
}

void Communicator::printReceivedData(){
    Serial.print("[");
    for(int i = 0; i < 8; i++) {
        Serial.print(String(receivedData_[i]) + ",");
    }
    Serial.println("]");
}

bool Communicator::isConnectionAvailable(){
    return isConnectionAvailable_;
}

void Communicator::updateConnectionLost() {
    if(connectionLostTimer_ + CONNECTION_LOST_WARNING > millis()) {     //check if the remote responded in the last 500 milliseconds
        isConnectionAvailable_ = true;
    } else {
        isConnectionAvailable_ = false;
    }
}