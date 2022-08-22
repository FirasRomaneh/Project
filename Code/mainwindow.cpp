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

void MainWindow::updateFront(){
    cv::Mat image;
    cv::Mat LastFrontImage;
    int indexFro = 0;
    Type* N = nullptr;
    ImageType* A = nullptr;
    extern int Work;
    while (Work){
        N = DS->Read(index::Front_image);
        if(N != nullptr){
            A = dynamic_cast<ImageType*>(N);
            image = A->getData();
            if(!image.empty()){
                if (!LastFrontImage.empty()){
                    if(!MatIsEqual(image, LastFrontImage)){
                        LastFrontImage = image.clone();
                        cv::resize(image, image, cv::Size(700, 325), cv::INTER_LINEAR);
                        ui->Front->setPixmap(
                        QPixmap::fromImage(QImage(image.data, image.cols, image.rows, image.step, 
                        QImage::Format_RGB888)));
                        ui->Front->update();
                        indexFro++;
                        std::cout << indexFro << std::endl;
                    }
                } else{
                    LastFrontImage = image.clone();
                    cv::resize(image, image, cv::Size(700, 325), cv::INTER_LINEAR);
                    ui->Front->setPixmap(
                    QPixmap::fromImage(QImage(image.data, image.cols, image.rows, image.step, 
                    QImage::Format_RGB888)));
                    ui->Front->update();
                    indexFro++;
                    std::cout << "Ftr" << std::endl;	
                }
            }
        }
    }
}

void MainWindow::updateBack(){
    cv::Mat image;
    cv::Mat LastBackImage;
    Type* N = nullptr;
    ImageType* A = nullptr;
    extern int Work;
    while (Work){
        N = DS->Read(index::Back_image);
        if(N != nullptr){
            A = dynamic_cast<ImageType*>(N);
            image = A->getData();
            if(!image.empty()){
                if (!LastBackImage.empty()){
                    if(!MatIsEqual(image, LastBackImage)){
                        LastBackImage = image.clone();
                        cv::resize(image, image, cv::Size(300, 325), cv::INTER_LINEAR);
                        ui->Back->setPixmap(
                        QPixmap::fromImage(QImage(image.data, image.cols, image.rows, image.step, 
                        QImage::Format_RGB888)));
                        ui->Back->update();	
                    }
                } else{
                    LastBackImage = image.clone();
                    cv::resize(image, image, cv::Size(300, 325), cv::INTER_LINEAR);
                    ui->Back->setPixmap(
                    QPixmap::fromImage(QImage(image.data, image.cols, image.rows, image.step, 
                    QImage::Format_RGB888)));
                    ui->Back->update();	
                }
            }
        }
    }
}

void MainWindow::updateLeft(){
    cv::Mat image;
    cv::Mat LastLeftImage;
    Type* N = nullptr;
    ImageType* A = nullptr;
    extern int Work;
    while (Work){
        N = DS->Read(index::Left_image);
        if(N != nullptr){
            A = dynamic_cast<ImageType*>(N);
            image = A->getData();
            if(!image.empty()){
                if (!LastLeftImage.empty()){
                    if(!MatIsEqual(image, LastLeftImage)){
                        LastLeftImage = image.clone();
                        cv::resize(image, image, cv::Size(300, 325), cv::INTER_LINEAR);
                        ui->Left->setPixmap(
                        QPixmap::fromImage(QImage(image.data, image.cols, image.rows, image.step, 
                        QImage::Format_RGB888)));
                        ui->Left->update();	
                    }
                } else{
                    LastLeftImage = image.clone();
                    cv::resize(image, image, cv::Size(300, 325), cv::INTER_LINEAR);
                    ui->Left->setPixmap(
                    QPixmap::fromImage(QImage(image.data, image.cols, image.rows, image.step, 
                    QImage::Format_RGB888)));
                    ui->Left->update();	
                }
            }
        }
    }
}

void MainWindow::updateRigth(){
    cv::Mat image;
    cv::Mat LastRigthImage;
    Type* N = nullptr;
    ImageType* A = nullptr;
    extern int Work;
    while (Work){
        N = DS->Read(index::Rigth_image);
        if(N != nullptr){
            A = dynamic_cast<ImageType*>(N);
            image = A->getData();
            if(!image.empty()){
                if (!LastRigthImage.empty()){
                    if(!MatIsEqual(image, LastRigthImage)){
                        LastRigthImage = image.clone();
                        cv::resize(image, image, cv::Size(300, 325), cv::INTER_LINEAR);
                        ui->Rigth->setPixmap(
                        QPixmap::fromImage(QImage(image.data, image.cols, image.rows, image.step, 
                        QImage::Format_RGB888)));
                        ui->Rigth->update();	
                    }
                } else{
                    LastRigthImage = image.clone();
                    cv::resize(image, image, cv::Size(300, 325), cv::INTER_LINEAR);
                    ui->Rigth->setPixmap(
                    QPixmap::fromImage(QImage(image.data, image.cols, image.rows, image.step, 
                    QImage::Format_RGB888)));
                    ui->Rigth->update();	
                }
            }
        }
    }
}

void MainWindow::updateGPS(){
    Type* N = nullptr;
    GPSType* D = nullptr;
    std::pair<double,double> LastGPS;
    extern int Work;
    while (Work){
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
    }
}

void MainWindow::updateSpeed(){
    double LastSpeed = -10000000.015655298284;
    Type* N = nullptr;
    DoubleType* f = nullptr;
    extern int Work;
    while (Work){
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
    }
}

void MainWindow::updateSteering(){
    double LastSteering = -10000000.015655298284;
    Type* N = nullptr;
    DoubleType* f = nullptr;
    extern int Work;
    while (Work){
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
    }
}

void MainWindow::updateBrake(){
    double LastBrake = -10000000.015655298284;
    Type* N = nullptr;
    DoubleType* f = nullptr;
    extern int Work;
    while (Work){
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
    }
    
}

void MainWindow::updateThrottle(){
    double LastThrottle = -10000000.015655298284;
    Type* N = nullptr;
    DoubleType* f = nullptr;
    extern int Work;
    while (Work){
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