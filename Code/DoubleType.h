#include "local.h"

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
    private:
        double data;
};