#ifndef KNOWLEDGECFGDLG_H
#define KNOWLEDGECFGDLG_H

#include <QDialog>
#include <QMessageBox>
#include <QDropEvent>
#include <map>
#include <fstream>
#include <QFile>
#include <QDir>
#include <QFileDialog>
#include "service/grpcclientservice.h"
#include "util/commonutils.h"

using namespace std;

namespace Ui {
class KnowledgeCfgDlg;
}

class KnowledgeCfgDlg : public QDialog
{
    Q_OBJECT

public:
    explicit KnowledgeCfgDlg(const GrpcClientService &_client, QWidget *parent = 0);
   // explicit KnowledgeCfgDlg(QWidget *parent = 0);
    ~KnowledgeCfgDlg();
    //void InitRPCClient();       // 初始化RPC Client
    void InitFactFileTable();   // 初始化规则库文件表格
    void InitSlotTable();       // 初始化槽模板表格
    void SaveFactFiles(bool toast); //保存事实库文件
    bool SetMapperList(); //保存时向服务端提交模板槽、变量映射关系列表
    bool SaveCfg2Local(); //将映射文件保存到本地
    bool LoadCfgFromLocal(); //从本地保存的文件中获取配置
    bool DoVarTableSearch(const QString &text);
private:
    bool eventFilter(QObject *, QEvent *); //Table Drag&Drop 事件过滤器

private slots:
    void on_loadFactsBtn_clicked();
    void on_cancelBtn_clicked();

    void on_saveCfgBtn_clicked();

    void on_loadBtn_clicked();

    void on_searchBar_textChanged(const QString &arg1);

private:
    Ui::KnowledgeCfgDlg *ui;
    CommonUtils m_util;
    GrpcClientService m_client;
    vector<string> m_fileNameList;
    int factFileRNum;     //事实库文件列表行数
    int slotRNum; //slot列表行数
    int varRNum; //变量表行数
};

#endif // KNOWLEDGECFGDLG_H
