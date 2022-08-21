#include "mainwindow.h"
#include "Code/ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    DS = DataStore::getInstance();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::updateData(){
    cv::Mat LastFrontImage;
    cv::Mat LastLeftImage;
    cv::Mat LastBackImage;
    cv::Mat LastRigthImage;
    cv::Mat image;
    std::pair<double,double> LastGPS;
    double LastSpeed = -10000000.015655298284;
    double LastBrake = -10000000.015655298284;
    double LastSteering = -10000000.015655298284;
    double LastThrottle = -10000000.015655298284;
    Type* N = nullptr;
    ImageType* A = nullptr;
    GPSType* D = nullptr;
    DoubleType* f = nullptr;
    extern int Work;
    while (Work){
        N = DS->Read(index::Front_image);
        if(N != nullptr){
            A = dynamic_cast<ImageType*>(N);
            image = A->getData();
            if(!image.empty()){
                if (!LastFrontImage.empty()){
                    if(image.data != LastFrontImage.data){
                        LastFrontImage = image;
                        cv::resize(image, image, cv::Size(700, 325), cv::INTER_LINEAR);
                        ui->Front->setPixmap(
                        QPixmap::fromImage(QImage(image.data, image.cols, image.rows, image.step, 
                        QImage::Format_RGB888)));
                        ui->Front->update();
                    }
                } else{
                    LastFrontImage = image;
                    cv::resize(image, image, cv::Size(700, 325), cv::INTER_LINEAR);
                    ui->Front->setPixmap(
                    QPixmap::fromImage(QImage(image.data, image.cols, image.rows, image.step, 
                    QImage::Format_RGB888)));
                    ui->Front->update();	
                }
            }
        }
        N = DS->Read(index::Back_image);
        if(N != nullptr){
            A = dynamic_cast<ImageType*>(N);
            image = A->getData();
            if(!image.empty()){
                if (!LastBackImage.empty()){
                    if(image.data != LastBackImage.data){
                        LastBackImage = image;
                        cv::resize(image, image, cv::Size(300, 325), cv::INTER_LINEAR);
                        ui->Back->setPixmap(
                        QPixmap::fromImage(QImage(image.data, image.cols, image.rows, image.step, 
                        QImage::Format_RGB888)));
                        ui->Back->update();	
                    }
                } else{
                    LastBackImage = image;
                    cv::resize(image, image, cv::Size(300, 325), cv::INTER_LINEAR);
                    ui->Back->setPixmap(
                    QPixmap::fromImage(QImage(image.data, image.cols, image.rows, image.step, 
                    QImage::Format_RGB888)));
                    ui->Back->update();	
                }
            }
        }
        N = DS->Read(index::Left_image);
        if(N != nullptr){
            A = dynamic_cast<ImageType*>(N);
            image = A->getData();
            if(!image.empty()){
                if (!LastLeftImage.empty()){
                    if(image.data != LastLeftImage.data){
                        LastLeftImage = image;
                        cv::resize(image, image, cv::Size(300, 325), cv::INTER_LINEAR);
                        ui->Left->setPixmap(
                        QPixmap::fromImage(QImage(image.data, image.cols, image.rows, image.step, 
                        QImage::Format_RGB888)));
                        ui->Left->update();	
                    }
                } else{
                    LastLeftImage = image;
                    cv::resize(image, image, cv::Size(300, 325), cv::INTER_LINEAR);
                    ui->Left->setPixmap(
                    QPixmap::fromImage(QImage(image.data, image.cols, image.rows, image.step, 
                    QImage::Format_RGB888)));
                    ui->Left->update();	
                }
            }
        }
        N = DS->Read(index::Rigth_image);
        if(N != nullptr){
            A = dynamic_cast<ImageType*>(N);
            image = A->getData();
            if(!image.empty()){
                if (!LastRigthImage.empty()){
                    if(image.data != LastRigthImage.data){
                        LastRigthImage = image;
                        cv::resize(image, image, cv::Size(300, 325), cv::INTER_LINEAR);
                        ui->Rigth->setPixmap(
                        QPixmap::fromImage(QImage(image.data, image.cols, image.rows, image.step, 
                        QImage::Format_RGB888)));
                        ui->Rigth->update();	
                    }
                } else{
                    LastRigthImage = image;
                    cv::resize(image, image, cv::Size(300, 325), cv::INTER_LINEAR);
                    ui->Rigth->setPixmap(
                    QPixmap::fromImage(QImage(image.data, image.cols, image.rows, image.step, 
                    QImage::Format_RGB888)));
                    ui->Rigth->update();	
                }
            }
        }
        N = DS->Read(index::GPS);
        if(N != nullptr){
            D = dynamic_cast<GPSType*>(N);
            auto GPSData = D->getData();
            if((GPSData.first != LastGPS.first) || (GPSData.second != LastGPS.second)){
                LastGPS.first = GPSData.first;
                LastGPS.second = GPSData.second;
                ui->GPSLabel->setText("  GPS: " + QString::number(GPSData.first) + ", " + QString::number(GPSData.second));
                ui->GPSLabel->update();	
            }
        }
        N = DS->Read(index::Speed);
        if(N != nullptr){
            f = dynamic_cast<DoubleType*>(N);
            auto SpeedData = f->getData();
            if(SpeedData != LastSpeed){
                LastSpeed = SpeedData;
                ui->SpeedLabel->setText("  Speed: " + QString::number(SpeedData));
                ui->SpeedLabel->update();	
            }
        }
        N = DS->Read(index::Steering);
        if(N != nullptr){
            f = dynamic_cast<DoubleType*>(N);
            auto SteeringData = f->getData();
            if(SteeringData != LastSteering){
                LastSteering = SteeringData;
                ui->SteeringLabel->setText("  Steering: " + QString::number(SteeringData));
                ui->SteeringLabel->update();	
            }
        }
        N = DS->Read(index::Brake);
        if(N != nullptr){
            f = dynamic_cast<DoubleType*>(N);
            auto BrakeData = f->getData();
            if(BrakeData != LastBrake){
                LastBrake = BrakeData;
                ui->BrakeLabel->setText("  Brake: " + QString::number(BrakeData));
                ui->BrakeLabel->update();	
            }
        }
        N = DS->Read(index::Throttle);
        if(N != nullptr){
            f = dynamic_cast<DoubleType*>(N);
            auto ThrottleData = f->getData();
            if(ThrottleData != LastThrottle){
                LastThrottle = ThrottleData;
                ui->ThrottleLabel->setText("  Throttle: " + QString::number(ThrottleData));
                ui->ThrottleLabel->update();	
            }
        }
    }
}