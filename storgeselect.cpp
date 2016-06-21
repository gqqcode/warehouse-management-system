#include "storgeselect.h"
#include <QFileDialog>
StorgeSelect::StorgeSelect(QWidget *parent)
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
void StorgeSelect::createButton()
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
void StorgeSelect::createList()
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

/*"select   goodsstorage.goodsid,goodsstorage.goodsname,goodsstorage.storagecount,
goodsstorage.storagprice,goodsstorage.storagetotal,
goods.goodssave,goods.goodsstatus where goods.goodsname in(select goodsname from goodsstorage
 where goodsname=:conditionStr1 ) and goods.goodsname=goodsstorage.goodsname";*/

void StorgeSelect::createTableView()
{
    mainTableView=new QTableView(this);
    mainTableView->setGeometry(30,150,950,500);
    tableModel = new QStandardItemModel();
    mainTableView->setEditTriggers(QTableView::NoEditTriggers);

    tableModel->setHorizontalHeaderItem(0, new QStandardItem(QObject::tr("产品编号 ")));
    tableModel->setHorizontalHeaderItem(1, new QStandardItem(QObject::tr("产品名称 ")));

    tableModel->setHorizontalHeaderItem(2, new QStandardItem(QObject::tr("库存量 ")));
    tableModel->setHorizontalHeaderItem(3, new QStandardItem(QObject::tr("产品单价 ")));
    tableModel->setHorizontalHeaderItem(4, new QStandardItem(QObject::tr("产品总价 ")));

    tableModel->setHorizontalHeaderItem(5, new QStandardItem(QObject::tr("安全库存 ")));
    tableModel->setHorizontalHeaderItem(6, new QStandardItem(QObject::tr("产品状态 ")));


    mainTableView->setModel(tableModel);

}
void StorgeSelect::createLabel_LineEdit()
{
    selectLabel=new QLabel(tr("请选择查询条件:"),this);
    selectLabel->setGeometry(50,20,190,30);
    selectComboBox=new QComboBox(this);
    selectComboBox->addItem(tr("名称"));
    selectComboBox->addItem(tr("编码"));

    selectComboBox->setGeometry(170,20,80,30);
    selectLineEdit=new QLineEdit(this);
    selectLineEdit->setGeometry(310,20,230,30);
    selectCompleter = new QCompleter(selectList);
    selectCompleter->setCaseSensitivity(Qt::CaseInsensitive);//大小写匹配
    selectCompleter->setCompletionMode(QCompleter::PopupCompletion); //匹配以弹出式显示  （2）
    selectLineEdit->setCompleter(selectCompleter);

}

void StorgeSelect::paintEvent(QPaintEvent*)

{
    QPainter painter(this);
    QPixmap pix;
    pix.load(":/mainImag/background.png");
    painter.drawPixmap(0,0,this->width(),this->height(),pix);
}
void StorgeSelect::showStatus()
{
    exportthread->quit();
    delete exportthread;
    exportthread=NULL;
    QMessageBox::information(this,"提示","数据导出成功！");
}
void StorgeSelect::exportFun()
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
        exportthread=new ExportExcelThread(this,fileName,storgeList,row,cloumn);
        exportthread->start();
        connect(exportthread,SIGNAL(sendStatus()),this,SLOT(showStatus()));
    }
}
void StorgeSelect::printFun()
{

}


void StorgeSelect::clearTableView()
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
void StorgeSelect::selectFun()
{
    createList();
    clearTableView();
    QSqlQuery query;
    QString select_sql;
    int i=0;

    int  condition=selectComboBox->currentIndex();
    QString conditionStr1;

    switch(condition)
    {
    case 0:
    {
        //goodsstorage  storagecount storagprice  storagetotal  goodsid goodsname
        //goodsid goodsname  goodsformat  goodsclass  goodsunit   goodssave  goodsprice   goodsremarks   goodsstatus   goodsstatusid
        conditionStr1=selectLineEdit->text();
        select_sql = "select   goodsstorage.goodsid,goodsstorage.goodsname,goodsstorage.storagecount,\
                goodsstorage.storagprice,goodsstorage.storagetotal,\
                goods.goodssave,goods.goodsstatus from goodsstorage,goods  where goods.goodsname in(select goodsname from goodsstorage \
                 where goodsname=:conditionStr1 ) and goods.goodsname=goodsstorage.goodsname";
        if(conditionStr1.isEmpty())
        {
            QMessageBox::warning(this,"警告","请输入查询的商品名字！");
            return ;
        }
        query.prepare(select_sql);
        query.bindValue(":conditionStr1",conditionStr1);
        break;
    }

    case 1:
    {
        conditionStr1=selectLineEdit->text();

        select_sql = "select   goodsstorage.goodsid,goodsstorage.goodsname,goodsstorage.storagecount,\
                goodsstorage.storagprice,goodsstorage.storagetotal,\
                goods.goodssave,goods.goodsstatus from goodsstorage,goods  where goods.goodsid in(select goodsid from goodsstorage \
                 where goodsname=:conditionStr1 ) and goods.goodsid=goodsstorage.goodsid";

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
        storgeList.clear();
        storgeList.append("产品编号");
        storgeList.append("产品名称");
        storgeList.append("库存量");
        storgeList.append("产品单价");
        storgeList.append("产品总价");
        storgeList.append("安全库存");
        storgeList.append("产品状态");
        while(query.next())
        {

            tableModel->setItem(i,0,new QStandardItem(query.value("goodsid").toString()));
            storgeList.append(query.value("goodsid").toString());

            tableModel->setItem(i,1,new QStandardItem(query.value("goodsname").toString()));
            storgeList.append(query.value("goodsname").toString());

            tableModel->setItem(i,2,new QStandardItem(query.value("storagecount").toString()));
            storgeList.append(query.value("storagecount").toString());


            tableModel->setItem(i,3,new QStandardItem(query.value("storagprice").toString()));
            storgeList.append(query.value("storagprice").toString());

            tableModel->setItem(i,4,new QStandardItem(query.value("storagetotal").toString()));
            storgeList.append(query.value("storagetotal").toString());

            tableModel->setItem(i,5,new QStandardItem(query.value("goodssave").toString()));
            storgeList.append(query.value("goodssave").toString());

            tableModel->setItem(i,6,new QStandardItem(query.value("goodsstatus").toString()));
            storgeList.append(query.value("goodsstatus").toString());

            if(query.value("goodsstatus").toString()=="停用")
            {
                tableModel->item(i,6)->setBackground(QBrush(QColor(255,0, 0)));
            }
            else
            {
                tableModel->item(i,6)->setBackground(QBrush(QColor(255, 255, 255)));

            }

            i++;
        }
    }
}
