#include "Driver.h"

Driver::Driver(std::string path){
    this->path = path;
    //initialize the poniters.
    CM = ClockManager::getInstance();
    IMR = new ImageReader();
    GPSR = new GPSReader();
    DR = new DoubleReader();
    UI = new MainWindow();
    //show the MainWindow
    UI -> show();
}

void Driver::start(){
    //Create Thread of ClockManager
    std::thread ClockManagerThread(&ClockManager::synct, CM);
    //Create Thread of UI
    std::thread UIThread(&MainWindow::UIData, UI);
    /////////////////////////////////////////////////////////////
    //Create Thread of ImageReader to read FrontImage
    std::thread FrontThread(&ImageReader::Read, IMR, path+"/3d_images/1/left/", index::Front_image);
    ////////////////////////////////////////////////////////////////////////////
    //Create Thread of ImageReader to read BackImage
    std::thread BackThread(&ImageReader::Read, IMR, path+"/3d_images/3/left/", index::Back_image);
    ////////////////////////////////////////////////////////////////////////////
    ///Create Thread of ImageReader to read LeftImage
    std::thread LeftThread(&ImageReader::Read, IMR, path+"/3d_images/0/left/", index::Left_image);
    ////////////////////////////////////////////////////////////////////////////
    //Create Thread of ImageReader to read RigthImage
    std::thread RigthThread(&ImageReader::Read, IMR, path+"/3d_images/2/left/", index::Rigth_image);
    ////////////////////////////////////////////////////////////////////////////
    //Create Thread of GPSReader to read GPS Data
    std::thread GPSThread(&GPSReader::Read, GPSR, path+"/gps.csv", index::GPS);
    /////////////////////////////////////////////////////////////////////
    //Create Thread of DoubleReader to read Speed Data
    std::thread SpeedThread(&DoubleReader::Read, DR, path+"/speed.csv", index::Speed);
    /////////////////////////////////////////////////////////////////////
    //Create Thread of DoubleReader to read Steering Data
    std::thread SteeringThread(&DoubleReader::Read, DR, path+"/steering.csv", index::Steering);
    /////////////////////////////////////////////////////////////////////
    //Create Thread of DoubleReader to read Brake Data
    std::thread BrakeThread(&DoubleReader::Read, DR, path+"/brake.csv", index::Brake);
    /////////////////////////////////////////////////////////////////////
    //Create Thread of DoubleReader to read Throttle Data
    std::thread ThrottleThread(&DoubleReader::Read, DR, path+"/throttle.csv", index::Throttle);
    /////////////////////////////////////////////////////////////////////
    //wait the Threads of DoubleReader to finish.
    SpeedThread.join();
    SteeringThread.join();
    BrakeThread.join();
    ThrottleThread.join();
    //////////////////////////////////////////////////////////////////
    //wait the Threads of GPSReader to finish
    GPSThread.join();
    ///////////////////////////////////////////////////////////////////
    //wait the Threads of ImageReader to finish
    LeftThread.join();
    BackThread.join();
    RigthThread.join();
    FrontThread.join();
    ////////////////////////////////////////////////////////////////////
    //wait ClockManagerThread and UIThread to finish
    ClockManagerThread.join();
    UIThread.join();
}