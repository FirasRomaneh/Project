#include "DataStore.h"

DataStore* DataStore::getInstance(){
    if(instance == nullptr){
        instance = new DataStore();
    }
    return instance;
}

void DataStore::Write(Type* newdata, int index){
    AllData_Mutex.lock();
    if(newdata != nullptr){ //if the pointer of the newData don't equal null, update the Data in DataStore
        AllData.at(index) = newdata;
    }
    AllData_Mutex.unlock();
}

Type* DataStore::Read(int index){
    AllData_Mutex.lock();
    Type* SendData = AllData.at(index);
    AllData_Mutex.unlock();
    return SendData;
}

