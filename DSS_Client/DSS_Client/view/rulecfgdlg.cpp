#include "rulecfgdlg.h"
#include "ui_rulecfgdlg.h"
#include <iostream>
using namespace std;
#pragma execution_character_set("utf-8")

RuleCfgDlg::RuleCfgDlg(const GrpcClientService &_client, QWidget *parent):
    QDialog(parent),
    ui(new Ui::RuleCfgDlg),
    rowNum(0),
    factRowNum(0),
    m_client(_client)
{
    ui->setupUi(this);
    setFixedSize(this->width(), this->height());
    InitRuleFileTable();
    InitSlotTable();
}

RuleCfgDlg::~RuleCfgDlg()
{
    delete ui;
}

void RuleCfgDlg::InitSlotTable()
{
    ui->slot_table->horizontalHeader()->setSectionResizeMode(0, QHeaderView::ResizeToContents);
    ui->slot_table->horizontalHeader()->setSectionResizeMode(1, QHeaderView::Stretch);
    ui->slot_table->horizontalHeader()->setSectionResizeMode(2, QHeaderView::Stretch);
    ui->slot_table->horizontalHeader()->setSectionResizeMode(3, QHeaderView::ResizeToContents);
    connect(ui->slot_table,SIGNAL(itemClicked(QTableWidgetItem *)),this,SLOT(tableItemClicked(QTableWidgetItem *)));
}


void RuleCfgDlg::InitRuleFileTable()
{
    vector<rule_file_info> ruleFileList;
    m_fileNameList.clear();

    m_client.FetchRuleFileList(ruleFileList);

    rowNum = ruleFileList.size();
    if(rowNum<=0) return;

    ui->ruleFileTable->setRowCount(rowNum);
    ui->ruleFileTable->horizontalHeader()->setSectionResizeMode(0, QHeaderView::ResizeToContents);
    ui->ruleFileTable->horizontalHeader()->setSectionResizeMode(1, QHeaderView::Stretch);
    ui->ruleFileTable->horizontalHeader()->setSectionResizeMode(2, QHeaderView::Stretch);
    ui->ruleFileTable->horizontalHeader()->setSectionResizeMode(3, QHeaderView::ResizeToContents);


    for(unsigned int i = 0; i < ruleFileList.size(); i++)
    {
        QTableWidgetItem *check=new QTableWidgetItem;
        check->setCheckState (Qt::Unchecked);
        m_fileNameList.emplace_back(ruleFileList[i].file_name());
        ui->ruleFileTable->setItem(i, 0, check); //插入复选框
        ui->ruleFileTable->setItem(i, 1, new QTableWidgetItem(QString::fromStdString(ruleFileList[i].file_name())));
        ui->ruleFileTable->setItem(i, 2, new QTableWidgetItem(QString::fromStdString(ruleFileList[i].file_desc())));
        ui->ruleFileTable->setItem(i, 3, new QTableWidgetItem(QString::fromStdString(ruleFileList[i].create_time())));

        ui->ruleFileTable->item(i, 1)->setFlags(ui->ruleFileTable->item(i, 1)->flags() & (~Qt::ItemIsEditable));
        ui->ruleFileTable->item(i, 2)->setFlags(ui->ruleFileTable->item(i, 2)->flags() & (~Qt::ItemIsEditable));
        ui->ruleFileTable->item(i, 3)->setFlags(ui->ruleFileTable->item(i, 3)->flags() & (~Qt::ItemIsEditable));
    }

}

void RuleCfgDlg::LoadCfgFile()   //从本地加载配置
{
    QString fileName = QFileDialog::getOpenFileName(this,tr("打开"),"../../data/rules/",tr("data Files (*.dat)"));
    cerr << fileName.toStdString() <<endl;
    QFile file(fileName);
    if(!file.open(QIODevice::ReadOnly | QIODevice::Text)) {

       return;
    }

//    m_fileNameList.clear();
//    m_slotList.clear();

    for(int i = 0 ; i < rowNum; i ++)
    {
        QTableWidgetItem *check=new QTableWidgetItem;
        check->setCheckState (Qt::Unchecked);
        ui->ruleFileTable->setItem(i, 0, check); //插入复选框
    }

    ui->slot_table->setRowCount(1);
    ui->slot_table->setSortingEnabled(true);

    int slot_row = 0;
    QString tempstr = "";
    while(!file.atEnd())
    {
        QByteArray line = file.readLine();
        QString str(line);
        //恢复已选列表
        if(str.contains("[RULEFILE]:"))
        {
            QStringList list = str.split('|');
            bool bHasFile = false;
            for(int i = 0 ; i < rowNum; i ++)
            {
                if(ui->ruleFileTable->item(i, 1)->text() == list[1]) //插入复选框
                {
                    QTableWidgetItem *check=new QTableWidgetItem;
                    if(list[0].split(':')[1].toInt() == Qt::Unchecked)
                        check->setCheckState (Qt::Unchecked);
                    if(list[0].split(':')[1].toInt() == Qt::Checked)
                        check->setCheckState (Qt::Checked);

                    ui->ruleFileTable->setItem(i, 0, check); //插入复选框
                    bHasFile = true;
                    break;
                }
            }
            if(!bHasFile)
            {
                QMessageBox::about(NULL, tr("警告"), tr("存在无法打开的规则库文件，请检查规则库文件完整性!"));
            }
        }

        //恢复已选槽
        if(str.contains("[SLOT]:"))
        {
            QStringList list = str.split('|');
            QTableWidgetItem *check=new QTableWidgetItem;
            QString templateName = list[1];
            if(tempstr == templateName)
            {
                check->setFlags(~(Qt::ItemIsEnabled|Qt::ItemIsEditable));
            }else{
                tempstr = templateName;
            }

            if(list[0].split(':')[1].toInt() == Qt::Unchecked)
                check->setCheckState (Qt::Unchecked);
            if(list[0].split(':')[1].toInt() == Qt::Checked)
                check->setCheckState (Qt::Checked);

            ui->slot_table->setItem(slot_row, 0, check); //插入复选框
            ui->slot_table->setItem(slot_row, 1, new QTableWidgetItem(list[1]));
            ui->slot_table->setItem(slot_row, 2, new QTableWidgetItem(list[2]));
            ui->slot_table->setItem(slot_row, 3, new QTableWidgetItem(list[3]));

            ui->slot_table->item(slot_row, 1)->setFlags(ui->slot_table->item(slot_row, 1)->flags() & (~Qt::ItemIsEditable));
            ui->slot_table->item(slot_row, 2)->setFlags(ui->slot_table->item(slot_row, 2)->flags() & (~Qt::ItemIsEditable));
            ui->slot_table->item(slot_row, 3)->setFlags(ui->slot_table->item(slot_row, 3)->flags() & (~Qt::ItemIsEditable));

            ui->slot_table->insertRow( ui->slot_table->rowCount());

            slot_row++;
        }

    }
    factRowNum = slot_row;
    ui->slot_table->removeRow(slot_row);


}

void RuleCfgDlg::SaveCfg2Local()
{
    std::ofstream outStream;
    outStream.open("../../data/rules/cfg", ios::binary);
    QString path = "../../data/rules/cfg";
    if(outStream.is_open())
    {
        for(unsigned int i = 0; i < rowNum; i++)
        {
            outStream << "[RULEFILE]:" << ui->ruleFileTable->item(i, 0)->checkState()<<"|"
                      << ui->ruleFileTable->item(i, 1)->text().trimmed().toStdString()<<"|"
                      <<ui->ruleFileTable->item(i, 2)->text().trimmed().toStdString()<<"|"
                     <<ui->ruleFileTable->item(i, 3)->text().trimmed().toStdString()<< "|"
                     <<endl;
        }

        for(unsigned int i = 0; i < factRowNum; i++)
        {
            outStream << "[SLOT]:"
                      << ui->slot_table->item(i, 0)->checkState() << "|"
                      <<ui->slot_table->item(i, 1)->text().trimmed().toStdString()<< "|"
                      <<ui->slot_table->item(i, 2)->text().trimmed().toStdString()<< "|"
                      <<ui->slot_table->item(i, 3)->text().trimmed().toStdString() <<"|"
                      <<endl;
        }
    }
    outStream.close();

    QString filename = QFileDialog::getSaveFileName(this, tr("另存为"), path, tr("data Files (*.dat)"));
    QFile::copy(path, filename);
    QFile::remove(path);
}

//加载模板槽列表
void RuleCfgDlg::LoadSlots()
{
    SaveRuleFiles(false);
    std::vector<std::map<std::string, std::string>>  slot_list;

    std::map<std::string, std::string>::iterator itm;
    slot_list = m_client.GetSlotList();

    factRowNum = slot_list.size();
    if(factRowNum <= 0) return;

    ui->slot_table->setRowCount(factRowNum);
    ui->slot_table->horizontalHeader()->setSectionResizeMode(0, QHeaderView::ResizeToContents);
    ui->slot_table->horizontalHeader()->setSectionResizeMode(1, QHeaderView::Stretch);
    ui->slot_table->horizontalHeader()->setSectionResizeMode(2, QHeaderView::Stretch);
    ui->slot_table->horizontalHeader()->setSectionResizeMode(3, QHeaderView::ResizeToContents);
    ui->slot_table->setSortingEnabled(true);
    std::string tempstr = "";

    for(int i = 0; i< factRowNum; i++)
    {
        QTableWidgetItem *check=new QTableWidgetItem;
        check->setCheckState (Qt::Checked);
        string templateName = slot_list[i].begin()->first;
        if(tempstr == templateName)
        {
            check->setFlags(~(Qt::ItemIsEnabled|Qt::ItemIsEditable));
        }else{
            tempstr = templateName;
        }

        ui->slot_table->setItem(i, 0, check); //插入复选框
        ui->slot_table->setItem(i, 1, new QTableWidgetItem(QString::fromStdString(templateName)));
        ui->slot_table->setItem(i, 2, new QTableWidgetItem(QString::fromStdString(slot_list[i].begin()->second)));
        ui->slot_table->setItem(i, 3, new QTableWidgetItem(QString::fromStdString("--")));

        ui->slot_table->item(i, 1)->setFlags(ui->slot_table->item(i, 1)->flags() & (~Qt::ItemIsEditable));
        ui->slot_table->item(i, 2)->setFlags(ui->slot_table->item(i, 2)->flags() & (~Qt::ItemIsEditable));
        ui->slot_table->item(i, 3)->setFlags(ui->slot_table->item(i, 3)->flags() & (~Qt::ItemIsEditable));

    }
}

void RuleCfgDlg::SaveRuleFiles(bool bShowToast)
{
    vector<rule_file_chk> chkList;
    if( m_fileNameList.size() <= 0)  return;

    for(unsigned int i = 0; i < rowNum; i++)
    {
        if(ui->ruleFileTable->item(i, 0)->checkState() == Qt::Checked)
        {
            rule_file_chk rfc_obj;
            rfc_obj.set_ischeck(true);
            rfc_obj.set_filename(m_fileNameList[i]);
            chkList.emplace_back(rfc_obj);
        }
    }

    if(bShowToast)
    {
        vector<fact_list> factList;
        string temp = "";
        for(unsigned int i = 0; i < factRowNum; i++)
        {
            if(ui->slot_table->item(i, 0)->checkState() == Qt::Checked)
            {
                string curr_name = ui->slot_table->item(i, 1)->text().toStdString();
                if(curr_name.compare(temp) == 0) continue;

                fact_list rfc_obj;
                rfc_obj.set_template_name(curr_name);
                rfc_obj.set_slot_name("");
                factList.emplace_back(rfc_obj);
                temp = curr_name;
            }
        }
        m_client.SetSlotList(factList);
    }

    if(m_client.SaveRuleList(chkList))
    {
        if(bShowToast)
        {
            QMessageBox::information(NULL, tr("提示"), tr("保存到服务端成功!"));
            this->hide();
        }
    }
    else
    {
        if(bShowToast)
            QMessageBox::warning(NULL, tr("警告"), tr("保存到服务端失败，请重试！"));
    }

}

void RuleCfgDlg::on_refreshbtn_clicked()
{
    //InitRuleFileTable();
}

void RuleCfgDlg::on_RuleCfgDlg_accepted()
{

}

void RuleCfgDlg::on_cancelbtn_clicked()
{
   this->destroy();
}

void RuleCfgDlg::on_savebtn_clicked()
{
    if(ui->isSaveFileRadio->isChecked())
        SaveCfg2Local();

    cerr <<"Saving..." <<endl;
    SaveRuleFiles(true);
}

void RuleCfgDlg::on_pushButton_clicked()
{
    LoadSlots();
}

void RuleCfgDlg::tableItemClicked(QTableWidgetItem * _item)
{
    for(int i = _item->row() + 1; i < factRowNum; i++)
    {
        if(ui->slot_table->item(i, 1)->text().trimmed() == ui->slot_table->item(_item->row(), 1)->text().trimmed())
        {
            QTableWidgetItem *check=new QTableWidgetItem;

            if(_item->checkState() == Qt::Checked)
                check->setCheckState (Qt::Checked);
            if(_item->checkState() == Qt::Unchecked)
                check->setCheckState (Qt::Unchecked);

            check->setFlags(~(Qt::ItemIsEnabled|Qt::ItemIsEditable));
            ui->slot_table->setItem(i, 0, check);

        }
        else{
            break;
        }
    }
}

void RuleCfgDlg::on_loadCfgBtn_clicked()
{
    LoadCfgFile();
}
