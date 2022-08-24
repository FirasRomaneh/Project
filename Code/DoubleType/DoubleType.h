#pragma once
#include "Code/local/local.h"

class DoubleType : public Type{
    public:
        DoubleType(){
            
        }
        DoubleType(std::time_t TimeStamp, double data): Type(TimeStamp){
            this->data = data;
        }
        void setData(double data){
            this->data = data;
        }
        double getData(){
            return this->data;
        }
        std::time_t getTimeStamp() override{
            return TimeStamp;
        }
        void setTimeStamp(std::time_t TimeStamp) override{
            this->TimeStamp = TimeStamp;
        }
    private:
        double data;
};