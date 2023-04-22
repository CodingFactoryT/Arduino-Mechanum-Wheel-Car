#include <Communicator.h>

Communicator::Communicator() {
    Mirf.cePin = NRFCEPIN;
    Mirf.csnPin = NRFCSNPIN; 
    Mirf.spi = &MirfHardwareSpi;
    Mirf.init();
    
    Mirf.setRADDR((byte *)"MCNR");
    Mirf.setTADDR((byte *)"MCNC");

    Mirf.payload = PAYLOAD;
    Mirf.channel = CHANNEL;
    Mirf.config();

    saveStopTimer_ = millis() - CONNECTION_LOST_WARNING;

    Serial.println("Communicator initialized");
    delay(1000);
}

void Communicator::send(uint8_t data[]){
    Mirf.send(data);
    while(Mirf.isSending());
}

uint8_t* Communicator::getReceivedData(){
    if(!isDataReady()){
        return receivedData_;
    }
    saveStopTimer_ = millis();
    Mirf.getData(receivedData_);
    return receivedData_;
}

bool Communicator::isDataReady(){
    return Mirf.dataReady();
}

unsigned long Communicator::getSaveStopTimer(){
    return saveStopTimer_;
}
