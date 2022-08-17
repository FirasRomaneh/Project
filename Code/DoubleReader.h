#include "Reader.h"
#include "DoubleType.h"


class DoubleReader: public Reader{
    public:
        DoubleReader();
        void Read(std::string, int) override;
        void start() override;
};

