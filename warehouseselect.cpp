#include "warehouseselect.h"

#include <QFileDialog>
WareHouseSelect::WareHouseSelect(QWidget *parent)
    : QMainWindow(parent)
{
    setWindowIcon(QIcon(":/mainImag/nuoya.png"));

    createList();
    this->setFixedSize(1010,700);
    this->setAttribute(Qt::WA_QuitOnClose,false);

    createTableView();
    createLabel_LineEdit();
    createButton();

}
void WareHouseSelect::createButton()
{
    exportButton=new QPushButton(tr("导出excel"),this);
    exportButton->setGeometry(800,60,100,40);
    connect(exportButton,SIGNAL(clicked()),this,SLOT(exportFun()));


    /*printButton=new QPushButton(tr("打印"),this);
    printButton->setGeometry(640,60,100,40);
    connect(printButton,SIGNAL(clicked()),this,SLOT(printFun()));*/



    selectButton=new QPushButton(this);
    selectButton->setStyleSheet("background-image:url(:/mainImag/search.png);");
    selectButton->setGeometry(538,19,35,32);
    connect(selectButton,SIGNAL(clicked()),this,SLOT(selectFun()));


}
void WareHouseSelect::createList()
{
    selectList.clear();

    QString select_sql = "select goodsid ,goodsname from goodsstorage";
    QSqlQuery query;
    query.prepare(select_sql);
    query.exec();
    while(query.next())
    {
        selectList.append(query.value("goodsid").toString());
        selectList.append(query.value("goodsname").toString());
    }

}
void WareHouseSelect::createTableView()
{
    mainTableView=new QTableView(this);
    mainTableView->setGeometry(30,150,950,500);
    tableModel = new QStandardItemModel();
    mainTableView->setEditTriggers(QTableView::NoEditTriggers);

    tableModel->setHorizontalHeaderItem(0, new QStandardItem(QObject::tr("产品编号 ")));
    tableModel->setHorizontalHeaderItem(1, new QStandardItem(QObject::tr("产品名称 ")));

    tableModel->setHorizontalHeaderItem(2, new QStandardItem(QObject::tr("出库数量 ")));
    tableModel->setHorizontalHeaderItem(3, new QStandardItem(QObject::tr("计量单位 ")));
    tableModel->setHorizontalHeaderItem(4, new QStandardItem(QObject::tr("出库单价 ")));

    tableModel->setHorizontalHeaderItem(5, new QStandardItem(QObject::tr("出库总价 ")));
    tableModel->setHorizontalHeaderItem(6, new QStandardItem(QObject::tr("出库类型 ")));
    tableModel->setHorizontalHeaderItem(7, new QStandardItem(QObject::tr("安全库存 ")));
    tableModel->setHorizontalHeaderItem(8, new QStandardItem(QObject::tr("产品状态 ")));
    tableModel->setHorizontalHeaderItem(9, new QStandardItem(QObject::tr("备注 ")));
    tableModel->setHorizontalHeaderItem(10, new QStandardItem(QObject::tr("出库时间 ")));


    mainTableView->setModel(tableModel);

}
void WareHouseSelect::createLabel_LineEdit()
{
    selectLabel=new QLabel(tr("请选择查询条件:"),this);
    selectLabel->setGeometry(50,20,190,30);
    selectComboBox=new QComboBox(this);
    selectComboBox->addItem(tr("日期"));
    selectComboBox->addItem(tr("名称"));
    selectComboBox->addItem(tr("编码"));

    selectComboBox->setGeometry(170,20,80,30);
    selectLineEdit=new QLineEdit(this);
    selectLineEdit->setGeometry(310,20,230,30);
    selectCompleter = new QCompleter(selectList);
    selectCompleter->setCaseSensitivity(Qt::CaseInsensitive);//大小写匹配
    selectCompleter->setCompletionMode(QCompleter::PopupCompletion); //匹配以弹出式显示  （2）
    selectLineEdit->setCompleter(selectCompleter);


    setLabel=new QLabel(tr("指定查询日期 "),this);
    setLabel->setGeometry(170,70,100,30);


    fromLabel=new QLabel(tr("从"),this);
    fromLabel->setGeometry(290,70,30,30);

    fromlineedit = new MyLineEdit(this);

    fromlineedit->setGeometry(310,70,100,30);
    fromCaledar = new QCalendarWidget(this);
    fromCaledar->setGeometry(250,110,300,300);
    fromCaledar->hide();
    connect(fromlineedit,SIGNAL(clicked()),fromCaledar,SLOT(show()));
    connect(fromlineedit,SIGNAL(textChanged(QString)),fromCaledar,SLOT(show()));
    connect(fromCaledar,SIGNAL(clicked(QDate)),this,SLOT(fromOk()));


    toLabel=new QLabel(tr("到"),this);
    toLabel->setGeometry(420,70,100,30);
    tolineedit = new MyLineEdit(this);

    tolineedit->setGeometry(440,70,100,30);
    toCaledar = new QCalendarWidget(this);
    toCaledar->setGeometry(300,110,300,300);
    toCaledar->hide();
    connect(tolineedit,SIGNAL(clicked()),toCaledar,SLOT(show()));
    connect(tolineedit,SIGNAL(textChanged(QString)),toCaledar,SLOT(show()));
    connect(toCaledar,SIGNAL(clicked(QDate)),this,SLOT(toOk()));

}
void WareHouseSelect::fromOk()
{
    QDate date = fromCaledar->selectedDate();
    fromlineedit->setText(date.toString("yyyy-MM-dd"));
    fromCaledar->hide();
}
void WareHouseSelect::toOk()
{
    QDate date = toCaledar->selectedDate();

    tolineedit->setText(date.toString("yyyy-MM-dd"));
    toCaledar->hide();
}

void WareHouseSelect::paintEvent(QPaintEvent*)

{
    QPainter painter(this);
    QPixmap pix;
    pix.load(":/mainImag/background.png");
    painter.drawPixmap(0,0,this->width(),this->height(),pix);
}
void WareHouseSelect::showStatus()
{
    exportthread->quit();
    delete exportthread;
    exportthread=NULL;
    QMessageBox::information(this,"提示","数据导出成功！");
}
void WareHouseSelect::exportFun()
{
    QString fileName = QFileDialog::getSaveFileName(this,
        tr("保存excel"),
        "未命名.xlsx",
        tr("*.xlsx")); //选择路径
    if(fileName.isEmpty())
    {
        return;
    }
    else
    {
        int row=tableModel->rowCount();
        int cloumn=tableModel->columnCount();
        exportthread=new ExportExcelThread(this,fileName,warehouseList,row,cloumn);
        exportthread->start();
        connect(exportthread,SIGNAL(sendStatus()),this,SLOT(showStatus()));
    }
}
void WareHouseSelect::printFun()
{

}


void WareHouseSelect::clearTableView()
{
    int totalRow = tableModel->rowCount();

    if (totalRow != 0)
    {
        for (int i = 0; i < totalRow; i++)
        {
            int remainRow = tableModel->rowCount();
            tableModel->removeRow(remainRow -1);
        }
    }
}
void WareHouseSelect::selectFun()
{
    createList();
    clearTableView();
    QSqlQuery query;
    QString select_sql;
    int i=0;

    int  condition=selectComboBox->currentIndex();
    QString conditionStr1,conditionStr2;
    /*select_sql = "select goodsid ,goodsname,inputcount,inputprice,inputtotal,inputtype,\
                inputtime,customsid from :tableName where inputtime Between :conditionStr1 and  conditionStr2";*/
    switch(condition)
    {
    case 0:
    {
        conditionStr1=fromlineedit->text();
        conditionStr2=tolineedit->text();
        QString info=conditionStr1+"   "+conditionStr2;
        if(!(fromlineedit->text().isEmpty()&&tolineedit->text().isEmpty()))
            selectLineEdit->setText(info);
        else
        {
            QMessageBox::warning(this,"警告","请选择查询的日期！");
            return ;
        }


        select_sql = "select   goodsoutput.goodsid,goodsoutput.goodsname,goodsoutput.outputcount ,goods.goodsunit,\
                goodsoutput.outputprice,goodsoutput.outputtotal,goodsoutput.outputtype,\
                goods.goodssave,goods.goodsstatus,goods.goodsremarks,goodsoutput.outputtime from\
                goods,goodsoutput where goodsoutput.id in\
                (  select id from goodsoutput where outputtime>=:conditionStr1 and outputtime<=:conditionStr2) \
                 and goods.goodsid=goodsoutput.goodsid";

        query.prepare(select_sql);
        query.bindValue(":conditionStr1",QDateTime::fromString(conditionStr1, "yyyy-mm-dd"));
        query.bindValue(":conditionStr2",QDateTime::fromString(conditionStr2, "yyyy-MM-dd"));
        qDebug() << QDateTime::fromString(conditionStr1, "yyyy-MM-dd");
        break;
    }

    case 1:
    {
        conditionStr1=selectLineEdit->text();
        select_sql = "select   goodsoutput.goodsid,goodsoutput.goodsname,goodsoutput.outputcount ,goods.goodsunit,\
                goodsoutput.outputprice,goodsoutput.outputtotal,goodsoutput.outputtype,\
                goods.goodssave,goods.goodsstatus,goods.goodsremarks,goodsoutput.outputtime from\
                goods,goodsoutput where goodsoutput.goodsname in(select goodsname from goodsoutput \
                                                             where goodsname=:conditionStr1 ) and goods.goodsname=goodsoutput.goodsname";
        if(conditionStr1.isEmpty())
        {
            QMessageBox::warning(this,"警告","请输入查询的商品名字！");
            return ;
        }
        query.prepare(select_sql);
        query.bindValue(":conditionStr1",conditionStr1);
        break;
    }
    case 2:
    {
        conditionStr1=selectLineEdit->text();

        select_sql = "select   goodsoutput.goodsid,goodsoutput.goodsname,goodsoutput.outputcount ,goods.goodsunit,\
                goodsoutput.outputprice,goodsoutput.outputtotal,goodsoutput.outputtype,\
                goods.goodssave,goods.goodsstatus,goods.goodsremarks,goodsoutput.outputtime from\
                goods,goodsoutput where goodsoutput.goodsid in(select goodsid from goodsoutput \
                                                             where goodsid=:conditionStr1 ) and goods.goodsid=goodsoutput.goodsid";

        if(conditionStr1.isEmpty())
        {
            QMessageBox::warning(this,"警告","请输入查询的商品编号！");
            return ;
        }
        query.prepare(select_sql);
        query.bindValue(":conditionStr1",conditionStr1);
        break;
    }
    }
    if(!query.exec())
    {
        qDebug()<<query.lastError();
    }
    else
    {
        //goodsid ,goodsname,inputcount,inputprice,inputtotal,inputtype,inputtime,customsid
        warehouseList.clear();
        warehouseList.append("产品编号");
        warehouseList.append("产品名称");
        warehouseList.append("出库数量");
        warehouseList.append("计量单位");
        warehouseList.append("出库单价");
        warehouseList.append("出库总价");
        warehouseList.append("出库类型");
        warehouseList.append("安全库存");
        warehouseList.append("产品状态");
        warehouseList.append("备注");
        warehouseList.append("出库时间");
        while(query.next())
        {
            tableModel->setItem(i,0,new QStandardItem(query.value("goodsid").toString()));
            warehouseList.append(query.value("goodsid").toString());

            tableModel->setItem(i,1,new QStandardItem(query.value("goodsname").toString()));
            warehouseList.append(query.value("goodsname").toString());

            tableModel->setItem(i,2,new QStandardItem(query.value("outputcount").toString()));
            warehouseList.append(query.value("outputcount").toString());

            tableModel->setItem(i,3,new QStandardItem(query.value("goodsunit").toString()));
            warehouseList.append(query.value("goodsunit").toString());


            tableModel->setItem(i,4,new QStandardItem(query.value("outputprice").toString()));
            warehouseList.append(query.value("outputprice").toString());


            tableModel->setItem(i,5,new QStandardItem(query.value("outputtotal").toString()));
            warehouseList.append(query.value("outputtotal").toString());

            tableModel->setItem(i,6,new QStandardItem(query.value("outputtype").toString()));
            warehouseList.append(query.value("outputtype").toString());

            tableModel->setItem(i,7,new QStandardItem(query.value("goodssave").toString()));
            warehouseList.append(query.value("goodssave").toString());

            tableModel->setItem(i,8,new QStandardItem(query.value("goodsstatus").toString()));
            warehouseList.append(query.value("goodsstatus").toString());

            if(query.value("goodsstatus").toString()=="停用")
            {
                tableModel->item(i,8)->setBackground(QBrush(QColor(255,0, 0)));
            }
            else
            {
                tableModel->item(i,8)->setBackground(QBrush(QColor(255, 255, 255)));

            }
            tableModel->setItem(i,9,new QStandardItem(query.value("goodsremarks").toString()));
            warehouseList.append(query.value("goodsremarks").toString());


            tableModel->setItem(i,10,new QStandardItem(query.value("outputtime").toDate().toString("yyyy-MM-dd")));
            warehouseList.append(query.value("outputtime").toDate().toString("yyyy-MM-dd"));


            i++;
        }
    }
}
