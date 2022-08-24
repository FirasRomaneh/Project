#include "Code/Reader/Reader.h"
#include "Code/DoubleType/DoubleType.h"


class DoubleReader: public Reader{
    public:
        DoubleReader(){
            
        }
        void Read(std::string, int) override;
};

