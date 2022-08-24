#include "Code/Reader/Reader.h"
#include "Code/GPSType/GPSType.h"


class GPSReader: public Reader{
    public:
        GPSReader(){
            
        }
        void Read(std::string, int) override;
};

