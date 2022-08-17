#include "Reader.h"
#include "GPSType.h"


class GPSReader: public Reader{
    public:
        GPSReader();
        void Read(std::string, int) override;
        void start() override;
};

