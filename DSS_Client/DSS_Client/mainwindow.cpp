#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QTcpSocket>
using namespace std;

#pragma execution_character_set("utf-8")
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->statusBar->hide();
    setWindowFlags(Qt::CustomizeWindowHint|Qt::FramelessWindowHint);
    timerThread = new TimerThread;
    // SIGNAL - SLOT
    connect(this, SIGNAL(emitDoUpdateChart(const std::vector<std::vector<double> > &, int)), this, SLOT(doUpdateChart(const std::vector<std::vector<double> > &, int)));
    connect(this, SIGNAL(emitDoUpdateGauges(const std::string&, const std::string&, const std::string&)), this, SLOT(doUpdateGauges(const std::string&, const std::string&, const std::string&)));
    connect(timerThread, SIGNAL(UpdateSignal(int)), this, SLOT(doUpdateTimescreen(int)));

    m_timestep = 0;
    bIsSimPause = false;
    bIsSimTermintate = true;
    InitRPCClient();
    ShowDashBoard();
}

MainWindow::~MainWindow()
{
    if ( m_nTimerId != 0 )
        killTimer(m_nTimerId);
    delete timerThread;
    delete ui;
}

void MainWindow::InitRPCClient()
{
    auto channel = grpc::CreateChannel(m_util.GetGrpcUrl(), grpc::InsecureChannelCredentials());
    m_client.SetChannel(channel);
}

void MainWindow::on_action_rule_triggered()
{
    m_pRuleCfgDlg = new RuleCfgDlg(m_client, this);
    m_pRuleCfgDlg->setWindowTitle(tr("配置规则库"));
    m_pRuleCfgDlg->show();
}



void MainWindow::on_action_knowlege_triggered()
{
    m_pKnowledgeCfgDlg = new KnowledgeCfgDlg(m_client, this);
    m_pKnowledgeCfgDlg->setWindowTitle(tr("配置知识库"));
    m_pKnowledgeCfgDlg->show();
}

void MainWindow::on_action_start_triggered()
{
    if(bIsSimTermintate){
        m_client.StartReasoning();
        bIsSimTermintate = false;
    }

    m_nTimerId = startTimer(TIMER_INTERVAL);
    timerThread->start();
}

void MainWindow::on_action_fc_triggered()
{

//    m_pFlightCtrlDlg = new FlightControlDlg(this);
//    QMdiSubWindow *sub = ui->mdiArea->addSubWindow(m_pFlightCtrlDlg);
//    sub->setWindowFlags(Qt::FramelessWindowHint);
//    sub->resize(1920, 1030);
//    m_pFlightCtrlDlg->show();

}

void MainWindow::on_action_fast_triggered()
{
    if ( m_nTimerId != 0 )
        killTimer(m_nTimerId);
    m_nTimerId = startTimer(TIMER_INTERVAL / 5.0);
}


void MainWindow::on_action_slow_triggered()
{
    if ( m_nTimerId != 0 )
        killTimer(m_nTimerId);
    m_nTimerId = startTimer(TIMER_INTERVAL * 5.0);
}

void MainWindow::on_action_pause_triggered()
{
    bIsSimPause = true;
    if ( m_nTimerId != 0 )
        killTimer(m_nTimerId);

    timerThread->terminate();
}

void MainWindow::on_action_terminate_triggered()
{
    if ( m_nTimerId != 0 )
        killTimer(m_nTimerId);
    bIsSimTermintate = true;
   m_pDashboardDlg->Reset();
   m_timestep = 0;
   timerThread->terminate();
   timerThread->reset();
   QMessageBox::information(NULL, tr("提示"), tr("仿真停止!"));
}


void MainWindow::timerEvent( QTimerEvent *event )
{
    buaa::facts::result result = this->m_client.GetReasoningResult();
    m_client.TriggerChartSim();
    m_timestep ++;
    if(result.end())
    {
        if ( m_nTimerId != 0 ){
            killTimer(m_nTimerId);
            QMessageBox::information(NULL, tr("提示"), tr("仿真结束!"));
        }
    }
    else
    {
        if(m_pDashboardDlg != NULL)
        {
            emit emitDoUpdateGauges(result.data().data(), result.res(), result.wdlgres());
            if(m_timestep % 20 == 0)
            {
                std::vector<std::vector<double>> rpmChartData;
                emit emitDoUpdateChart(rpmChartData, m_timestep);
            }
        }
    }

}




void MainWindow::ShowDashBoard()
{
    m_pDashboardDlg = new Dashboard(m_client, this);
    ui->m_GlobalGridLayout->addWidget(m_pDashboardDlg, 1,0);
    m_pDashboardDlg->setGeometry(0,42,1920,990);
    m_pDashboardDlg->show();
}




void MainWindow::on_action_exit_triggered()
{
    if ( m_nTimerId != 0 )
        killTimer(m_nTimerId);
//    delete ui;
//    if(timerThread->isRunning())
//        timerThread->terminate();
//    delete timerThread;
    qApp->quit();
}

void MainWindow::doUpdateChart(const std::vector<std::vector<double> > &rpmChartDatap, int timeStep)
{
    std::vector<std::vector<double>> rpmChartData = m_client.GetRPMChartData();
    m_pDashboardDlg->UpdateRPMChart(rpmChartData, m_timestep);
}

void MainWindow::doUpdateGauges(const std::string& data, const std::string& result, const std::string& wdlgres)
{
     m_pDashboardDlg->UpdateGauges(data, result, wdlgres);
}

void MainWindow::doUpdateTimescreen(int timestep)
{
    ui->m_simTimeLabel->setText(QString::number(double(timestep) / double(10.0), 10, 2) + QString("s"));
}


TimerThread::TimerThread()
{
    t_timestep = 0;
}

void TimerThread::run()
{
    while(1)
    {
        t_timestep++;
        emit UpdateSignal(t_timestep);
        msleep(100);
    }

}

void TimerThread::reset()
{
    t_timestep = 0;
    emit UpdateSignal(t_timestep);
}
