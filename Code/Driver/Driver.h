#ifndef DRIVER_H
#define DRIVER_H

#include "Code/GPSReader/GPSReader.h"
#include "Code/ImageReader/ImageReader.h"
#include "Code/DoubleReader/DoubleReader.h"
#include "Code/mainwindow/mainwindow.h"

class Driver{
    public:
        Driver(std::string);
        void start();
    private:
        ClockManager* CM;
        ImageReader* IMR;
        GPSReader* GPSR;
        DoubleReader* DR;
        MainWindow* UI;
        std::string path;
};

#endif