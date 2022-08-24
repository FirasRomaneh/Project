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
    extern int Work;
    while (Work){
        auto Front = DS->Read(index::Front_image); //Get pointer of Frontimage Data from Data Store
        std::time_t NewTS; 
        if(Front != nullptr){ //if the pointer is not nullptr, read TS and Compare it with TS in ClockManager
            NewTS = Front->getTimeStamp();
            if(NewTS != ClockManager::getTS()){
                ClockManager::setTS(NewTS); //update the TS in ClockManager
            }
        }
    }
}