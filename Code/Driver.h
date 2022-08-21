#ifndef DRIVER_H
#define DRIVER_H

#include "GPSReader.h"
#include "ImageReader.h"
#include "DoubleReader.h"
#include "mainwindow.h"

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