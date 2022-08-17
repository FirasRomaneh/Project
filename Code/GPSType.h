#include "local.h"

class GPSType : public Type{
    public:
        GPSType(){
            
        }
        GPSType(std::time_t TimeStamp, std::pair<double, double> data): Type(TimeStamp){
            this->data = data;
        }
        void setData(std::pair<double, double> data){
            this->data = data;
        }
        std::pair<double, double> getData(){
            return this->data;
        }
    private:
        std::pair<double, double> data;
};