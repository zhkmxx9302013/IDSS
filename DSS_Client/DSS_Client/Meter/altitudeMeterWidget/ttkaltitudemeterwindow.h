#ifndef TTKALTITUDEMETERWINDOW_H
#define TTKALTITUDEMETERWINDOW_H


#include <QMainWindow>
#include "ttkglobaldefine.h"

namespace Ui {
class TTKAltitudeMeterWindow;
}

/*!
* @author   Greedysky <greedysky@163.com>
* @modifier Zhaozihe <zhkmxx930@buaa.edu.cn>
* @desc     Customed Alt Meter
*/
class TTK_EXTRAS_EXPORT TTKAltitudeMeterWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit TTKAltitudeMeterWindow(QWidget *parent = 0);
    ~TTKAltitudeMeterWindow();
    void SetAltitudeType(const int type); //设置高度类型 气压高度 1，无线电高度 2, 三合一高度 3等
//private Q_SLOTS:
    void update(double value);

private:
    Ui::TTKAltitudeMeterWindow *ui;
    int altType; // 高度类型： 气压高度 1，无线电高度 2, 三合一高度 3
};

#endif // TTKALTITUDEMETERWINDOW_H
