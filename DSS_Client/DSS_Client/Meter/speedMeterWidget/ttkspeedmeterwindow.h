#ifndef TTKSPEEDMETERWINDOW_H
#define TTKSPEEDMETERWINDOW_H

#include <QMainWindow>
#include "ttkglobaldefine.h"

namespace Ui {
class TTKSpeedMeterWindow;
}

/*!
* @author Zhaozihe <zhkmxx930@buaa.edu.cn>
* @desc     Customed TA Meter
*/
class TTK_EXTRAS_EXPORT TTKSpeedMeterWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit TTKSpeedMeterWindow(QWidget *parent = 0);
    ~TTKSpeedMeterWindow();

//private Q_SLOTS:
    void update(double value);

private:
    Ui::TTKSpeedMeterWindow *ui;

};

#endif // TTKSPEEDMETERWINDOW_H
