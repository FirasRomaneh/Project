#include "mainwindow.h"
#include "Code/mainwindow/ui_mainwindow.h"
#include <unistd.h>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    DS = DataStore::getInstance();
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
        A = dynamic_cast<ImageType*>(DS->Read(index::Front_image));
        if(A != nullptr){
            image = A->getData();
            if(!image.empty()){
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
        A = dynamic_cast<ImageType*>(DS->Read(index::Back_image));
        if(A != nullptr){
            image = A->getData();
            if(!image.empty()){
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
        A = dynamic_cast<ImageType*>(DS->Read(index::Left_image));
        if(A != nullptr){
            image = A->getData();
            if(!image.empty()){
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
        A = dynamic_cast<ImageType*>(DS->Read(index::Rigth_image));
        if(A != nullptr){
            image = A->getData();
            if(!image.empty()){
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
        G = dynamic_cast<GPSType*>(DS->Read(index::GPS));
        if(G != nullptr){
            auto GPSData = G->getData();
            if((GPSData.first != LastGPS.first) || (GPSData.second != LastGPS.second)){
                LastGPS.first = GPSData.first;
                LastGPS.second = GPSData.second;
                emit SignalupdateGPS(GPSData);
            }
        }

        D = dynamic_cast<DoubleType*>(DS->Read(index::Speed));
        if(D != nullptr){
            auto SpeedData = D->getData();
            if(SpeedData != LastSpeed){
                LastSpeed = SpeedData;
                emit SignalupdateSpeed(SpeedData);
            }
        }

        D = dynamic_cast<DoubleType*>(DS->Read(index::Steering));
        if(D != nullptr){
            auto SteeringData = D->getData();
            if(SteeringData != LastSteering){
                LastSteering = SteeringData;
                emit SignalupdateSteering(SteeringData);
            }
        }

        D = dynamic_cast<DoubleType*>(DS->Read(index::Brake));
        if(D != nullptr){
            auto BrakeData = D->getData();
            if(BrakeData != LastBrake){
                LastBrake = BrakeData;
                emit SignalupdateBrake(BrakeData);
            }
        }

        D = dynamic_cast<DoubleType*>(DS->Read(index::Throttle));
        if(D != nullptr){
            auto ThrottleData = D->getData();
            if(ThrottleData != LastThrottle){
                LastThrottle = ThrottleData;
                emit SignalupdateThrottle(ThrottleData);
            }
        }    
    }
}

void MainWindow::updateFront(cv::Mat image){
    cv::resize(image, image, cv::Size(700, 325), cv::INTER_LINEAR);
    ui->Front->setPixmap(QPixmap::fromImage(QImage(image.data, image.cols, 
    image.rows, image.step, QImage::Format_RGB888)));
    ui->Front->update();
}

void MainWindow::updateBack(cv::Mat image){
    cv::resize(image, image, cv::Size(300, 325), cv::INTER_LINEAR);
    ui->Back->setPixmap(QPixmap::fromImage(QImage(image.data, image.cols, 
    image.rows, image.step, QImage::Format_RGB888)));
    ui->Back->update();
}

void MainWindow::updateLeft(cv::Mat image){
    cv::resize(image, image, cv::Size(300, 325), cv::INTER_LINEAR);
    ui->Left->setPixmap(QPixmap::fromImage(QImage(image.data, image.cols, 
    image.rows, image.step, QImage::Format_RGB888)));
    ui->Left->update();
}

void MainWindow::updateRigth(cv::Mat image){
    cv::resize(image, image, cv::Size(300, 325), cv::INTER_LINEAR);
    ui->Rigth->setPixmap(QPixmap::fromImage(QImage(image.data, image.cols, 
    image.rows, image.step, QImage::Format_RGB888)));
    ui->Rigth->update();
}

void MainWindow::updateGPS(std::pair<double, double> GPS){
    ui->GPSLabel->setText("  GPS: " + QString::number(GPS.first) + ", " + QString::number(GPS.second));
    ui->GPSLabel->update();	
}

void MainWindow::updateSpeed(double Speed){
    ui->SpeedLabel->setText("  Speed: " + QString::number(Speed));
    ui->SpeedLabel->update();	
}

void MainWindow::updateSteering(double Steering){
    ui->SteeringLabel->setText("  Steering: " + QString::number(Steering));
    ui->SteeringLabel->update();	
}

void MainWindow::updateBrake(double Brake){
    ui->BrakeLabel->setText("  Brake: " + QString::number(Brake));
    ui->BrakeLabel->update();	
}

void MainWindow::updateThrottle(double Throttle){
    ui->ThrottleLabel->setText("  Throttle: " + QString::number(Throttle));
    ui->ThrottleLabel->update();	
}

bool MainWindow::MatIsEqual(const cv::Mat mat1, const cv::Mat mat2){
    // treat two empty mat as identical as well
    if (mat1.empty() && mat2.empty())
        return true;
    // if dimensionality of two mat is not identical, these two mat is not identical
    if (mat1.cols != mat2.cols || mat1.rows != mat2.rows || mat1.dims != mat2.dims) 
        return false;

    cv::Mat diff; cv::Mat diff1color;
    cv::compare(mat1, mat2, diff, cv::CMP_NE);
    cv::cvtColor(diff, diff1color, cv::COLOR_BGRA2GRAY, 1);
    int nz = cv::countNonZero(diff1color);
    return (nz==0);
}