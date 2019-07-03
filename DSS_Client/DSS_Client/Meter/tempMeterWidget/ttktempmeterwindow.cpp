#include "ttktempmeterwindow.h"
#include "ui_ttktempmeterwindow.h"

TTKTempMeterWindow::TTKTempMeterWindow(QWidget *parent)
    : QMainWindow(parent),
    ui(new Ui::TTKTempMeterWindow)
{
    ui->setupUi(this);
    setWindowFlags(Qt::CustomizeWindowHint|Qt::FramelessWindowHint);
//    connect(ui->horizontalSlider, SIGNAL(valueChanged(int)), SLOT(update(int)));

}

TTKTempMeterWindow::~TTKTempMeterWindow()
{
    delete ui;
}

void TTKTempMeterWindow::update(double value)
{
    ui->widget->setValue(value);
}
