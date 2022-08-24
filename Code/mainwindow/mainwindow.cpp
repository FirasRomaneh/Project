#include "mainwindow.h"
#include "Code/mainwindow/ui_mainwindow.h"
#include <unistd.h>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    DS = DataStore::getInstance();
    //connect The Signals and the Slots.
    connect(this, SIGNAL(SignalupdateFront(cv::Mat)), this, SLOT(updateFront(cv::Mat)), Qt::DirectConnection);
    connect(this, SIGNAL(SignalupdateBack(cv::Mat)), this, SLOT(updateBack(cv::Mat)), Qt::DirectConnection);
    connect(this, SIGNAL(SignalupdateLeft(cv::Mat)), this, SLOT(updateLeft(cv::Mat)), Qt::DirectConnection);
    connect(this, SIGNAL(SignalupdateRigth(cv::Mat)), this, SLOT(updateRigth(cv::Mat)), Qt::DirectConnection);
    connect(this, SIGNAL(SignalupdateGPS(std::pair<double, double>)), this, SLOT(updateGPS(std::pair<double, double>)), Qt::DirectConnection);
    connect(this, SIGNAL(SignalupdateSpeed(double)), this, SLOT(updateSpeed(double)));
    connect(this, SIGNAL(SignalupdateSteering(double)), this, SLOT(updateSteering(double)));
    connect(this, SIGNAL(SignalupdateBrake(double)), this, SLOT(updateBrake(double)));
    connect(this, SIGNAL(SignalupdateThrottle(double)), this, SLOT(updateThrottle(double)));
}

MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::UIData(){
    cv::Mat image;
    ImageType* A = nullptr;
    GPSType* G = nullptr;
    DoubleType* D = nullptr;
    extern int Work;
    while (Work){
        //Get pointer of Frontimage Data from Data Store
        A = dynamic_cast<ImageType*>(DS->Read(index::Front_image));
        if(A != nullptr){ //if the pointer is not nullptr, read Frontimage Mat
            image = A->getData(); 
            if(!image.empty()){ //if Mat is not Empty, compare it with LastFrontImage Mat, if not equal, 
                //update LastFrontImage Mat, and emit SignalupdateFront Signal to update QLabel of FrontImage. 
                if (!LastFrontImage.empty()){
                    if(!MatIsEqual(image, LastFrontImage)){
                        LastFrontImage = image.clone();
                        emit SignalupdateFront(image);
                    }
                } else{
                    LastFrontImage = image.clone();
                    emit SignalupdateFront(image);
                }
            }
        }
        //Get pointer of Backimage Data from Data Store
        A = dynamic_cast<ImageType*>(DS->Read(index::Back_image));
        if(A != nullptr){ //if the pointer is not nullptr, read Backimage Mat
            image = A->getData();
            if(!image.empty()){ //if Mat is not Empty, compare it with LastBackImage Mat, if not equal, 
                //update LastBackImage Mat, and emit SignalupdateBack Signal to update QLabel of BackImage. 
                if (!LastBackImage.empty()){
                    if(!MatIsEqual(image, LastBackImage)){
                        LastBackImage = image.clone();
                        emit SignalupdateBack(image);
                    }
                } else{
                    LastBackImage = image.clone();
                    emit SignalupdateBack(image);
                }
            }
        }
        //Get pointer of Leftimage Data from Data Store
        A = dynamic_cast<ImageType*>(DS->Read(index::Left_image));
        if(A != nullptr){ //if the pointer is not nullptr, read Leftimage Mat
            image = A->getData();
            if(!image.empty()){ //if Mat is not Empty, compare it with LastLeftImage Mat, if not equal, 
                //update LastLeftImage Mat, and emit SignalupdateLeft Signal to update QLabel of LeftImage. 
                if (!LastLeftImage.empty()){
                    if(!MatIsEqual(image, LastLeftImage)){
                        LastLeftImage = image.clone();
                        emit SignalupdateLeft(image);
                    }
                } else{
                    LastLeftImage = image.clone();
                    emit SignalupdateLeft(image);
                } 
            }
        }
        //Get pointer of Rigthimage Data from Data Store
        A = dynamic_cast<ImageType*>(DS->Read(index::Rigth_image));
        if(A != nullptr){ //if the pointer is not nullptr, read Rigthimage Mat
            image = A->getData();
            if(!image.empty()){ //if Mat is not Empty, compare it with LastRigthImage Mat, if not equal, 
                //update LastRigthImage Mat, and emit SignalupdateRigth Signal to update QLabel of RigthImage. 
                if (!LastRigthImage.empty()){
                    if(!MatIsEqual(image, LastRigthImage)){
                        LastRigthImage = image.clone();
                        emit SignalupdateRigth(image);
                    }
                } else{
                    LastRigthImage = image.clone();
                    emit SignalupdateRigth(image);
                }
            }
        }
        //Get pointer of GPS Data from Data Store
        G = dynamic_cast<GPSType*>(DS->Read(index::GPS));
        if(G != nullptr){ //if the pointer is not nullptr, read NewGPSData
            auto GPSData = G->getData();
            //compare NewGPSData with LastGPSData, if not equal, update LastGPSData, 
            //and emit SignalupdateGPS Signal to update QLabel of GPS. 
            if((GPSData.first != LastGPS.first) || (GPSData.second != LastGPS.second)){
                LastGPS.first = GPSData.first;
                LastGPS.second = GPSData.second;
                emit SignalupdateGPS(GPSData);
            }
        }
        //Get pointer of Speed Data from Data Store
        D = dynamic_cast<DoubleType*>(DS->Read(index::Speed));
        if(D != nullptr){ //if the pointer is not nullptr, read NewSpeedData
            auto SpeedData = D->getData();
            //compare NewSpeedData with LastSpeedData, if not equal, update LastSpeedData, 
            //and emit SignalupdateGPS Signal to update QLabel of Speed. 
            if(SpeedData != LastSpeed){
                LastSpeed = SpeedData;
                emit SignalupdateSpeed(SpeedData);
            }
        }
        //Get pointer of Steering Data from Data Store
        D = dynamic_cast<DoubleType*>(DS->Read(index::Steering));
        if(D != nullptr){ //if the pointer is not nullptr, read NewSteeringData
            auto SteeringData = D->getData();
            //compare NewSteeringData with LastSteeringData, if not equal, update LastSteeringData, 
            //and emit SignalupdateSteering Signal to update QLabel of Steering. 
            if(SteeringData != LastSteering){
                LastSteering = SteeringData;
                emit SignalupdateSteering(SteeringData);
            }
        }
        //Get pointer of Brake Data from Data Store
        D = dynamic_cast<DoubleType*>(DS->Read(index::Brake));
        if(D != nullptr){ //if the pointer is not nullptr, read NewBrakeData
            auto BrakeData = D->getData();
            //compare NewBrakeData with LastBrakeData, if not equal, update LastBrakeData, 
            //and emit SignalupdateBrake Signal to update QLabel of Brake. 
            if(BrakeData != LastBrake){
                LastBrake = BrakeData;
                emit SignalupdateBrake(BrakeData);
            }
        }
        //Get pointer of Throttle Data from Data Store
        D = dynamic_cast<DoubleType*>(DS->Read(index::Throttle));
        if(D != nullptr){ //if the pointer is not nullptr, read NewThrottleData
            auto ThrottleData = D->getData();
            //compare NewThrottleData with LastThrottleData, if not equal, update LastThrottleData, 
            //and emit SignalupdateThrottle Signal to update QLabel of Throttle. 
            if(ThrottleData != LastThrottle){
                LastThrottle = ThrottleData;
                emit SignalupdateThrottle(ThrottleData);
            }
        }    
    }
}

//Slot to Update QLabel of FrontIamge
void MainWindow::updateFront(cv::Mat image){
    cv::resize(image, image, cv::Size(700, 325), cv::INTER_LINEAR);
    ui->Front->setPixmap(QPixmap::fromImage(QImage(image.data, image.cols, 
    image.rows, image.step, QImage::Format_RGB888)));
    ui->Front->update();
}

//Slot to Update QLabel of BackIamge
void MainWindow::updateBack(cv::Mat image){
    cv::resize(image, image, cv::Size(300, 325), cv::INTER_LINEAR);
    ui->Back->setPixmap(QPixmap::fromImage(QImage(image.data, image.cols, 
    image.rows, image.step, QImage::Format_RGB888)));
    ui->Back->update();
}

//Slot to Update QLabel of LeftIamge
void MainWindow::updateLeft(cv::Mat image){
    cv::resize(image, image, cv::Size(300, 325), cv::INTER_LINEAR);
    ui->Left->setPixmap(QPixmap::fromImage(QImage(image.data, image.cols, 
    image.rows, image.step, QImage::Format_RGB888)));
    ui->Left->update();
}

//Slot to Update QLabel of RigthIamge
void MainWindow::updateRigth(cv::Mat image){
    cv::resize(image, image, cv::Size(300, 325), cv::INTER_LINEAR);
    ui->Rigth->setPixmap(QPixmap::fromImage(QImage(image.data, image.cols, 
    image.rows, image.step, QImage::Format_RGB888)));
    ui->Rigth->update();
}

//Slot to Update QLabel of GPS
void MainWindow::updateGPS(std::pair<double, double> GPS){
    ui->GPSLabel->setText("  GPS: " + QString::number(GPS.first) + ", " + QString::number(GPS.second));
    ui->GPSLabel->update();	
}

//Slot to Update QLabel of Speed
void MainWindow::updateSpeed(double Speed){
    ui->SpeedLabel->setText("  Speed: " + QString::number(Speed));
    ui->SpeedLabel->update();	
}

//Slot to Update QLabel of Steering
void MainWindow::updateSteering(double Steering){
    ui->SteeringLabel->setText("  Steering: " + QString::number(Steering));
    ui->SteeringLabel->update();	
}

//Slot to Update QLabel of Brake
void MainWindow::updateBrake(double Brake){
    ui->BrakeLabel->setText("  Brake: " + QString::number(Brake));
    ui->BrakeLabel->update();	
}

//Slot to Update QLabel of Throttle
void MainWindow::updateThrottle(double Throttle){
    ui->ThrottleLabel->setText("  Throttle: " + QString::number(Throttle));
    ui->ThrottleLabel->update();	
}

//function to show if Mat Is Equal or no.
bool MainWindow::MatIsEqual(const cv::Mat mat1, const cv::Mat mat2){
    //treat two empty mat as identical as well
    if (mat1.empty() && mat2.empty())
        return true;
    //if dimensionality of two mat is not identical, these two mat is not identical
    if (mat1.cols != mat2.cols || mat1.rows != mat2.rows || mat1.dims != mat2.dims) 
        return false;

    cv::Mat diff; cv::Mat diff1color;
    cv::compare(mat1, mat2, diff, cv::CMP_NE);
    cv::cvtColor(diff, diff1color, cv::COLOR_BGRA2GRAY, 1);
    int nz = cv::countNonZero(diff1color);
    return (nz==0);
}