#ifndef READER_H
#define READER_H

#include "Code/ClockManager/ClockManager.h"

class Reader{
    public:
        Reader(){
            
        }
        virtual void Read(std::string, int) = 0;
    protected:
        DataStore* DS = DataStore::getInstance();
        ClockManager* CM = ClockManager::getInstance(); 
};

#endif