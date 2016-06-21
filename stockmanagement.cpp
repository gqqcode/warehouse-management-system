#include "stockmanagement.h"
#include <QDebug>
StockManagement::StockManagement(QWidget *parent)
    : QMainWindow(parent)
{
    setWindowIcon(QIcon(":/mainImag/nuoya.png"));

    this->setAttribute(Qt::WA_QuitOnClose,false);

    this->setFixedSize(1070,700);
    this->setWindowTitle(tr("入库单"));
    createIdList(NULL);

    createAction();
    createLabel_LineEdit();
    createButton();
    createTableView();
    connect(goodsidLineEdit,SIGNAL(textChanged(QString)),this,SLOT(setGoodsName(QString)));
    connect(inputcountLineEdit,SIGNAL(textChanged(QString)),this,SLOT(setinputTotal(QString)));
    connect(inputpriceLineEdit,SIGNAL(textChanged(QString)),this,SLOT(setinputTotal(QString)));

    connect(goodsidLineEdit,SIGNAL(textChanged(QString)),this,SLOT(createIdList(QString)));
    connect(goodsidLineEdit,SIGNAL(textChanged(QString)),this,SLOT(createIdList(QString)));


    selectShow();

}
void StockManagement::selectShow()
{
    QString select_sql = "select goodsid ,goodsname,inputcount,inputprice,inputtotal,inputtype,inputtime,customsid from goodsinput";
    QSqlQuery query;
    int i=0;
    if(!query.exec(select_sql))
    {
        qDebug()<<query.lastError();
    }
    else
    {
        //goodsid ,goodsname,inputcount,inputprice,inputtotal,inputtype,inputtime,customsid

        while(query.next())
        {
            tableModel->setItem(i,0,new QStandardItem(query.value("goodsid").toString()));
            tableModel->setItem(i,1,new QStandardItem(query.value("goodsname").toString()));
            tableModel->setItem(i,2,new QStandardItem(query.value("inputcount").toString()));
            tableModel->setItem(i,3,new QStandardItem(query.value("inputprice").toString()));
            tableModel->setItem(i,4,new QStandardItem(query.value("inputtotal").toString()));
            tableModel->setItem(i,5,new QStandardItem(query.value("inputtype").toString()));
            tableModel->setItem(i,6,new QStandardItem(query.value("inputtime").toDate().toString("yyyy-MM-dd")));
            int index=query.value("customsid").toInt();
            if(index>=0&&index<customsIdList.length())
                tableModel->setItem(i,7,new QStandardItem(customsNameList.operator [](index)));
            else
                tableModel->setItem(i,7,new QStandardItem(query.value("customsid").toString()));
            i++;
        }
    }
}
void StockManagement::setinputTotal(const QString count)
{
    double total=(count.toDouble())*(inputpriceLineEdit->text().toDouble());
    inputtotalLineEdit->setText(QString::number(total,'f', 2));
}
void StockManagement::setGoodsName(QString goodsid)
{
    int index=goodsIdList.indexOf(goodsid);

    if(index>=0&&index<goodsIdList.length())
    {
        goodsnameLineEdit->setText(goodsNameList.operator [](index));
        inputpriceLineEdit->setText(goodspriceList.operator [](index));
    }
    else
        goodsnameLineEdit->clear();

}
void StockManagement::createIdList(QString temp)
{

    customsNameList.clear();
    customsIdList.clear();
    goodsIdList.clear();
    goodsNameList.clear();
    goodspriceList.clear();

    QString select_sql = "select name,id from customs";
    QSqlQuery query;
    query.prepare(select_sql);
    query.exec();
    while(query.next())
    {
        customsNameList.append(query.value("name").toString());
        customsIdList.append(query.value("id").toString());
    }

    select_sql = "select goodsid,goodsname,goodsprice from goods";
    query.prepare(select_sql);
    query.exec();

    while(query.next())
    {

        goodsIdList.append(query.value("goodsid").toString());
        goodsNameList.append(query.value("goodsname").toString());
        goodspriceList.append(query.value("goodsprice").toString());

    }


    //customsNamecompleter=new QCompleter(customsNameList);////////////////////////
    //goodscompleter = new QCompleter(goodsIdList);


}



void StockManagement::createButton()
{
    enterButton=new QPushButton(tr("确定入库"),this);
    enterButton->setGeometry(800,100,110,50);
    connect(enterButton,SIGNAL(clicked()),this,SLOT(saveFun()));


}
void StockManagement::createTableView()
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

    mainTableView=new QTableView(this);
    mainTableView->setGeometry(100,240,860,400);
    //mainTableView->setAlternatingRowColors(true);//"QTableView{background-color: rgb(30,144,255);"
    mainTableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    mainTableView->setEditTriggers(QTableView::NoEditTriggers);

    mainTableView->setContextMenuPolicy(Qt::CustomContextMenu);
    tableModel = new QStandardItemModel();

    tableModel->setHorizontalHeaderItem(0, new QStandardItem(QObject::tr("产品编号 ")));
    tableModel->setHorizontalHeaderItem(1, new QStandardItem(QObject::tr("产品名称 ")));
    tableModel->setHorizontalHeaderItem(2, new QStandardItem(QObject::tr("入库数量 ")));
    tableModel->setHorizontalHeaderItem(3, new QStandardItem(QObject::tr("入库单价 ")));
    tableModel->setHorizontalHeaderItem(4, new QStandardItem(QObject::tr("入库总价 ")));

    tableModel->setHorizontalHeaderItem(5, new QStandardItem(QObject::tr("入库类型 ")));
    tableModel->setHorizontalHeaderItem(6, new QStandardItem(QObject::tr("入库时间 ")));
    tableModel->setHorizontalHeaderItem(7, new QStandardItem(QObject::tr("客户名 ")));
    mainTableView->setModel(tableModel);

}
void StockManagement::createLabel_LineEdit()
{
    goodsnameLabel=new QLabel(this);


    goodsidLabel=new QLabel(this);
    goodsidLabel->setText(tr("产品编号:"));
    goodsidLabel->setGeometry(100,55,80,40);
    goodsidLineEdit=new QLineEdit(this);
    goodsidLineEdit->setGeometry(180,57,200,30);

    goodscompleter = new QCompleter(goodsIdList);
    goodscompleter->setCaseSensitivity(Qt::CaseInsensitive);//大小写匹配
    goodscompleter->setCompletionMode(QCompleter::PopupCompletion); //匹配以弹出式显示  （2）
    goodsidLineEdit->setCompleter(goodscompleter);


    goodsnameLabel->setText(tr("产品名称:"));
    goodsnameLabel->setGeometry(450,55,80,40);
    goodsnameLineEdit=new QLineEdit(this);
    goodsnameLineEdit->setGeometry(530,57,200,30);



    inputcountLabel=new QLabel(tr("入库数量:"),this);
    inputcountLabel->setGeometry(100,90,80,40);
    inputcountLineEdit=new QLineEdit(this);
    inputcountLineEdit->setGeometry(180,95,200,30);
    QRegExp regExp1("[1-9][0-9]+$");
    QValidator *validator1 = new QRegExpValidator(regExp1, inputcountLineEdit );//正则表达式

    inputcountLineEdit->setValidator(validator1);



    inputpriceLabel=new QLabel(tr("入库单价:"),this);
    inputpriceLabel->setGeometry(450,90,80,40);
    inputpriceLineEdit=new QLineEdit(this);
    inputpriceLineEdit->setGeometry(530,95,200,30);
    QRegExp regExp2("[1-9][0-9]+$");
    QValidator *validator2 = new QRegExpValidator(regExp2, inputpriceLineEdit );//正则表达式

    inputpriceLineEdit->setValidator(validator2);


    inputtimeLabel=new QLabel(tr("入库时间:"),this);
    inputtimeLabel->setGeometry(100,170,80,40);
    inputtimeLineEdit=new QLineEdit(this);
    inputtimeLineEdit->setGeometry(180,172,200,30);
    QDateTime time = QDateTime::currentDateTime();//获取系统现在的时间
    inputtimeLineEdit->setText(time.toString("yyyy-MM-dd"));///////////////////////////////////////////////////////
    inputtimeLineEdit->setEnabled(false);

    inputtotalLabel=new QLabel(tr("入库总价:"),this);
    inputtotalLabel->setGeometry(100,125,80,40);
    inputtotalLineEdit=new QLineEdit(this);
    inputtotalLineEdit->setGeometry(180,133,200,30);

    inputtypeLabel=new QLabel(tr("入库类型"),this);
    inputtypeLabel->setGeometry(450,125,80,40);
    inputtypeComboBox=new QComboBox(this);
    inputtypeComboBox->addItem(tr("其他入库"));
    inputtypeComboBox->addItem(tr("采购入库"));
    inputtypeComboBox->setGeometry(530,133,200,30);

    customsnameLabel=new QLabel(tr("客户名称:"),this);
    customsnameLabel->setGeometry(450,170,80,40);
    customsnameLineEdit=new QLineEdit(this);
    customsNamecompleter = new QCompleter(customsNameList);

    customsNamecompleter->setCaseSensitivity(Qt::CaseInsensitive);//大小写匹配
    customsNamecompleter->setCompletionMode(QCompleter::PopupCompletion); //匹配以弹出式显示  （2）
    customsnameLineEdit->setCompleter(customsNamecompleter);
    customsnameLineEdit->setGeometry(530,172,200,30);
}
void StockManagement::paintEvent(QPaintEvent*)

{
    QPainter painter(this);
    QPixmap pix;
    pix.load(":/mainImag/background.png");
    painter.drawPixmap(0,0,this->width(),this->height(),pix);
}

void StockManagement::createAction()
{

    alterAct=new QAction(QIcon(":/image/alter.png"),tr("修改"),this);
    connect(alterAct,SIGNAL(triggered()),this,SLOT(alterRecord()));



    deleteAct=new QAction(QIcon(":/image/alter.png"),tr("删除"),this);
    connect(deleteAct,SIGNAL(triggered()),this,SLOT(deleteRecord()));


}



void StockManagement::alterRecord()
{
    QMessageBox::information(this,"提示","修改");
}


void StockManagement::deleteRecord()
{
    QMessageBox::information(this,"提示","删除");
}

void StockManagement::showContextMenu(const QPoint& pos)//contextMenuEvent(QContextMenuEvent * event)
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
        rightMenu->exec(QCursor::pos()); // 菜单出现的位置为当前鼠标的位置
    }

}
bool StockManagement::isExist(QString selectedId)
{
    QString select_sql = "select goodsid from goodsstorage where goodsid=:selectedId";
    QSqlQuery query;
    query.prepare(select_sql);
    query.bindValue(":selectedId",selectedId);

    if(!query.exec())
        qDebug() << query.lastError();
    int i=0;
    while(query.next())
    {
        i=i+1;
    }
    if(i>=1)
    {
        i=0;
        return true;
    }
    else
        return false;
}
bool StockManagement::isExistGoods(QString selectedId)
{
    QString select_sql = "select goodsid from goods where goodsid=:selectedId";
    QSqlQuery query;
    query.prepare(select_sql);
    query.bindValue(":selectedId",selectedId);

    if(!query.exec())
        qDebug() << query.lastError();
    int i=0;
    while(query.next())
    {
        i=i+1;
    }
    if(i>=1)
    {
        i=0;
        return true;
    }
    else
        return false;
}

void StockManagement::saveFun()
{

    createIdList(NULL);
    if(inputcountLineEdit->text().isEmpty())
    {
        QMessageBox::warning(this,"警告","请填写入库的数量！");
        return ;
    }
    if(customsnameLineEdit->text().isEmpty())
        customsnameLineEdit->setText("未填写");
    QSqlQuery query;
    if(isExistGoods(goodsidLineEdit->text()))
    {

        msgLabel->setText("<h3><font color=red>当前操作：添加入库信息</font></h3>");

        if(isExist(goodsidLineEdit->text()))//已经存在要插入的信息
        {
            QString update_sql="update goodsstorage set storagecount=storagecount+:addcount,storagetotal=storagetotal+:addtotal\
                    where goodsid = :updatedId";
            query.prepare(update_sql);
            query.bindValue(":updatedId",goodsidLineEdit->text());
            query.bindValue(":addcount",inputcountLineEdit->text().toDouble());

            query.bindValue(":addtotal",inputtotalLineEdit->text().toDouble());

            if(!query.exec())
            {
                qDebug() << query.lastError();
            }

        }
        else//库存表不存在信息
        {
            QString insert_sql = "insert into goodsstorage(storagecount,storagprice,storagetotal ,goodsid,goodsname)   values (?,?,?,?,?)";
            query.prepare(insert_sql);

            query.addBindValue(inputcountLineEdit->text().toDouble());
            query.addBindValue(inputpriceLineEdit->text().toDouble());
            query.addBindValue(inputtotalLineEdit->text().toDouble());
            query.addBindValue(goodsidLineEdit->text());
            query.addBindValue(goodsnameLineEdit->text());
            query.exec();
        }
        QString insert_sql = "insert into goodsinput(goodsid ,goodsname,inputcount,inputprice,\
                inputtotal,inputtype,inputtime,customsid)  values (?,?,?,?,?,?,?,?)";


        query.prepare(insert_sql);

        query.addBindValue(goodsidLineEdit->text());
        query.addBindValue(goodsnameLineEdit->text());
        query.addBindValue(inputcountLineEdit->text().toDouble());
        query.addBindValue(inputpriceLineEdit->text().toDouble());
        query.addBindValue(inputtotalLineEdit->text().toDouble());
        query.addBindValue(inputtypeComboBox->currentText());
        query.addBindValue(QDateTime::fromString(inputtimeLineEdit->text(), "yyyy-MM-dd"));
        query.addBindValue(goodsidLineEdit->text());



        if(!query.exec())
        {
            qDebug() << query.lastError();
            resetFun();

        }
        else
        {
            int rowCount=tableModel->rowCount();
            tableModel->setItem(rowCount,0,new QStandardItem(goodsidLineEdit->text()));
            tableModel->setItem(rowCount,1,new QStandardItem(goodsnameLineEdit->text()));
            tableModel->setItem(rowCount,2,new QStandardItem(inputcountLineEdit->text()));
            tableModel->setItem(rowCount,3,new QStandardItem(inputpriceLineEdit->text()));
            tableModel->setItem(rowCount,4,new QStandardItem(inputtotalLineEdit->text()));
            tableModel->setItem(rowCount,5,new QStandardItem(inputtypeComboBox->currentText()));
            tableModel->setItem(rowCount,6,new QStandardItem(inputtimeLineEdit->text()));
            tableModel->setItem(rowCount,7,new QStandardItem(customsnameLineEdit->text()));

            msgLabel->setText("<h3><font color=red>入库信息添加成功！</font></h3>");
            resetFun();
        }




    }
    else
    {
        QMessageBox::warning(this,"警告","商品管理中不存在该商品的信息,请你先添加商品信息,再进行入库操作，此次操作无效！");
        resetFun();
        return ;
    }

}
void StockManagement::resetFun()
{
    goodsidLineEdit->clear();
    goodsnameLineEdit->clear();
    inputcountLineEdit->clear();
    inputpriceLineEdit->clear();
    customsnameLineEdit->clear();
    inputtotalLineEdit->clear();
}
StockManagement::~StockManagement()
{

}
