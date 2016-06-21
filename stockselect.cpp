#include "stockselect.h"
#include <QFileDialog>
StockSelect::StockSelect(QWidget *parent)
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
void StockSelect::createButton()
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
void StockSelect::createTableView()
{
    mainTableView=new QTableView(this);
    mainTableView->setGeometry(30,150,950,500);
    tableModel = new QStandardItemModel();
    mainTableView->setEditTriggers(QTableView::NoEditTriggers);

    tableModel->setHorizontalHeaderItem(0, new QStandardItem(QObject::tr("产品编号 ")));
    tableModel->setHorizontalHeaderItem(1, new QStandardItem(QObject::tr("产品名称 ")));

    tableModel->setHorizontalHeaderItem(2, new QStandardItem(QObject::tr("入库数量 ")));
    tableModel->setHorizontalHeaderItem(3, new QStandardItem(QObject::tr("计量单位 ")));
    tableModel->setHorizontalHeaderItem(4, new QStandardItem(QObject::tr("入库单价 ")));

    tableModel->setHorizontalHeaderItem(5, new QStandardItem(QObject::tr("入库总价 ")));
    tableModel->setHorizontalHeaderItem(6, new QStandardItem(QObject::tr("入库类型 ")));
    tableModel->setHorizontalHeaderItem(7, new QStandardItem(QObject::tr("安全库存 ")));
    tableModel->setHorizontalHeaderItem(8, new QStandardItem(QObject::tr("产品状态 ")));
    tableModel->setHorizontalHeaderItem(9, new QStandardItem(QObject::tr("备注 ")));
    tableModel->setHorizontalHeaderItem(10, new QStandardItem(QObject::tr("入库时间 ")));




    mainTableView->setModel(tableModel);

}
void StockSelect::createLabel_LineEdit()
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
void StockSelect::createList()
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
void StockSelect::fromOk()
{
    QDate date = fromCaledar->selectedDate();

    fromlineedit->setText(date.toString("yyyy-MM-dd"));
    fromCaledar->hide();
}
void StockSelect::toOk()
{
    QDate date = toCaledar->selectedDate();

    tolineedit->setText(date.toString("yyyy-MM-dd"));
    toCaledar->hide();
}

void StockSelect::paintEvent(QPaintEvent*)

{
    QPainter painter(this);
    QPixmap pix;
    pix.load(":/mainImag/background.png");
    painter.drawPixmap(0,0,this->width(),this->height(),pix);
}
void StockSelect::showStatus()
{
    exportthread->quit();
    delete exportthread;
    exportthread=NULL;
    QMessageBox::information(this,"提示","数据导出成功！");
}
void StockSelect::exportFun()
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
        exportthread=new ExportExcelThread(this,fileName,stockList,row,cloumn);
        exportthread->start();
        connect(exportthread,SIGNAL(sendStatus()),this,SLOT(showStatus()));
    }
}
void StockSelect::printFun()
{

}

void StockSelect::clearTableView()
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
void StockSelect::selectFun()
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
        /*conditionStr1="\""+conditionStr1+"\"";
        conditionStr2="\""+conditionStr2+"\"";*/

        select_sql = "select   goodsinput.goodsid,goodsinput.goodsname,goodsinput.inputcount ,goods.goodsunit,\
                goodsinput.inputprice,goodsinput.inputtotal,goodsinput.inputtype,\
                goods.goodssave,goods.goodsstatus,goods.goodsremarks,goodsinput.inputtime from\
                goods,goodsinput where goodsinput.id in\
                (  select id from goodsinput where inputtime>=:conditionStr1 and inputtime<=:conditionStr2) \
                 and goods.goodsid=goodsinput.goodsid";

        query.prepare(select_sql);
        query.bindValue(":conditionStr1",QDateTime::fromString(conditionStr1, "yyyy-MM-dd"));
        query.bindValue(":conditionStr2",QDateTime::fromString(conditionStr2, "yyyy-MM-dd"));
        break;
    }

    case 1:
    {
        conditionStr1=selectLineEdit->text();
        select_sql = "select   goodsinput.goodsid,goodsinput.goodsname,goodsinput.inputcount ,goods.goodsunit,\
                goodsinput.inputprice,goodsinput.inputtotal,goodsinput.inputtype,\
                goods.goodssave,goods.goodsstatus,goods.goodsremarks,goodsinput.inputtime from\
                goods,goodsinput where goodsinput.goodsname in(select goodsname from goodsinput \
                                                             where goodsname=:conditionStr1 ) and goods.goodsname=goodsinput.goodsname";
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

        select_sql = "select   goodsinput.goodsid,goodsinput.goodsname,goodsinput.inputcount ,goods.goodsunit,\
                goodsinput.inputprice,goodsinput.inputtotal,goodsinput.inputtype,\
                goods.goodssave,goods.goodsstatus,goods.goodsremarks,goodsinput.inputtime from\
                goods,goodsinput where goodsinput.goodsid in(select goodsid from goodsinput \
                                                             where goodsid=:conditionStr1 ) and goods.goodsid=goodsinput.goodsid";

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
        stockList.clear();
        stockList.append("产品编号");
        stockList.append("产品名称");
        stockList.append("入库数量");
        stockList.append("计量单位");
        stockList.append("入库单价");
        stockList.append("入库总价");
        stockList.append("入库类型");
        stockList.append("安全库存");
        stockList.append("产品状态");
        stockList.append("备注");
        stockList.append("入库时间");

        while(query.next())
        {
            tableModel->setItem(i,0,new QStandardItem(query.value("goodsid").toString()));
            stockList.append(query.value("goodsid").toString());

            tableModel->setItem(i,1,new QStandardItem(query.value("goodsname").toString()));
            stockList.append(query.value("goodsname").toString());

            tableModel->setItem(i,2,new QStandardItem(query.value("inputcount").toString()));
            stockList.append(query.value("inputcount").toString());

            tableModel->setItem(i,3,new QStandardItem(query.value("goodsunit").toString()));
            stockList.append(query.value("goodsunit").toString());

            tableModel->setItem(i,4,new QStandardItem(query.value("inputprice").toString()));
            stockList.append(query.value("inputprice").toString());

            tableModel->setItem(i,5,new QStandardItem(query.value("inputtotal").toString()));
            stockList.append(query.value("inputtotal").toString());

            tableModel->setItem(i,6,new QStandardItem(query.value("inputtype").toString()));
            stockList.append(query.value("inputtype").toString());

            tableModel->setItem(i,7,new QStandardItem(query.value("goodssave").toString()));
            stockList.append(query.value("goodssave").toString());

            tableModel->setItem(i,8,new QStandardItem(query.value("goodsstatus").toString()));
            stockList.append(query.value("goodsstatus").toString());

            if(query.value("goodsstatus").toString()=="停用")
            {
                tableModel->item(i,8)->setBackground(QBrush(QColor(255,0, 0)));
            }
            else
            {
                tableModel->item(i,8)->setBackground(QBrush(QColor(255, 255, 255)));

            }
            tableModel->setItem(i,9,new QStandardItem(query.value("goodsremarks").toString()));
            stockList.append(query.value("goodsremarks").toString());

            tableModel->setItem(i,10,new QStandardItem(query.value("inputtime").toDate().toString("yyyy-MM-dd")));
            stockList.append(query.value("inputtime").toDate().toString("yyyy-MM-dd"));

            i++;
        }
    }
}
