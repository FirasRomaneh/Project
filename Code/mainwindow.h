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
    void updateData();
    
private:
    Ui::MainWindow *ui;
    DataStore* DS;
};
#endif // MAINWINDOW_H
