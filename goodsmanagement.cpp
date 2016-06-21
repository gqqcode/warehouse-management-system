#include "goodsmanagement.h"
extern bool flag;
extern bool isOK;
extern bool goodsisChange;
GoodsManagement::GoodsManagement(QWidget *parent)
    : QMainWindow(parent)
{
    setWindowIcon(QIcon(":/mainImag/nuoya.png"));

    this->setAttribute(Qt::WA_QuitOnClose,false);

    this->setFixedSize(1200,700);
    this->setWindowTitle(tr("商品管理"));
    createLabel_LineEdit();
    createButton();
    createTableView();
    selectShow();
    oper=0;
}
void GoodsManagement::createLabel_LineEdit()
{
    msgLabel=new QLabel();
    msgLabel->setMinimumSize(msgLabel->sizeHint());
    msgLabel->setAlignment(Qt::AlignLeft);
    QFont ft;
    ft.setPointSize(12);

    //设置颜色
    QPalette pa;
    pa.setColor(QPalette::WindowText,Qt::red);
    this->statusBar()->addWidget(msgLabel);
    this->statusBar()->setFixedHeight(40);
    this->statusBar()->setFont(ft);
    this->statusBar()->setPalette(pa);

    createAction();
    goodsIdLabel=new QLabel(tr("产品编号："),this);//x 250 y   50
    goodsIdLabel->setGeometry(100,30,70,30);

    goodsIdLineEdit=new QLineEdit(this);
    goodsIdLineEdit->setGeometry(170,30,160,30);



    goodsNameLabel=new QLabel(tr("产品名称："),this);
    goodsNameLabel->setGeometry(350,30,70,30);

    goodsNameLineEdit=new QLineEdit(this);
    goodsNameLineEdit->setGeometry(420,30,160,30);


    goodsFormatLabel=new QLabel(tr("产品规格："),this);
    goodsFormatLabel->setGeometry(600,30,70,30);

    goodsFormatLineEdit=new QLineEdit(this);
    goodsFormatLineEdit->setGeometry(670,30,160,30);

    goodsClassLabel=new QLabel(tr("产品类别："),this);
    goodsClassLabel->setGeometry(850,30,70,30);

    goodsClassLineEdit=new QLineEdit(this);
    goodsClassLineEdit->setGeometry(920,30,160,30);


    goodsUnitLabel=new QLabel(tr("计量单位："),this);
    goodsUnitLabel->setGeometry(100,80,70,30);
    goodsUnitLineEdit=new QLineEdit(this);
    goodsUnitLineEdit->setGeometry(170,80,160,30);

    goodsStatusLabel=new QLabel(tr("产品状态："),this);
    goodsStatusLabel->setGeometry(350,80,70,30);

    goodsStatusComboBox=new QComboBox(this);
    goodsStatusComboBox->addItem(tr("在售"));
    goodsStatusComboBox->addItem(tr("停用"));

    goodsStatusComboBox->setGeometry(420,80,160,30);

    goodsSaveLabel=new QLabel(tr("安全库存："),this);
    goodsSaveLabel->setGeometry(600,80,70,30);
    goodsSaveLineEdit=new QLineEdit(this);
    goodsSaveLineEdit->setGeometry(670,80,160,30);
    QRegExp regExp1("[1-9][0-9]+$");
    QValidator *validator1 = new QRegExpValidator(regExp1, goodsSaveLineEdit );//正则表达式

    goodsSaveLineEdit->setValidator(validator1);

    goodsPriceLabel=new QLabel(tr("  单价："),this);
    goodsPriceLabel->setGeometry(850,80,70,30);
    goodsPriceLineEdit=new QLineEdit(this);
    goodsPriceLineEdit->setGeometry(920,80,160,30);
    QRegExp regExp2("[1-9][0-9]+$");
    QValidator *validator2 = new QRegExpValidator(regExp2, goodsPriceLineEdit );//正则表达式

    goodsPriceLineEdit->setValidator(validator2);



    goodsremarksLabel=new QLabel(tr("备注："),this);
    goodsremarksLabel->setGeometry(100,130,70,30);
    goodsremarksTextEdit=new QTextEdit(this);
    goodsremarksTextEdit->setGeometry(170,130,500,100);


}
void GoodsManagement::createButton()
{

    enterPushButton=new QPushButton("保存",this);
    enterPushButton->setGeometry(970,180,100,50);
    connect(enterPushButton,SIGNAL(clicked()),this,SLOT(saveFun()));

    importPushButton=new QPushButton("导入",this);
    importPushButton->setGeometry(800,180,100,50);
    connect(importPushButton,SIGNAL(clicked()),this,SLOT(importFun()));


}
void GoodsManagement::createTableView()
{
    mainTableView=new QTableView(this);
    mainTableView->setGeometry(80,260,1050,400);
    mainTableView->setEditTriggers(QTableView::NoEditTriggers);

    mainTableView->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(mainTableView, SIGNAL(customContextMenuRequested(const QPoint&)),this, SLOT(showContextMenu(const QPoint&)));//this是datatable所在窗口

    tableModel = new QStandardItemModel();

    tableModel->setHorizontalHeaderItem(0, new QStandardItem(QObject::tr("产品编号 ")));
    tableModel->setHorizontalHeaderItem(1, new QStandardItem(QObject::tr("产品名称 ")));

    tableModel->setHorizontalHeaderItem(2, new QStandardItem(QObject::tr("产品规格 ")));
    tableModel->setHorizontalHeaderItem(3, new QStandardItem(QObject::tr("产品类别 ")));
    tableModel->setHorizontalHeaderItem(4, new QStandardItem(QObject::tr("计量单位 ")));

    tableModel->setHorizontalHeaderItem(5, new QStandardItem(QObject::tr("安全库存 ")));
    tableModel->setHorizontalHeaderItem(6, new QStandardItem(QObject::tr("单价 ")));
    tableModel->setHorizontalHeaderItem(7, new QStandardItem(QObject::tr("备注 ")));
    tableModel->setHorizontalHeaderItem(8, new QStandardItem(QObject::tr("产品状态 ")));

    mainTableView->setModel(tableModel);
}
void GoodsManagement::createAction()
{

    alterAct=new QAction(QIcon(":/image/alter.png"),tr("修改"),this);
    alterAct->setStatusTip(tr("修改基础档案"));
    connect(alterAct,SIGNAL(triggered()),this,SLOT(alterRecord()));



    deleteAct=new QAction(QIcon(":/image/alter.png"),tr("删除"),this);
    deleteAct->setStatusTip(tr("删除基础档案"));
    connect(deleteAct,SIGNAL(triggered()),this,SLOT(deleteRecord()));



    availableAct=new QAction(QIcon(":/image/alter.png"),tr("启用"),this);
    availableAct->setStatusTip(tr("使停用基础档案可用"));
    connect(availableAct,SIGNAL(triggered()),this,SLOT(availableFun()));


    pauseAct=new QAction(QIcon(":/image/alter.png"),tr("停用"),this);
    pauseAct->setStatusTip(tr("使基础档案停用"));
    connect(pauseAct,SIGNAL(triggered()),this,SLOT(pauseFun()));
}


void GoodsManagement::alterRecord()
{
    rowNum= mainTableView->currentIndex().row();

    updatedId=tableModel->item(rowNum, 0)->text();
    goodsIdLineEdit->setText(tableModel->item(rowNum, 0)->text());
    goodsNameLineEdit->setText(tableModel->item(rowNum, 1)->text());
    goodsFormatLineEdit->setText(tableModel->item(rowNum, 2)->text());
    goodsClassLineEdit->setText(tableModel->item(rowNum, 3)->text());
    goodsUnitLineEdit->setText(tableModel->item(rowNum, 4)->text());
    goodsSaveLineEdit->setText(tableModel->item(rowNum,5)->text());
    goodsPriceLineEdit->setText(tableModel->item(rowNum, 6)->text());
    goodsremarksTextEdit->setText(tableModel->item(rowNum, 7)->text());
    goodsStatusComboBox->setCurrentText(tableModel->item(rowNum, 8)->text());
    msgLabel->setText("<h3><font color=red>当前操作：修改商品信息</font></h3>");
    oper=1;
}

bool GoodsManagement::isExist(QString id)
{
    QSqlQuery query;
    QString select_sql="select goodsid from goodsstorage where goodsid=:id";
    query.prepare(select_sql);
    query.bindValue(":id",id);
    query.exec();
    int i=0;
    while(query.next())
    {
        i++;
    }
    if(i>0)
        return true;
    else
        return false;
}

void GoodsManagement::deleteRecord()
{




    QSqlQuery query;
    int row=mainTableView->currentIndex().row();



    if(isExist(tableModel->item(row, 0)->text()))
    {
        QMessageBox msgBox(QMessageBox::Warning, tr("警告"),"库存中还存在一些该商品未出库,是否继续删除？", 0, this);
        msgBox.addButton(tr("取消"), QMessageBox::AcceptRole);
        msgBox.addButton(tr("继续"), QMessageBox::RejectRole);
        if (msgBox.exec() == QMessageBox::AcceptRole)
        {

            return;
        }
        else
        {
            QSqlQuery deletequery;

            QString delete_sql = "delete from goodsstorage where goodsid = ?";

            deletequery.prepare(delete_sql);
            deletequery.addBindValue(tableModel->item(row, 0)->text());
            deletequery.exec();
        }

    }


    QString delete_sql = "delete from goods where goodsid = ?";

    query.prepare(delete_sql);
    query.addBindValue(tableModel->item(row, 0)->text());
    if(!query.exec())
    {
        QMessageBox::warning(this,"警告","商品信息删除失败,可能不存在该商品信息！");
    }
    else
    {


        tableModel->removeRow(row);
        msgLabel->setText("<h3><font color=red>商品信息删除成功！</font></h3>");

    }
}

void GoodsManagement::availableFun()
{

    int row=mainTableView->currentIndex().row();

    msgLabel->setText("<h3><font color=red>当前操作：生效商品信息</font></h3>");

    if(tableModel->item(row, 8)->text()=="停用")
    {
        QSqlQuery query;
        QString update_sql="update goods set goodsstatus=:goodsstatus,   goodsstatusid=:goodsstatusid where goodsid = :goodsid";
        query.prepare(update_sql);
        query.bindValue(":goodsid",  tableModel->item(row, 0)->text());

        //tableModel->item(row,8)->setForeground();
        query.bindValue(":goodsstatus", "在售");
        query.bindValue(":goodsstatusid",0);
        if(!query.exec())
        {
            return;
        }
        /*if(isExist(tableModel->item(row, 0)->text()))
        {

            QSqlQuery updatequery;

            QString update_sql = "update  goodsstorage goodsstatus=:goodsstatus where goodsid = :goodsid";
            updatequery.prepare(update_sql);
            updatequery.bindValue(":goodsstatus", "在售");
            updatequery.bindValue(":goodsstatusid",1);

            updatequery.exec();

        }*/
        tableModel->item(row, 8)->setText("在售");
        tableModel->item(row,8)->setBackground(QBrush(QColor(255, 255, 255)));
        msgLabel->setText("<h3><font color=red>当前状态：  在售</font></h3>");


    }

}
void GoodsManagement::pauseFun()
{

    int row=mainTableView->currentIndex().row();

    msgLabel->setText("<h3><font color=red>当前操作：停用商品信息</font></h3>");
    if(tableModel->item(row, 8)->text()=="在售")
    {
        QSqlQuery query;
        QString update_sql="update goods set goodsstatus=:goodsstatus,   goodsstatusid=:goodsstatusid where goodsid = :goodsid";
        query.prepare(update_sql);
        query.bindValue(":goodsid", tableModel->item(row, 0)->text());

        //tableModel->item(row,8)->setForeground();
        query.bindValue(":goodsstatus", "停用");
        query.bindValue(":goodsstatusid",0);
        if(!query.exec())
        {
            return;
        }
        /*if(isExist(tableModel->item(row, 0)->text()))
        {

            QSqlQuery updatequery;

            QString update_sql = "update  goodsstorage goodsstatus=:goodsstatus where goodsid = :goodsid";
            updatequery.prepare(update_sql);
            updatequery.bindValue(":goodsid", tableModel->item(row, 0)->text());

            updatequery.bindValue(":goodsstatus", "停用");
            updatequery.bindValue(":goodsstatusid",0);

            updatequery.exec();

        }*/

        tableModel->item(row, 8)->setText("停用");
        tableModel->item(row,8)->setBackground(QBrush(QColor(255, 0, 0)));
        msgLabel->setText("<h3><font color=red>当前状态：  停用</font></h3>");

    }

}


void GoodsManagement::paintEvent(QPaintEvent*)

{
    QPainter painter(this);
    QPixmap pix;
    pix.load(":/mainImag/background.png");
    painter.drawPixmap(0,0,this->width(),this->height(),pix);
}
void GoodsManagement::showContextMenu(const QPoint& pos)//contextMenuEvent(QContextMenuEvent * event)
{
    if(rightMenu)//保证同时只存在一个menu，及时释放内存
    {
        delete rightMenu;
        rightMenu = NULL;
    }
    if( mainTableView->currentIndex().isValid())
    {


        rightMenu = new QMenu(this);
        rightMenu->addAction(alterAct);
        rightMenu->addAction(deleteAct);
        rightMenu->addAction(pauseAct);
        rightMenu->addAction(availableAct);
        rightMenu->exec(QCursor::pos()); // 菜单出现的位置为当前鼠标的位置
    }


}
void GoodsManagement::clearEdit()
{
    goodsIdLineEdit->clear();
    goodsNameLineEdit->clear();
    goodsFormatLineEdit->clear();
    goodsClassLineEdit->clear();
    goodsUnitLineEdit->clear();
    goodsSaveLineEdit->clear();
    goodsPriceLineEdit->clear();
    goodsremarksTextEdit->clear();
}
void GoodsManagement::saveFun()
{

    QSqlQuery query;

    if(goodsIdLineEdit->text().isEmpty())
    {
        QMessageBox::warning(this,"警告","请添加产品编号！");
        return ;
    }
    if(goodsNameLineEdit->text().isEmpty())
    {
        QMessageBox::warning(this,"警告","请添加产品名称！");
        return ;
    }
    if(goodsSaveLineEdit->text().isEmpty())
    {
        QMessageBox::warning(this,"警告","请添加产品安全库存！");
        return ;
    }
    if(goodsPriceLineEdit->text().isEmpty())
    {
        QMessageBox::warning(this,"警告","请添加产品单价！");
        return ;
    }

    switch(oper)
    {
    case 1:
    {

        QString update_sql="update goods set goodsid=:goodsid, goodsname=:goodsname,  goodsformat=:goodsformat,\
                goodsclass=:goodsclass , goodsunit=:goodsunit,   goodssave=:goodssave,  goodsprice=:goodsprice,\
                goodsremarks=:goodsremarks,   goodsstatus=:goodsstatus,   goodsstatusid=:goodsstatusid where goodsid = :updatedId";
        query.prepare(update_sql);
        query.bindValue(":updatedId",updatedId);
        query.bindValue(":goodsid", goodsIdLineEdit->text());
        query.bindValue(":goodsname", goodsNameLineEdit->text());
        query.bindValue(":goodsformat",goodsFormatLineEdit->text() );
        query.bindValue(":goodsclass",goodsClassLineEdit->text());
        query.bindValue(":goodsunit", goodsUnitLineEdit->text());
        query.bindValue(":goodssave", goodsSaveLineEdit->text().toDouble());
        query.bindValue(":goodsprice", goodsPriceLineEdit->text().toDouble());
        query.bindValue(":goodsremarks", goodsremarksTextEdit->toPlainText());
        query.bindValue(":goodsstatus", goodsStatusComboBox->currentText());

        QString status=goodsStatusComboBox->currentText();
        status=status.simplified();
        if(status=="在售")
        {
            query.bindValue(":goodsstatusid",1);

        }
        else
        {
            query.bindValue(":goodsstatusid",0);
        }
        if(!query.exec())
        {
            QString waring="已经存在编号为："+goodsIdLineEdit->text()+" 的商品的信息,商品信息修改失败\n请核实后再操作！";
            QMessageBox::warning(this,"警告",waring);
            clearEdit();
        }
        else
        {

            if(isExist(updatedId))
            {
                QSqlQuery updatequery;

                QString update_sql = "update  goodsstorage set goodsid=:goodsid, goodsname=:goodsname where goodsid = :updatedId";
                updatequery.prepare(update_sql);
                updatequery.bindValue(":updatedId", updatedId);

                updatequery.bindValue(":goodsid", goodsIdLineEdit->text());
                updatequery.bindValue(":goodsname", goodsNameLineEdit->text());

                if(!updatequery.exec())
                    qDebug() << updatequery.lastError();

            }



            msgLabel->setText("<h3><font color=red>商品信息修改成功！</font></h3>");

            tableModel->item(rowNum, 0)->setText(goodsIdLineEdit->text());
            tableModel->item(rowNum, 1)->setText(goodsNameLineEdit->text());
            tableModel->item(rowNum, 2)->setText(goodsFormatLineEdit->text());
            tableModel->item(rowNum, 3)->setText(goodsClassLineEdit->text());
            tableModel->item(rowNum, 4)->setText(goodsUnitLineEdit->text());
            tableModel->item(rowNum, 5)->setText(goodsSaveLineEdit->text());
            tableModel->item(rowNum, 6)->setText(goodsPriceLineEdit->text());
            tableModel->item(rowNum, 7)->setText(goodsremarksTextEdit->toPlainText());
            tableModel->item(rowNum, 8)->setText(goodsStatusComboBox->currentText());
            if(goodsStatusComboBox->currentText()=="停用")
            {
                tableModel->item(rowNum,8)->setBackground(QBrush(QColor(255, 0, 0)));
            }
            else
            {
                tableModel->item(rowNum,8)->setBackground(QBrush(QColor(255, 255, 255)));

            }

            clearEdit();
        }

            oper=0;
            break;
    }
    case 0:
    {
        msgLabel->setText("<h3><font color=red>当前操作：添加商品信息</font></h3>");

        QString insert_sql = "insert into goods values (?,?,?,?,?,?,?,?,?,?)";
        query.prepare(insert_sql);

        query.addBindValue(goodsIdLineEdit->text());
        query.addBindValue(goodsNameLineEdit->text());
        query.addBindValue(goodsFormatLineEdit->text());
        query.addBindValue(goodsClassLineEdit->text());
        query.addBindValue(goodsUnitLineEdit->text());
        query.addBindValue(goodsSaveLineEdit->text().toDouble());
        query.addBindValue(goodsPriceLineEdit->text().toDouble());
        query.addBindValue(goodsremarksTextEdit->toPlainText());
        query.addBindValue(goodsStatusComboBox->currentText());
        QString status=goodsStatusComboBox->currentText();
        status=status.simplified();
        if(status=="在售")
        {
            query.addBindValue(1);
        }
        else
        {
            query.addBindValue(0);
        }

        if(!query.exec())
        {
            QString waring="已经存在编号为："+goodsIdLineEdit->text()+" 的商品的信息,商品信息添加失败,请进行其他的操作！";
            QMessageBox::warning(this,"警告",waring);
            clearEdit();
        }
        else
        {
            int rowCount=tableModel->rowCount();
            tableModel->setItem(rowCount,0,new QStandardItem(goodsIdLineEdit->text()));
            tableModel->setItem(rowCount,1,new QStandardItem(goodsNameLineEdit->text()));
            tableModel->setItem(rowCount,2,new QStandardItem(goodsFormatLineEdit->text()));
            tableModel->setItem(rowCount,3,new QStandardItem(goodsClassLineEdit->text()));
            tableModel->setItem(rowCount,4,new QStandardItem(goodsUnitLineEdit->text()));
            //tableModel->setItem(i,5,new QStandardItem(goodsstatusid));
            tableModel->setItem(rowCount,5,new QStandardItem(goodsSaveLineEdit->text()));
            tableModel->setItem(rowCount,6,new QStandardItem(goodsPriceLineEdit->text()));
            tableModel->setItem(rowCount,7,new QStandardItem(goodsremarksTextEdit->toPlainText()));
            tableModel->setItem(rowCount,8,new QStandardItem(goodsStatusComboBox->currentText()));
            if(goodsStatusComboBox->currentText()=="停用")
            {
                tableModel->item(rowCount,8)->setBackground(QBrush(QColor(255, 0, 0)));
            }
            else
            {
                tableModel->item(rowCount,8)->setBackground(QBrush(QColor(255, 255, 255)));

            }
            clearEdit();
            msgLabel->setText("<h3><font color=red>商品信息添加成功！</font></h3>");


        }

    break;
    }
    }

}

void GoodsManagement::recvOk()
{
     import->quit();
     delete import;
     import=NULL;
    msgLabel->setText("<h3><font color=red>数据导入成功!</font></h3>");
    QMessageBox::information(this,"提示","数据导入成功");

}

void GoodsManagement::importFun()
{
    QString fileName = QFileDialog::getOpenFileName(this);
    if(!fileName.isEmpty())
    {
        if(fileName.right(4)!="xlsx")
        {
            QMessageBox::warning(this,tr("警告"),tr("导入的Excel表格格式不支持，请导入xlsx格式的表格！"));
            return ;
        }
        import=new ImportExcelThread(this,fileName);
        import->start();
        msgLabel->setText("<h3><font color=red>数据导入中......</font></h3>");
        connect(import,SIGNAL(sendBuf(const QString)),this,SLOT(updataTabeleView(const QString)),Qt::QueuedConnection);
        connect(import,SIGNAL(sendOk()),this,SLOT(recvOk()));
    }
}

void GoodsManagement::updataTabeleView(const QString Qbuf)
{
    //flag=false;
    msgLabel->setText("<h3><font color=red>数据导入中.......</font></h3>");
    QStringList strlist=Qbuf.split("#");
    int rowCount=tableModel->rowCount();
    tableModel->setItem(rowCount,0,new QStandardItem(strlist[0]));
    tableModel->setItem(rowCount,1,new QStandardItem(strlist[1]));
    tableModel->setItem(rowCount,2,new QStandardItem(strlist[2]));
    tableModel->setItem(rowCount,3,new QStandardItem(strlist[3]));
    tableModel->setItem(rowCount,4,new QStandardItem(strlist[4]));
    //tableModel->setItem(i,5,new QStandardItem(goodsstatusid));
    tableModel->setItem(rowCount,5,new QStandardItem(strlist[5]));
    tableModel->setItem(rowCount,6,new QStandardItem(strlist[6]));
    tableModel->setItem(rowCount,7,new QStandardItem(strlist[7]));
    tableModel->setItem(rowCount,8,new QStandardItem(strlist[8]));
    if(strlist[8]=="停用")
    {
        tableModel->item(rowCount,8)->setBackground(QBrush(QColor(255, 0, 0)));
    }
    //flag=true;


}

void GoodsManagement::selectShow()
{
    QString select_sql = "select * from goods";
    QSqlQuery query;
    int i=0;
    if(!query.exec(select_sql))
    {
        qDebug()<<query.lastError();
    }
    else
    {

        while(query.next())
        {
            goodsid=query.value("goodsid").toString();
            goodsname=query.value("goodsname").toString();
            goodsformat=query.value("goodsformat").toString();;
            goodsclass=query.value("goodsclass").toString();;
            goodsunit=query.value("goodsunit").toString();;
            goodsstatus=query.value("goodsstatus").toString();;
            goodsstatusid=query.value("goodsstatusid").toInt();
            goodssave=query.value("goodssave").toString();
            goodsprice=query.value("goodsprice").toString();
            goodsremarks=query.value("goodsremarks").toString();



            tableModel->setItem(i,0,new QStandardItem(goodsid));
            tableModel->setItem(i,1,new QStandardItem(goodsname));
            tableModel->setItem(i,2,new QStandardItem(goodsformat));
            tableModel->setItem(i,3,new QStandardItem(goodsclass));
            tableModel->setItem(i,4,new QStandardItem(goodsunit));
            //tableModel->setItem(i,5,new QStandardItem(goodsstatusid));
            tableModel->setItem(i,5,new QStandardItem(goodssave));
            tableModel->setItem(i,6,new QStandardItem(goodsprice));
            tableModel->setItem(i,7,new QStandardItem(goodsremarks));
            tableModel->setItem(i,8,new QStandardItem(goodsstatus));
            if(goodsstatus=="停用")
            {
                tableModel->item(i,8)->setBackground(QBrush(QColor(255, 0, 0)));
            }
            else
            {
                tableModel->item(i,8)->setBackground(QBrush(QColor(255, 255, 255)));

            }
            i++;
        }
    }
}
GoodsManagement::~GoodsManagement()
{
    //import->deleteLater();
}
