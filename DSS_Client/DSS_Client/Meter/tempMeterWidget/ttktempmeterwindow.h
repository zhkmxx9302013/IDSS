#ifndef TTKTEMPMETERWINDOW_H
#define TTKTEMPMETERWINDOW_H

#include <QMainWindow>
#include "ttkglobaldefine.h"

namespace Ui {
class TTKTempMeterWindow;
}

/*!
* @author Zhaozihe <zhkmxx930@buaa.edu.cn>
* @desc     Customed Temperature Meter
*/
class TTK_EXTRAS_EXPORT TTKTempMeterWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit TTKTempMeterWindow(QWidget *parent = 0);
    ~TTKTempMeterWindow();

//private Q_SLOTS:
    void update(double value);

private:
    Ui::TTKTempMeterWindow *ui;

};

#endif // TTKTEMPMETERWINDOW_H
