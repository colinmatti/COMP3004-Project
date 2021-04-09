#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#define NO_ERROR "***No error detected***"
#define ERROR_NO_SKIN "***ERROR: No skin detected***"
#define WARNING_LOW_BATT "***WARNING: Battery is low***"
#define WARNING_TREATMENT_RUNNING "***WARNING: treatment is currently running***"

#include "device.h"

#include <iostream>
#include <string>
#include <QApplication>
#include <QMainWindow>
#include <QStringListModel>
#include <QTimer>

using namespace std;

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_okButton_clicked();
    void on_powerButton_clicked();
    void on_downButton_clicked();
    void on_upButton_clicked();
    void on_rightButton_clicked();
    void on_leftButton_clicked();
    void on_goBackButton_clicked();
    void on_menuButton_clicked();
    void on_timerStart();
    void on_onSkin_stateChanged(int checked);
    void on_addButton_clicked();

private:
    int countdown;
    Device device;
    QModelIndex currentSelectionIndex;
    View* currentView;
    QStringListModel* model;
    QTimer *timer;
    Ui::MainWindow *ui;
    bool addHistory;

    void powerOnDevice();
    void powerOffDevice();
    void displayMainMenu();
    void treatmentEnded();

    void menuVisibility();
    void offVisibility();
    void treatmentVisibility();
};

#endif // MAINWINDOW_H
