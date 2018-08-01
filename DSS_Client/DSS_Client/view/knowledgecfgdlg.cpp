#include "knowledgecfgdlg.h"
#include "ui_knowledgecfgdlg.h"
#pragma execution_character_set("utf-8")



KnowledgeCfgDlg::KnowledgeCfgDlg(const GrpcClientService &_client, QWidget *parent):
    QDialog(parent),
    ui(new Ui::KnowledgeCfgDlg),
    slotRNum(0),
    factFileRNum(0),
    varRNum(0),
    m_client(_client)
{
    ui->setupUi(this);
    setFixedSize(this->width(), this->height());
    InitFactFileTable();
    InitSlotTable();
}

KnowledgeCfgDlg::~KnowledgeCfgDlg()
{
    delete ui;
}


void KnowledgeCfgDlg::InitFactFileTable()   // 初始化规则库文件列表
{
    vector<fact_file_info> factFileList;
    m_fileNameList.clear();

    m_client.FetchFactList(factFileList);

    factFileRNum = factFileList.size();
    if(factFileRNum<=0) return;

    ui->factFileTable->setRowCount(factFileRNum);
    ui->factFileTable->horizontalHeader()->setSectionResizeMode(0, QHeaderView::ResizeToContents);
    ui->factFileTable->horizontalHeader()->setSectionResizeMode(1, QHeaderView::Stretch);
    ui->factFileTable->horizontalHeader()->setSectionResizeMode(2, QHeaderView::Stretch);
    ui->factFileTable->horizontalHeader()->setSectionResizeMode(3, QHeaderView::ResizeToContents);

    for(size_t i = 0; i < factFileRNum; i++)
    {
        QTableWidgetItem *check=new QTableWidgetItem;
        check->setCheckState (Qt::Unchecked);
        m_fileNameList.emplace_back(factFileList[i].file_name());
        ui->factFileTable->setItem(i, 0, check); //插入复选框
        ui->factFileTable->setItem(i, 1, new QTableWidgetItem(QString::fromStdString(factFileList[i].file_name())));
        ui->factFileTable->setItem(i, 2, new QTableWidgetItem(QString::fromStdString(factFileList[i].file_desc())));
        ui->factFileTable->setItem(i, 3, new QTableWidgetItem(QString::fromStdString(factFileList[i].create_time())));

        ui->factFileTable->item(i, 1)->setFlags(ui->factFileTable->item(i, 1)->flags() & (~Qt::ItemIsEditable));
        ui->factFileTable->item(i, 2)->setFlags(ui->factFileTable->item(i, 2)->flags() & (~Qt::ItemIsEditable));
        ui->factFileTable->item(i, 3)->setFlags(ui->factFileTable->item(i, 3)->flags() & (~Qt::ItemIsEditable));
    }
}


void KnowledgeCfgDlg::SaveFactFiles(bool bShowToast)
{
    vector<fact_file_chk> chkList;
    if( m_fileNameList.size() <= 0)  { return;}
    cerr << "--" <<factFileRNum <<endl;
    for(size_t i = 0; i < factFileRNum; i++)
    {
        if(ui->factFileTable->item(i, 0)->checkState() == Qt::Checked)
        {
            cout << "**" <<endl;
            fact_file_chk rfc_obj;
            rfc_obj.set_ischeck(true);
            rfc_obj.set_filename(m_fileNameList[i]);
            chkList.emplace_back(rfc_obj);
        }
    }

    if(chkList.size() <= 0)
    {
        QMessageBox::warning(NULL, tr("警告"), tr("请选择需要加载的事实库文件!"));
        return;
    }

    if(m_client.SaveFactList(chkList))
    {
        if(bShowToast)
        {
            QMessageBox::information(NULL, tr("提示"), tr("保存成功!"));
            this->hide();
        }
    }
    else
    {
        if(bShowToast)
            QMessageBox::warning(NULL, tr("警告"), tr("保存失败，请重试！"));
    }
}


void KnowledgeCfgDlg::InitSlotTable()
{
    std::vector<fact_list> slotList = m_client.GetSelectedSlots();
    slotRNum = slotList.size();
    if(slotRNum <= 0)
    {
         QMessageBox::warning(NULL, tr("警告"), tr("请先加载规则库!"));
         this->destroy();
    }

    ui->slotTable->setRowCount(slotRNum);
    ui->slotTable->horizontalHeader()->setSectionResizeMode(0, QHeaderView::ResizeToContents);
    ui->slotTable->horizontalHeader()->setSectionResizeMode(1, QHeaderView::Stretch);
    ui->slotTable->horizontalHeader()->setSectionResizeMode(2, QHeaderView::Stretch);
    ui->slotTable->horizontalHeader()->setSectionResizeMode(3, QHeaderView::ResizeToContents);
    ui->slotTable->viewport()->installEventFilter(this);
    ////拖放使能
    ui->slotTable->setDragDropMode(QAbstractItemView::DragDrop);
    ui->slotTable->setDragEnabled(false);
    ui->slotTable->setAcceptDrops(true);

    ui->slotTable->setSelectionBehavior(QAbstractItemView::SelectItems);        //以Cell为单位
    ui->slotTable->setEditTriggers(QAbstractItemView::NoEditTriggers);        //不能编辑行内容

    for(size_t i = 0; i < slotRNum; i++)
    {
        ui->slotTable->setItem(i, 0, new QTableWidgetItem(QString::fromStdString(slotList[i].template_name())));
        ui->slotTable->setItem(i, 1, new QTableWidgetItem(QString::fromStdString(slotList[i].slot_name())));
        ui->slotTable->setItem(i, 2, new QTableWidgetItem(QString::fromStdString("")));
    }
}

bool KnowledgeCfgDlg::SaveCfg2Local() //将映射文件保存到本地
{
    std::ofstream outStream;
    outStream.open("../../data/facts/cfg", ios::binary);
    QString path = "../../data/facts/cfg";
    if(outStream.is_open())
    {
        for(size_t i = 0; i < factFileRNum; i++)
        {
            outStream << "[RULEFILE]:|" << ui->factFileTable->item(i, 0)->checkState()<<"|"
                      << ui->factFileTable->item(i, 1)->text().trimmed().toStdString() << "|"<< endl;

        }

        for(size_t i = 0; i < slotRNum; i++)
        {
            outStream << "[SLOT]:|"
                      << ui->slotTable->item(i, 0)->text().trimmed().toStdString()<< "|"
                      << ui->slotTable->item(i, 1)->text().trimmed().toStdString()<< "|"
                      << ui->slotTable->item(i, 2)->text().trimmed().toStdString()<< "|"<< endl;
        }

        for(size_t i = 0; i < varRNum; i++)
        {
            outStream << "[VAR]:|"
                      << ui->varTable->item(i, 0)->text().trimmed().toStdString() <<"|"
                      << ui->varTable->item(i, 1)->text().trimmed().toStdString() << "|"
                      << ui->varTable->item(i, 2)->text().trimmed().toStdString() << "|"<<endl;
        }
    }
    outStream.close();

    QString filename = QFileDialog::getSaveFileName(this, tr("另存为"), path, tr("Fact Config Files (*.fact)"));
    if(filename.size() <= 0) return false;

    QFile::copy(path, filename);
    QFile::remove(path);
    return true;
}

bool KnowledgeCfgDlg::LoadCfgFromLocal() //从本地保存的文件中获取配置
{
     //varRNum = tableRNum;
    QString fileName = QFileDialog::getOpenFileName(this,tr("打开"),"../../data/facts/",tr("Fact Config Files (*.fact)"));
    cerr << fileName.toStdString() <<endl;
    QFile file(fileName);
    if(!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
       return false;
    }

    for(int i = 0 ; i < factFileRNum; i ++)
    {
        QTableWidgetItem *check=new QTableWidgetItem;
        check->setCheckState (Qt::Unchecked);
        ui->factFileTable->setItem(i, 0, check); //插入复选框
    }

    ui->slotTable->setRowCount(1);

    ////拖放使能
    ui->slotTable->setDragDropMode(QAbstractItemView::DragDrop);
    ui->slotTable->setDragEnabled(false);
    ui->slotTable->setAcceptDrops(true);

    ui->slotTable->setSelectionBehavior(QAbstractItemView::SelectItems);        //以Cell为单位
    ui->slotTable->setEditTriggers(QAbstractItemView::NoEditTriggers);        //不能编辑行内容

    ui->varTable->setRowCount(1);
    ui->varTable->horizontalHeader()->setSectionResizeMode(0, QHeaderView::ResizeToContents);
    ui->varTable->horizontalHeader()->setSectionResizeMode(1, QHeaderView::Stretch);
    ui->varTable->horizontalHeader()->setSectionResizeMode(2, QHeaderView::ResizeToContents);

    ////拖放使能
    ui->varTable->setDragDropMode(QAbstractItemView::DragDrop);
    ui->varTable->setDragEnabled(true);
    ui->varTable->setAcceptDrops(false);
    ui->varTable->setSelectionBehavior(QAbstractItemView::SelectItems);      //以行为单位
    ui->varTable->setEditTriggers(QAbstractItemView::NoEditTriggers);        //不能编辑行内容

    int slot_row = 0;
    int var_row = 0;
    while(!file.atEnd())
    {
        QByteArray line = file.readLine();
        QString str(line);
        //恢复已选列表
        if(str.contains("[RULEFILE]:"))
        {
            QStringList list = str.split('|');
            bool bHasFile = false;
            for(int i = 0 ; i < factFileRNum; i ++)
            {
                if(ui->factFileTable->item(i, 1)->text() == list[2]) //插入复选框
                {

                    QTableWidgetItem *check=new QTableWidgetItem;
                    if(list[1].toInt() == Qt::Unchecked)
                        check->setCheckState (Qt::Unchecked);
                    if(list[1].toInt() == Qt::Checked)
                        check->setCheckState (Qt::Checked);

                    ui->factFileTable->setItem(i, 0, check); //插入复选框
                    bHasFile = true;
                    break;
                }
            }
            if(!bHasFile)
            {
                QMessageBox::about(NULL, tr("警告"), tr("存在无法打开的知识库文件，请检查知识库文件完整性!"));
            }
        }

        //恢复已选槽
        if(str.contains("[SLOT]:"))
        {
            QStringList list = str.split('|');

            ui->slotTable->setItem(slot_row, 0, new QTableWidgetItem(list[1]));
            ui->slotTable->setItem(slot_row, 1, new QTableWidgetItem(list[2]));
            ui->slotTable->setItem(slot_row, 2, new QTableWidgetItem(list[3]));

            ui->slotTable->insertRow( ui->slotTable->rowCount());

            slot_row++;
        }

        //恢复变量表
        if(str.contains("[VAR]:"))
        {
            QStringList list = str.split('|');

            ui->varTable->setItem(var_row, 0, new QTableWidgetItem(list[1]));
            ui->varTable->setItem(var_row, 1, new QTableWidgetItem(list[2]));
            ui->varTable->setItem(var_row, 2, new QTableWidgetItem(list[3]));

            ui->varTable->insertRow( ui->varTable->rowCount());

            var_row++;
        }

    }
    slotRNum = slot_row;
    varRNum = var_row;
    ui->slotTable->removeRow(slot_row);
    ui->varTable->removeRow(var_row);
    return true;
}

bool KnowledgeCfgDlg::eventFilter(QObject *obj, QEvent *event)
{
//    if(obj == ui->slotTable->viewport())
//    {
//        if(event->type() == QEvent::Drop)
//        {
//            QTableWidgetItem* pDropItem = ui->slotTable->itemAt(((QDropEvent*)event)->pos());
//            if(!pDropItem)
//            {
//                cout << pDropItem->row() <<endl;
//                return true;
//            }

//        }
//    }
    return false;
}

bool KnowledgeCfgDlg::DoVarTableSearch(const QString &text)
{
    int rC = ui->varTable->rowCount();//获得行号
        if ("" == text)//判断输入是否为空
        {
            for (int i = 0; i < rC; i++)
            {
                ui->varTable->setRowHidden(i, false);//显示所有行
            }
        }
        else
        {
            //获取符合条件的cell索引
            QList <QTableWidgetItem *> item = ui->varTable->findItems(text, Qt::MatchContains);

            for (int i = 0; i < rC; i++)
            {
                ui->varTable->setRowHidden(i, true);//隐藏所有行
            }

            if (!item.isEmpty())//不为空
            {
                for (int i = 0; i < item.count(); i++)
                {
                    ui->varTable->setRowHidden(item.at(i)->row(),false);//item.at(i).row()输出行号
                }
            }
        }
        return true;
}

//保存时向服务端提交模板槽、变量映射关系列表
bool KnowledgeCfgDlg::SetMapperList()
{
    vector<buaa::file::mapper> mapperList;
    for(size_t i = 0 ; i < slotRNum; i++)
    {

        buaa::file::mapper mapper;
        mapper.set_template_(ui->slotTable->item(i, 0)->text().toStdString());
        mapper.set_slot(ui->slotTable->item(i, 1)->text().toStdString());

        string slotName = ui->slotTable->item(i, 2)->text().toStdString();

        if(slotName.length() == 0) return false;
        else mapper.set_variable(ui->slotTable->item(i, 2)->text().toStdString());

        mapperList.emplace_back(mapper);
    }

    if(m_client.SetMapperList(mapperList))
        return true;
    else return false;
}

//根据选择的事实库文件加载事实库中可用的变量(按钮事件)
void KnowledgeCfgDlg::on_loadFactsBtn_clicked()
{
    ui->varTable->clearContents();
    SaveFactFiles(false);
    std::vector<fact_var> varList;
    m_client.FetchVarList(varList);
    int tableRNum = varList.size();
    varRNum = tableRNum;
    if(tableRNum <= 0)
    {
        cerr <<"no facts" <<endl;
        return;
    }

    ui->varTable->setRowCount(tableRNum);
    ui->varTable->horizontalHeader()->setSectionResizeMode(0, QHeaderView::ResizeToContents);
    ui->varTable->horizontalHeader()->setSectionResizeMode(1, QHeaderView::Stretch);
    ui->varTable->horizontalHeader()->setSectionResizeMode(2, QHeaderView::ResizeToContents);
    ui->varTable->viewport()->installEventFilter(this);
    ////拖放使能
    ui->varTable->setDragDropMode(QAbstractItemView::DragDrop);
    ui->varTable->setDragEnabled(true);
    ui->varTable->setAcceptDrops(false);
    ui->varTable->setSelectionBehavior(QAbstractItemView::SelectItems);      //以行为单位
    ui->varTable->setEditTriggers(QAbstractItemView::NoEditTriggers);        //不能编辑行内容

    for(unsigned int i = 0; i < tableRNum; i++)
    {
        ui->varTable->setItem(i, 0, new QTableWidgetItem(QString::fromStdString(varList[i].file())));
        ui->varTable->setItem(i, 1, new QTableWidgetItem(QString::fromStdString(varList[i].var_name())));
        ui->varTable->setItem(i, 2, new QTableWidgetItem(QString::fromStdString(varList[i].var_val())));
    }
}


void KnowledgeCfgDlg::on_cancelBtn_clicked()
{
    this->destroy();
}

void KnowledgeCfgDlg::on_saveCfgBtn_clicked()
{
    SaveFactFiles(false);
    if(!SetMapperList())
    {
        QMessageBox::warning(NULL, tr("警告"), tr("请检查是否有遗漏的，未进行变量映射的槽!"));
        return;
    }

    if(ui->saveLocalRadioBtn->isChecked())
    {
        if(!SaveCfg2Local()) return;
    }

    QMessageBox::information(NULL, tr("提示"), tr("保存到服务器成功!"));
    this->destroy();
}

void KnowledgeCfgDlg::on_loadBtn_clicked()
{
    if(!LoadCfgFromLocal())
    {
        cerr << "No file opened!" <<endl;
    }
}

void KnowledgeCfgDlg::on_searchBar_textChanged(const QString &arg1)
{
    DoVarTableSearch(arg1);
}
