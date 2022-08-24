#ifndef TYPE_H
#define TYPE_H

#include "Code/local/local.h"

class Type{
    public:
        Type(){
            
        }
        Type(std::time_t TimeStamp){
            this->TimeStamp = TimeStamp;
        }
        virtual std::time_t getTimeStamp() = 0;
        void setTimeStamp(std::time_t TimeStamp){
            this->TimeStamp = TimeStamp;
        }
    protected:
        std::time_t TimeStamp;
};

#endif
