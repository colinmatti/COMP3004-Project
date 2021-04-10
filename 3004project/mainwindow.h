#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "device.h"

#include <QApplication>
#include <QMainWindow>
#include <QStringListModel>
#include <QTimer>

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
    void on_onSkin_stateChanged(int checked);
    void on_powerButton_clicked();
    void on_rightButton_clicked();
    void on_timerStart();
    void on_upButton_clicked();

private:
    int countdown; // check
    QModelIndex currentSelectionIndex; // check
    Device device;
    QStringListModel* model; // check
    QTimer *timer; // check
    Ui::MainWindow *ui;

    void menuVisibility(View* menu);
    void offVisibility();
    void treatmentVisibility(View* treatmentView);
};

#endif // MAINWINDOW_H
