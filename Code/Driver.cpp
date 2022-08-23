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
    //UI
    std::thread UIThread(&MainWindow::UIData, UI);
    std::thread UIUpdateThread(&MainWindow::UpdateUI, UI);
    /////////////////////////////////////////////////////////////
    //FrontImage
    std::thread FrontThread(&ImageReader::Read, IMR, path+"/3d_images/1/left/", index::Front_image);
    ////////////////////////////////////////////////////////////////////////////
    //BackImage
    std::thread BackThread(&ImageReader::Read, IMR, path+"/3d_images/3/left/", index::Back_image);
    ////////////////////////////////////////////////////////////////////////////
    //LeftImage
    std::thread LeftThread(&ImageReader::Read, IMR, path+"/3d_images/0/left/", index::Left_image);
    ////////////////////////////////////////////////////////////////////////////
    //RigthImage
    std::thread RigthThread(&ImageReader::Read, IMR, path+"/3d_images/2/left/", index::Rigth_image);
    ////////////////////////////////////////////////////////////////////////////
    //GPS
    std::thread GPSThread(&GPSReader::Read, GPSR, path+"/gps.csv", index::GPS);
    /////////////////////////////////////////////////////////////////////
    //Speed
    std::thread SpeedThread(&DoubleReader::Read, DR, path+"/speed.csv", index::Speed);
    /////////////////////////////////////////////////////////////////////
    //Steering
    std::thread SteeringThread(&DoubleReader::Read, DR, path+"/steering.csv", index::Steering);
    /////////////////////////////////////////////////////////////////////
    //Brake
    std::thread BrakeThread(&DoubleReader::Read, DR, path+"/brake.csv", index::Brake);
    /////////////////////////////////////////////////////////////////////
    //Throttle
    std::thread ThrottleThread(&DoubleReader::Read, DR, path+"/throttle.csv", index::Throttle);
    /////////////////////////////////////////////////////////////////////
    //Double Type
    SpeedThread.join();
    SteeringThread.join();
    BrakeThread.join();
    ThrottleThread.join();
    //////////////////////////////////////////////////////////////////
    //GPS
    GPSThread.join();
    ///////////////////////////////////////////////////////////////////
    //images
    LeftThread.join();
    BackThread.join();
    RigthThread.join();
    FrontThread.join();
    ////////////////////////////////////////////////////////////////////
    ClockManagerThread.join();
    UIUpdateThread.join();
    UIThread.join();
}