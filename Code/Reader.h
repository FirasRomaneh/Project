#ifndef READER_H
#define READER_H

#include "ClockManager.h"

class Reader{
    public:
        Reader();
        virtual void Read(std::string, int) = 0;
        virtual void start() = 0;
    protected:
        DataStore* DS = DataStore::getInstance();
        ClockManager* CM = ClockManager::getInstance(); 
};

#endif