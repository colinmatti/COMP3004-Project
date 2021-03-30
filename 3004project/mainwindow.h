#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStringListModel>
#include "device.h"
#include <QTimer>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
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

    void on_timer_start();

private:
    Ui::MainWindow *ui;
    QStringList *stringList;
    QStringList *empty;
    QStringListModel *model;
    QModelIndex currentIndex;
    Device device;
    QTimer *timer;
    // REPLACED WITH THERAPY TIMER
    int countdown;
};
#endif // MAINWINDOW_H
