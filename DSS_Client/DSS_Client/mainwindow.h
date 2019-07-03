#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#define TIMER_INTERVAL   (2) //10ms

#include <QMainWindow>
#include <QHBoxLayout>
#include <QObject>
#include <QTimer>
#include <QDebug>
#include <QThread>

#include "service/grpcclientservice.h"
#include "view/rulecfgdlg.h"
#include "view/knowledgecfgdlg.h"
#include "view/dashboard.h"
#include "util/commonutils.h"

class QTimer;
class TimerThread;

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

signals:
    void emitDoUpdateChart(const std::vector<std::vector<double> > &rpmChartData, int timeStep);
    void emitDoUpdateGauges(const std::string& data, const std::string& result, const std::string& wdlgres);
    void emitDoUpdateTimescreen(int timestep);

private slots:
    void on_action_rule_triggered();
    void on_action_knowlege_triggered();
    void on_action_start_triggered();
    void on_action_fc_triggered();
    void on_action_fast_triggered();
    void on_action_slow_triggered();
    void on_action_pause_triggered();
    void on_action_terminate_triggered();
    void on_action_exit_triggered();

    void doUpdateChart(const std::vector<std::vector<double> > &rpmChartData, int timeStep);
    void doUpdateGauges(const std::string& data, const std::string& result, const std::string& wdlgres);
    void doUpdateTimescreen(int timestep);


private:
    Ui::MainWindow *ui;
    GrpcClientService m_client;
    CommonUtils m_util;

    RuleCfgDlg *m_pRuleCfgDlg;
    KnowledgeCfgDlg *m_pKnowledgeCfgDlg;

    Dashboard *m_pDashboardDlg;
    int m_timestep;
    TimerThread* timerThread;
    bool bIsSimTermintate; //仿真是否停止
    bool bIsSimPause;   //仿真是否暂停
protected:
    void timerEvent( QTimerEvent *event );
    int m_nTimerId;


private:
    void ShowDashBoard(); // 显示主窗体Dashboard
};



class TimerThread: public QThread
{
    Q_OBJECT
public:
    TimerThread();
    void run(); //override
    void reset();
signals:
    void UpdateSignal(int num);

private:
    int t_timestep = 0;
};


#endif // MAINWINDOW_H
