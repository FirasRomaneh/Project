#include "ClockManager.h"

ClockManager* ClockManager::getInstance(){
    if(instance == nullptr){
        instance = new ClockManager();
    }
    return instance;
}

void ClockManager::setTS(std::time_t TS){
    TS_Mutex.lock();
    this->TS = TS;
    TS_Mutex.unlock();
}

std::time_t ClockManager::getTS(){
    TS_Mutex.lock();
    std::time_t SendTS = this->TS;
    TS_Mutex.unlock();
    return SendTS;
}

void ClockManager::synct(){
    DataStore* DS = DataStore::getInstance();
    while (true){
        auto T = DS->Read();
        auto Front = T.at(index::Front_image);
        if(Front.getTimeStamp() != ClockManager::getTS()){
            ClockManager::setTS(Front.getTimeStamp());
        }
    }
}

void ClockManager::start(){
    std::thread SYNC(&ClockManager::synct, this);
    SYNC.join();
}