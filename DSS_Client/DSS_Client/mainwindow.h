#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QHBoxLayout>
#include "service/grpcclientservice.h"
#include "view/rulecfgdlg.h"
#include "view/knowledgecfgdlg.h"
#include "view/flightcontroldlg.h"
#include "util/commonutils.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    void InitRPCClient();
    ~MainWindow();

private slots:
    void on_action_rule_triggered();

    void on_action_knowlege_triggered();

    void on_action_start_triggered();

    void on_action_fc_triggered();

private:
    Ui::MainWindow *ui;
    GrpcClientService m_client;
    CommonUtils m_util;

    RuleCfgDlg *m_pRuleCfgDlg;
    KnowledgeCfgDlg *m_pKnowledgeCfgDlg;
    FlightControlDlg *m_pFlightCtrlDlg;
};

#endif // MAINWINDOW_H
