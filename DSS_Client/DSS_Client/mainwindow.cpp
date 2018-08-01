#include "mainwindow.h"
#include "ui_mainwindow.h"
using namespace std;

#pragma execution_character_set("utf-8")
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    // Set layout
    QFormLayout *layout = new QFormLayout;
    m_pFlightCtrlDlg = new FlightControlDlg(this);
//    ui->mdiArea->addSubWindow(m_pFlightCtrlDlg);
    m_pFlightCtrlDlg->show();
    layout->addWidget(m_pFlightCtrlDlg);
    // Set layout in QWidget
    QWidget *window = new QWidget();
    window->setLayout(layout);
    // Set QWidget as the central layout of the main window
    setCentralWidget(window);
//    ui->mdiArea->size()
    InitRPCClient();

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::InitRPCClient()
{
    auto channel = grpc::CreateChannel(m_util.GetGrpcUrl(), grpc::InsecureChannelCredentials());
    m_client.SetChannel(channel);
}

void MainWindow::on_action_rule_triggered()
{
    m_pRuleCfgDlg = new RuleCfgDlg( m_client, this);
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
    m_client.StartReasoning();
    /*ui->textBrowser->setText(QString::fromStdString(m_client.GetReasoningResult().res()));
    ui->textBrowser->setText(QString::fromStdString(m_client.GetReasoningResult().data().data()));*/
    //cout <<"RESULT: " << m_client.GetReasoningResult().res() <<endl;
}

void MainWindow::on_action_fc_triggered()
{

//    m_pFlightCtrlDlg = new FlightControlDlg(this);
//    ui->mdiArea->addSubWindow(m_pFlightCtrlDlg);
//    m_pFlightCtrlDlg->show();
}
