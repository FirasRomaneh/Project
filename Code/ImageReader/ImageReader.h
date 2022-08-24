#include "Code/Reader/Reader.h"
#include "Code/ImageType/ImageType.h"


class ImageReader: public Reader{
    public:
        ImageReader(){
            
        }
        void Read(std::string, int) override;
};

