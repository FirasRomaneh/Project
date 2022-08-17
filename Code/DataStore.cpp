#include "DataStore.h"

DataStore* DataStore::getInstance(){
    if(instance == nullptr){
        instance = new DataStore();
    }
    return instance;
}

void DataStore::Write(Type newdata, int index){
    AllData_Mutex.lock();
    AllData.at(index) = newdata;
    AllData_Mutex.unlock();
}

std::vector <Type> DataStore::Read(){
    AllData_Mutex.lock();
    std::vector <Type> SendData = AllData;
    AllData_Mutex.unlock();
    return SendData;
}

