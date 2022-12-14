#ifndef CLOCKMANAGER_H
#define CLOCKMANAGER_H

#include "Code/DataStore/DataStore.h"

class ClockManager{
    public:
        static ClockManager* getInstance();
        void setTS(std::time_t);
        std::time_t getTS();
        static ClockManager* instance;
        void synct();
    private:
        ClockManager(){
            TS = 0; //initialize TS
        }
        std::time_t TS;
        std::mutex TS_Mutex;
};

#endif