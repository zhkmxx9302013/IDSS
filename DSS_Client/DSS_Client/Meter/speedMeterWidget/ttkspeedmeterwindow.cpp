#include "ttkspeedmeterwindow.h"
#include "ui_ttkspeedmeterwindow.h"

TTKSpeedMeterWindow::TTKSpeedMeterWindow(QWidget *parent)
    : QMainWindow(parent),
    ui(new Ui::TTKSpeedMeterWindow)
{
    ui->setupUi(this);
    setWindowFlags(Qt::CustomizeWindowHint|Qt::FramelessWindowHint);
//    connect(ui->horizontalSlider, SIGNAL(valueChanged(int)), SLOT(update(int)));

}

TTKSpeedMeterWindow::~TTKSpeedMeterWindow()
{
    delete ui;
}

void TTKSpeedMeterWindow::update(double value)
{
    ui->widget->setValue(value);
}
