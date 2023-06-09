#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "device.h"

#include <QApplication>
#include <QMainWindow>
#include <QStringListModel>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_addButton_clicked();
    void on_clearButton_clicked();
    void on_deleteButton_clicked();
    void on_downButton_clicked();
    void on_goBackButton_clicked();
    void on_leftButton_clicked();
    void on_menuButton_clicked();
    void on_okButton_clicked();
    void on_onSkin_stateChanged();
    void on_powerButton_clicked();
    void on_rightButton_clicked();
    void on_timerStart();
    void on_upButton_clicked();
    void on_chargeBatteryButton_clicked();

private:
    Device* device;

    Ui::MainWindow *ui;

    void menuVisibility();
    void offVisibility();
    void treatmentVisibility(View* treatmentView);
};

#endif // MAINWINDOW_H
