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
    //Images
    ////////////////////////////////////////////////////////////////////////////
    std::thread FrontThread(&ImageReader::Read, IMR, path+"/3d_images/1/left/", index::Front_image);
    //ClockManager
    // ///////////////////////////////////////////////////////////
    std::thread ClockManagerTread(&ClockManager::synct, CM);
    std::thread UITread(&MainWindow::updateData, UI);
    //Images
    // /////////////////////////////////////////////////////////////////////////
    std::thread BackThread(&ImageReader::Read, IMR, path+"/3d_images/3/left/", index::Back_image);
    std::thread LeftThread(&ImageReader::Read, IMR, path+"/3d_images/0/left/", index::Left_image);
    std::thread RigthThread(&ImageReader::Read, IMR, path+"/3d_images/2/left/", index::Rigth_image);
    // //GPS
    // /////////////////////////////////////////////////////////////////////
    std::thread GPSThread(&GPSReader::Read, GPSR, path+"/gps.csv", index::GPS);
    //Double
    /////////////////////////////////////////////////////////////////////
    std::thread SpeedThread(&DoubleReader::Read, DR, path+"/speed.csv", index::Speed);
    std::thread SteeringThread(&DoubleReader::Read, DR, path+"/steering.csv", index::Steering);
    std::thread BrakeThread(&DoubleReader::Read, DR, path+"/brake.csv", index::Brake);
    std::thread ThrottleThread(&DoubleReader::Read, DR, path+"/throttle.csv", index::Throttle);
    //UI
    /////////////////////////////////////////////////////////
    SpeedThread.join();
    SteeringThread.join();
    BrakeThread.join();
    ThrottleThread.join();
    FrontThread.join();
    LeftThread.join();
    BackThread.join();
    RigthThread.join();
    GPSThread.join();
    ClockManagerTread.join();
    UITread.join();
}