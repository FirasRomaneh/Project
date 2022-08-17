#include "Reader.h"
#include "ImageType.h"


class ImageReader: public Reader{
    public:
        ImageReader();
        void Read(std::string, int) override;
        void start() override;
};

