#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <qt5/QtWidgets/QMainWindow>
#include "DataStore.h"
#include "GPSType.h"
#include "ImageType.h"
#include "DoubleType.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void UIData();
    void UpdateUI();

private slots:
    void updateFront(cv::Mat);
    void updateBack(cv::Mat);
    void updateLeft(cv::Mat);
    void updateRigth(cv::Mat);
    void updateGPS(std::pair<double, double>);
    void updateSpeed(double);
    void updateSteering(double);
    void updateBrake(double);
    void updateThrottle(double);
    bool MatIsEqual(const cv::Mat, const cv::Mat);

signals:
    void SignalupdateFront(cv::Mat);
    void SignalupdateBack(cv::Mat);
    void SignalupdateLeft(cv::Mat);
    void SignalupdateRigth(cv::Mat);
    void SignalupdateGPS(std::pair<double, double>);
    void SignalupdateSpeed(double);
    void SignalupdateSteering(double);
    void SignalupdateBrake(double);
    void SignalupdateThrottle(double);

private:
    Ui::MainWindow *ui;
    DataStore* DS;
    cv::Mat LastFrontImage;
    cv::Mat LastBackImage;
    cv::Mat LastLeftImage;
    cv::Mat LastRigthImage;
    std::mutex FrontMutex;
    std::mutex BackMutex;
    std::mutex LeftMutex;
    std::mutex RigthMutex;
    std::pair<double,double> LastGPS;
    std::mutex GPSMutex;
    double LastSpeed = -10000000.015655298284;
    double LastSteering = -10000000.015655298284;
    double LastBrake = -10000000.015655298284;
    double LastThrottle = -10000000.015655298284;
    std::mutex SpeedMutex; 
    std::mutex SteeringMutex; 
    std::mutex BrakeMutex; 
    std::mutex ThrottleMutex;
};
#endif // MAINWINDOW_H
