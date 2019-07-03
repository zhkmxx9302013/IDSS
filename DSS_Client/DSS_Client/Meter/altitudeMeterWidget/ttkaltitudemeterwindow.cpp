#include "ttkaltitudemeterwindow.h"
#include "ui_ttkaltitudemeterwindow.h"

TTKAltitudeMeterWindow::TTKAltitudeMeterWindow(QWidget *parent)
    : QMainWindow(parent),
    ui(new Ui::TTKAltitudeMeterWindow)
{
    ui->setupUi(this);
    setWindowFlags(Qt::CustomizeWindowHint|Qt::FramelessWindowHint);
//    connect(ui->horizontalSlider, SIGNAL(valueChanged(int)), SLOT(update(int)));

}

TTKAltitudeMeterWindow::~TTKAltitudeMeterWindow()
{
    delete ui;
}

void TTKAltitudeMeterWindow::SetAltitudeType(const int type)
{
    altType = type;
    ui->widget->setAltType(altType);
}

void TTKAltitudeMeterWindow::update(double value)
{
    ui->widget->setValue(value);
}
