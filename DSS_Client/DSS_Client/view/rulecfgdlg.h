#ifndef RULECFGDLG_H
#define RULECFGDLG_H

#include <QDialog>
#include <QMessageBox>
#include <map>
#include "service/grpcclientservice.h"
#include "util/commonutils.h"
#include <fstream>
#include <QFile>
#include <QDir>
#include <QFileDialog>
#include <QTableWidgetItem>



namespace Ui {
class RuleCfgDlg;
}

class RuleCfgDlg : public QDialog
{
    Q_OBJECT

public:
//    RuleCfgDlg(){}
//    explicit RuleCfgDlg(QWidget *parent = 0);
    explicit RuleCfgDlg(const GrpcClientService &_client, QWidget *parent = 0);
    ~RuleCfgDlg();

    //void InitRPCClient();       // 初始化RPC Client
    void InitRuleFileTable();   // 初始化规则库文件列表
    void InitSlotTable();
    void LoadCfgFile();   //从本地加载配置
    void SaveCfg2Local();   //将配置存在本地
    void SaveRuleFiles(bool bShowToast);       // 确认加载所选文件
    void LoadSlots();//加载模板槽列表

private slots:
    void on_refreshbtn_clicked();
    void on_RuleCfgDlg_accepted();
    void on_cancelbtn_clicked();
    void on_savebtn_clicked();
    void on_pushButton_clicked();
    void tableItemClicked(QTableWidgetItem * item);
    void on_loadCfgBtn_clicked();

private:
    Ui::RuleCfgDlg *ui;
    CommonUtils m_util;
    GrpcClientService m_client;
    int rowNum;
    int factRowNum;

    vector<string> m_fileNameList;
    std::map<std::string, std::string> m_slotList;
};

#endif // RULECFGDLG_H
