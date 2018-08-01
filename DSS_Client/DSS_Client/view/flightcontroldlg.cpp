#include "flightcontroldlg.h"
#include "ui_flightcontroldlg.h"

FlightControlDlg::FlightControlDlg(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::FlightControlDlg)
{
    ui->setupUi(this);
}

FlightControlDlg::~FlightControlDlg()
{
    delete ui;
}
