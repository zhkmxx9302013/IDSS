#ifndef FLIGHTCONTROLDLG_H
#define FLIGHTCONTROLDLG_H

#include <QDialog>

namespace Ui {
class FlightControlDlg;
}

class FlightControlDlg : public QDialog
{
    Q_OBJECT

public:
    explicit FlightControlDlg(QWidget *parent = 0);
    ~FlightControlDlg();

private:
    Ui::FlightControlDlg *ui;
};

#endif // FLIGHTCONTROLDLG_H
