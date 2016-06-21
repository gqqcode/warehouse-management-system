#include "warehouseanagement.h"

Warehouseanagement::Warehouseanagement(QWidget *parent) :
    QMainWindow(parent)
{
    setWindowIcon(QIcon(":/mainImag/nuoya.png"));

    this->setAttribute(Qt::WA_QuitOnClose,false);

    this->setFixedSize(1070,700);
    this->setWindowTitle(tr("出库单"));
    createIdList(NULL);

    createAction();
    createLabel_LineEdit();
    createButton();
    createTableView();
    connect(goodsidLineEdit,SIGNAL(textChanged(QString)),this,SLOT(setGoodsName(QString)));
    connect(outputcountLineEdit,SIGNAL(textChanged(QString)),this,SLOT(setoutputTotal(QString)));
    connect(outputpriceLineEdit,SIGNAL(textChanged(QString)),this,SLOT(setoutputTotal(QString)));
    connect(goodsidLineEdit,SIGNAL(textChanged(QString)),this,SLOT(createIdList(QString)));
    connect(goodsidLineEdit,SIGNAL(textChanged(QString)),this,SLOT(createIdList(QString)));

    selectShow();
}

void Warehouseanagement::setoutputTotal(const QString count)
{

    double total=(count.toDouble())*(outputpriceLineEdit->text().toDouble());
    outputtotalLineEdit->setText(QString::number(total,'f',2));

}

void Warehouseanagement::selectShow()
{
    QString select_sql = "select goodsid ,goodsname,outputcount,outputprice,outputtotal,outputtype,outputtime,customsid from goodsoutput";
    QSqlQuery query;
    int i=0;
    if(!query.exec(select_sql))
    {
        qDebug()<<query.lastError();
    }
    else
    {
        //goodsid ,goodsname,outputcount,outputprice,outputtotal,outputtype,outputtime,customsid

        while(query.next())
        {
            tableModel->setItem(i,0,new QStandardItem(query.value("goodsid").toString()));
            tableModel->setItem(i,1,new QStandardItem(query.value("goodsname").toString()));
            tableModel->setItem(i,2,new QStandardItem(query.value("outputcount").toString()));
            tableModel->setItem(i,3,new QStandardItem(query.value("outputprice").toString()));
            tableModel->setItem(i,4,new QStandardItem(query.value("outputtotal").toString()));
            tableModel->setItem(i,5,new QStandardItem(query.value("outputtype").toString()));
            tableModel->setItem(i,6,new QStandardItem(query.value("outputtime").toDate().toString("yyyy-MM-dd")));
            int index=query.value("customsid").toInt();
            if(index>=0&&index<customsIdList.length())
                tableModel->setItem(i,7,new QStandardItem(customsNameList.operator [](index)));
            else
                tableModel->setItem(i,7,new QStandardItem(query.value("customsid").toString()));
            i++;
        }
    }
}
void Warehouseanagement::setGoodsName(QString goodsid)
{
    int index=goodsIdList.indexOf(goodsid);

    if(index>=0&&index<goodsIdList.length())
    {
        goodsnameLineEdit->setText(goodsNameList.operator [](index));
        outputpriceLineEdit->setText(goodspriceList.operator [](index));
    }
    else
        goodsnameLineEdit->clear();

}
void Warehouseanagement::createIdList(QString temp)
{

    customsNameList.clear();
    customsIdList.clear();
    goodsIdList.clear();
    goodsNameList.clear();
    goodspriceList.clear();
    goodssaveList.clear();
    QString select_sql = "select name,id from customs";
    QSqlQuery query;
    query.prepare(select_sql);
    query.exec();
    while(query.next())
    {
        customsNameList.append(query.value("name").toString());
        customsIdList.append(query.value("id").toString());
    }

    select_sql = "select goodsid,goodsname,goodsprice,goodssave from goods";
    query.prepare(select_sql);
    query.exec();

    while(query.next())
    {

        goodsIdList.append(query.value("goodsid").toString());
        goodsNameList.append(query.value("goodsname").toString());
        goodspriceList.append(query.value("goodsprice").toString());
        goodssaveList.append(query.value("goodssave").toString());

    }
    //customsNamecompleter = new QCompleter(customsNameList);

    //goodscompleter = new QCompleter(goodsIdList);

}

void Warehouseanagement::createButton()
{
    enterButton=new QPushButton(tr("确定出库"),this);
    enterButton->setGeometry(800,100,110,50);
    connect(enterButton,SIGNAL(clicked()),this,SLOT(saveFun()));


}
void Warehouseanagement::createTableView()
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
    tableModel->setHorizontalHeaderItem(2, new QStandardItem(QObject::tr("出库数量 ")));
    tableModel->setHorizontalHeaderItem(3, new QStandardItem(QObject::tr("出库单价 ")));
    tableModel->setHorizontalHeaderItem(4, new QStandardItem(QObject::tr("出库总价 ")));

    tableModel->setHorizontalHeaderItem(5, new QStandardItem(QObject::tr("出库类型 ")));
    tableModel->setHorizontalHeaderItem(6, new QStandardItem(QObject::tr("出库时间 ")));
    tableModel->setHorizontalHeaderItem(7, new QStandardItem(QObject::tr("客户名 ")));
    mainTableView->setModel(tableModel);
}

void Warehouseanagement::paintEvent(QPaintEvent*)
{
    QPainter painter1(this);
    QPixmap pix1;
    pix1.load(":/mainImag/background.png");
    painter1.drawPixmap(0,0,this->width(),this->height(),pix1);
}

void Warehouseanagement::createAction()
{

    alterAct=new QAction(QIcon(":/image/alter.png"),tr("修改"),this);
    connect(alterAct,SIGNAL(triggered()),this,SLOT(alterRecord()));

    deleteAct=new QAction(QIcon(":/image/alter.png"),tr("删除"),this);
    connect(deleteAct,SIGNAL(triggered()),this,SLOT(deleteRecord()));
}

void Warehouseanagement::createLabel_LineEdit()
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



    outputcountLabel=new QLabel(tr("出库数量:"),this);
    outputcountLabel->setGeometry(100,90,80,40);
    outputcountLineEdit=new QLineEdit(this);
    outputcountLineEdit->setGeometry(180,95,200,30);
    QRegExp regExp("[1-9][0-9]+$");
    QValidator *validator = new QRegExpValidator(regExp, outputcountLineEdit );//正则表达式
    outputcountLineEdit->setValidator(validator);



    outputpriceLabel=new QLabel(tr("出库单价:"),this);
    outputpriceLabel->setGeometry(450,90,80,40);
    outputpriceLineEdit=new QLineEdit(this);
    outputpriceLineEdit->setGeometry(530,95,200,30);


    outputtimeLabel=new QLabel(tr("出库时间:"),this);
    outputtimeLabel->setGeometry(100,170,80,40);
    outputtimeLineEdit=new QLineEdit(this);
    outputtimeLineEdit->setGeometry(180,172,200,30);
    QDateTime time = QDateTime::currentDateTime();//获取系统现在的时间
    outputtimeLineEdit->setText(time.toString("yyyy-MM-dd"));///////////////////////////////////////////////////////
    outputtimeLineEdit->setEnabled(false);

    outputtotalLabel=new QLabel(tr("出库总价:"),this);
    outputtotalLabel->setGeometry(100,125,80,40);
    outputtotalLineEdit=new QLineEdit(this);
    outputtotalLineEdit->setGeometry(180,133,200,30);

    outputtypeLabel=new QLabel(tr("出库类型"),this);
    outputtypeLabel->setGeometry(450,125,80,40);
    outputtypeComboBox=new QComboBox(this);
    outputtypeComboBox->addItem(tr("其他出库"));
    outputtypeComboBox->addItem(tr("销售出库"));
    outputtypeComboBox->setGeometry(530,133,200,30);

    customsidLabel=new QLabel(tr("客户名称:"),this);
    customsidLabel->setGeometry(450,170,80,40);
    customsidLineEdit=new QLineEdit(this);
    customsNamecompleter = new QCompleter(customsNameList);
    customsNamecompleter->setCaseSensitivity(Qt::CaseInsensitive);//大小写匹配
    customsNamecompleter->setCompletionMode(QCompleter::PopupCompletion); //匹配以弹出式显示  （2）
    customsidLineEdit->setCompleter(customsNamecompleter);
    customsidLineEdit->setGeometry(530,172,200,30);

}
void Warehouseanagement::alterRecord()
{
    QMessageBox::information(this,"提示","修改");
}


void Warehouseanagement::deleteRecord()
{
    QMessageBox::information(this,"提示","删除");
}

/*void Warehouseanagement::showContextMenu(const QPoint& pos)//contextMenuEvent(QContextMenuEvent * event)
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

}*/
double Warehouseanagement::isExist(QString selectedId)
{
    QString select_sql = "select goodsid ,storagecount from goodsstorage where goodsid=:selectedId";
    QSqlQuery query;
    query.prepare(select_sql);
    query.bindValue(":selectedId",selectedId);

    if(!query.exec())
        qDebug() << query.lastError();
    int i=0;
    double count=-2;
    while(query.next())
    {
        count=query.value("storagecount").toDouble();
        i=i+1;
    }
    if(i>=1)
    {

        return count;
    }
    else
        return -1;
}
double Warehouseanagement::isExistGoods(QString selectedId)
{
    QString select_sql = "select goodsid ,storagecount from goodsstorage where goodsid=:selectedId";
    QSqlQuery query;
    query.prepare(select_sql);
    query.bindValue(":selectedId",selectedId);

    if(!query.exec())
        qDebug() << query.lastError();
    int i=0;
    double count=-2;
    while(query.next())
    {
        count=query.value("storagecount").toDouble();
        i=i+1;
    }
    if(i>=1)
    {

        return count;
    }
    else
        return -1;
}
void Warehouseanagement::saveFun()
{
    createIdList(NULL);
    if(outputcountLineEdit->text().isEmpty())
    {
        QMessageBox::warning(this,"警告","请填写出库的数量！");
        return ;
    }
    if(customsidLineEdit->text().isEmpty())
        customsidLineEdit->setText("未填写");
    QSqlQuery query;
    int indexId=goodsIdList.indexOf(goodsidLineEdit->text());
    //int indexName=goodsNameList.indexOf(goodsnameLineEdit->text());
    double strogecount;
    if(isExistGoods(goodsidLineEdit->text())!=-1)
    {

        msgLabel->setText("<h3><font color=red>当前操作：添加出库信息</font></h3>");

        strogecount=isExist(goodsidLineEdit->text());
        qDebug() << "outcout" << strogecount;
        QString savecountStr=goodssaveList.operator [](indexId);
        if(strogecount<=0)
        {
            QMessageBox::warning(this,"警告","仓库中无此产品存货,无法进行出库操作，操作无效");
            resetFun();
            return ;
        }
        else
            if(strogecount<savecountStr.toDouble())
            {
                QString message="当前库存:"+QString::number(strogecount)+"\n"+"安全库存："+savecountStr+"\n"\
                        +"当前库存已经低于安全库存,是否继续出库";

                QMessageBox msgBox(QMessageBox::Warning, tr("警告"),
                                   message, 0, this);
                msgBox.addButton(tr("取消"), QMessageBox::AcceptRole);
                msgBox.addButton(tr("继续"), QMessageBox::RejectRole);
                if (msgBox.exec() == QMessageBox::AcceptRole)
                {
                    resetFun();
                    return;
                }

            }
            if(strogecount>=outputcountLineEdit->text().toDouble())//已经存在要插入的信息
            {
                QString update_sql="update goodsstorage set storagecount=storagecount-:outcount,storagetotal=storagetotal-:outtotal\
                        where goodsid = :updatedId";
                query.prepare(update_sql);
                query.bindValue(":updatedId",goodsidLineEdit->text());
                query.bindValue(":outcount",outputcountLineEdit->text().toDouble());

                query.bindValue(":outtotal",outputtotalLineEdit->text().toDouble());

                if(!query.exec())
                {
                    qDebug() << query.lastError();
                }

            }
            else//库存表不存在信息
            {
                QMessageBox::warning(this,"警告","库存量小于出库量,无法进行正常出库,请修改出库量！");
                return ;
            }
            QString insert_sql = "insert into goodsoutput(goodsid ,goodsname,outputcount,outputprice,\
                    outputtotal,outputtype,outputtime,customsid)  values (?,?,?,?,?,?,?,?)";


            query.prepare(insert_sql);

            query.addBindValue(goodsidLineEdit->text());
            query.addBindValue(goodsnameLineEdit->text());
            query.addBindValue(outputcountLineEdit->text().toDouble());
            query.addBindValue(outputpriceLineEdit->text().toDouble());
            query.addBindValue(outputtotalLineEdit->text().toDouble());
            query.addBindValue(outputtypeComboBox->currentText());
            query.addBindValue(QDateTime::fromString(outputtimeLineEdit->text(), "yyyy-MM-dd"));
            query.addBindValue(goodsIdList.operator [](indexId));

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
                tableModel->setItem(rowCount,2,new QStandardItem(outputcountLineEdit->text()));
                tableModel->setItem(rowCount,3,new QStandardItem(outputpriceLineEdit->text()));
                tableModel->setItem(rowCount,4,new QStandardItem(outputtotalLineEdit->text()));
                tableModel->setItem(rowCount,5,new QStandardItem(outputtypeComboBox->currentText()));
                tableModel->setItem(rowCount,6,new QStandardItem(outputtimeLineEdit->text()));
                tableModel->setItem(rowCount,7,new QStandardItem(customsidLineEdit->text()));

                msgLabel->setText("<h3><font color=red>出库信息添加成功！</font></h3>");
                resetFun();
            }

    }
    else
    {
        QMessageBox::warning(this,"警告","商品管理中不存在该商品的信息,无法进行出库操作，此次操作无效！");
        resetFun();
        return ;
    }

}
void Warehouseanagement::resetFun()
{
    goodsidLineEdit->clear();
    goodsnameLineEdit->clear();
    outputcountLineEdit->clear();
    outputpriceLineEdit->clear();
    customsidLineEdit->clear();
    outputtotalLineEdit->clear();
}
