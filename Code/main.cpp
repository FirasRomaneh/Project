#include <iostream>
#include <qt5/QtWidgets/QApplication>
#include "Driver.h"
 #include "opencv2/opencv.hpp"

ClockManager* ClockManager::instance = nullptr;
DataStore* DataStore::instance = nullptr;

int Work = 1;

int main(int argc, char *argv[]){
    std::string path = "/home/firas/Desktop/sample_trip";
    // std::cout << "Enter The Path Of Files:  ";
    // std::cin >> path;
    QApplication a(argc, argv);
    Driver* GO = new Driver(path);
    std::thread Di(&Driver::start, GO);
    a.exec();
    Work = 0;
    Di.join();
    return 0;
}
