#ifndef TYPE_H
#define TYPE_H

#include "local.h"

class Type{
    public:
        Type(){
            
        }
        Type(std::time_t TimeStamp){
            this->TimeStamp = TimeStamp;
        }
        std::time_t getTimeStamp(){
            return this->TimeStamp;
        }
        void setTimeStamp(std::time_t TimeStamp){
            this->TimeStamp = TimeStamp;
        }
    protected:
        std::time_t TimeStamp;
};

#endif
