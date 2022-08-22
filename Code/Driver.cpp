#include "Driver.h"

Driver::Driver(std::string path){
    this->path = path;
    CM = ClockManager::getInstance();
    IMR = new ImageReader();
    GPSR = new GPSReader();
    DR = new DoubleReader();
    UI = new MainWindow();
    UI -> show();
}

void Driver::start(){
    //ClockManager
    std::thread ClockManagerThread(&ClockManager::synct, CM);
    /////////////////////////////////////////////////////////////
    //FrontImage
    std::thread FrontThread(&ImageReader::Read, IMR, path+"/3d_images/1/left/", index::Front_image);
    std::thread UIFrontThread(&MainWindow::updateFront, UI);
    ////////////////////////////////////////////////////////////////////////////
    //BackImage
    std::thread BackThread(&ImageReader::Read, IMR, path+"/3d_images/3/left/", index::Back_image);
    std::thread UIBackThread(&MainWindow::updateBack, UI);
    ////////////////////////////////////////////////////////////////////////////
    //LeftImage
    std::thread LeftThread(&ImageReader::Read, IMR, path+"/3d_images/0/left/", index::Left_image);
    std::thread UILeftThread(&MainWindow::updateLeft, UI);
    ////////////////////////////////////////////////////////////////////////////
    //RigthImage
    std::thread RigthThread(&ImageReader::Read, IMR, path+"/3d_images/2/left/", index::Rigth_image);
    std::thread UIRigthThread(&MainWindow::updateRigth, UI);
    ////////////////////////////////////////////////////////////////////////////
    //GPS
    std::thread GPSThread(&GPSReader::Read, GPSR, path+"/gps.csv", index::GPS);
    std::thread UIGPSThread(&MainWindow::updateGPS, UI);
    /////////////////////////////////////////////////////////////////////
    //Speed
    std::thread SpeedThread(&DoubleReader::Read, DR, path+"/speed.csv", index::Speed);
    std::thread UISpeedThread(&MainWindow::updateSpeed, UI);
    /////////////////////////////////////////////////////////////////////
    //Steering
    std::thread SteeringThread(&DoubleReader::Read, DR, path+"/steering.csv", index::Steering);
    std::thread UISteeringThread(&MainWindow::updateSteering, UI);
    /////////////////////////////////////////////////////////////////////
    //Brake
    std::thread BrakeThread(&DoubleReader::Read, DR, path+"/brake.csv", index::Brake);
    std::thread UIBrakeThread(&MainWindow::updateBrake, UI);
    /////////////////////////////////////////////////////////////////////
    //Throttle
    std::thread ThrottleThread(&DoubleReader::Read, DR, path+"/throttle.csv", index::Throttle);
    std::thread UIThrottleThread(&MainWindow::updateThrottle, UI);
    /////////////////////////////////////////////////////////////////////
    //Double Type
    SpeedThread.join();
    UISpeedThread.join();
    SteeringThread.join();
    UISteeringThread.join();
    BrakeThread.join();
    UIBrakeThread.join();
    ThrottleThread.join();
    UIThrottleThread.join();
    //////////////////////////////////////////////////////////////////
    //GPS
    GPSThread.join();
    UIGPSThread.join();
    ///////////////////////////////////////////////////////////////////
    //images
    LeftThread.join();
    UILeftThread.join();
    BackThread.join();
    UIBackThread.join();
    RigthThread.join();
    UIRigthThread.join();
    FrontThread.join();
    UIFrontThread.join();
    ////////////////////////////////////////////////////////////////////
    ClockManagerThread.join();
}