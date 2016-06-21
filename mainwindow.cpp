
/********   入库查询1   出库查询2     库存3 其他入库4  其他出库5      *********/

#include "mainwindow.h"
#include <QPainter>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    setWindowIcon(QIcon(":/mainImag/nuoya.png"));

    setWindowTitle(tr("仓库管理系统"));
    this->resize(QSize(1500,900));//界面初始大小
    this->setAutoFillBackground(false);
    this->setAttribute(Qt::WA_QuitOnClose,true);

    msgLabel=new QLabel();


    msgLabel->setMinimumSize(msgLabel->sizeHint());
    msgLabel->setAlignment(Qt::AlignHCenter);
    QFont ft;
    ft.setPointSize(12);

    //设置颜色
    QPalette pa;
    pa.setColor(QPalette::WindowText,Qt::red);
    this->statusBar()->addWidget(msgLabel);
    this->statusBar()->setFixedHeight(40);
    this->statusBar()->setFont(ft);
    this->statusBar()->setPalette(pa);
    createActions();
    createMenus();
    createToolBars();

}
void MainWindow::createActions()
{
    customerAct=new QAction(QIcon(":/mainImag/KeHuGuanLi.png"), tr("客户管理"), this);
    customerAct->setStatusTip(tr("管理客户信息"));
    connect(customerAct,SIGNAL(triggered()),this,SLOT(customerManageFun()));


    goodsAct=new QAction(QIcon(":/mainImag/ShangPinGuanLi.png"), tr("商品管理"), this);
    goodsAct->setStatusTip(tr("管理商品信息"));
    connect(goodsAct,SIGNAL(triggered()),this,SLOT(goodsmanagementFun()));


    purchasestableAct=new QAction(QIcon(":/mainImag/JinHuoDan.png"), tr("入库单"), this);
    purchasestableAct->setStatusTip(tr("添加进货信息"));
    connect(purchasestableAct,SIGNAL(triggered()),this,SLOT(stockmanagementFun()));


    salestableAct=new QAction(QIcon(":/mainImag/XiaoShouDan.png"), tr("出库单"), this);
    salestableAct->setStatusTip(tr("销售信息"));
    connect(salestableAct,SIGNAL(triggered()),this,SLOT(warehouseanagementFun()));


    enterWarehouseAct=new QAction(QIcon(":/mainImag/ChaXun.png"), tr("入库查询"), this);
    enterWarehouseAct->setStatusTip(tr("入库查询"));
    connect(enterWarehouseAct,SIGNAL(triggered()),this,SLOT(enterwarehouseFun()));


    outWarehouseAct=new QAction(QIcon(":/mainImag/ChaXun.png"), tr("出库查询"), this);
    outWarehouseAct->setStatusTip(tr("出库查询"));
    connect(outWarehouseAct,SIGNAL(triggered()),this,SLOT(outwarehouseFun()));


    stockAct=new QAction(QIcon(":/mainImag/ChaXun1.png"), tr("库存查询"), this);
    stockAct->setStatusTip(tr("库存查询"));
    connect(stockAct,SIGNAL(triggered()),this,SLOT(stockFun()));


    otherEnterWarehouseAct=new QAction(QIcon(":/mainImag/ChaXun.png"), tr("其他入库查询"), this);
    otherEnterWarehouseAct->setStatusTip(tr("其他入库查询"));
    connect(otherEnterWarehouseAct,SIGNAL(triggered()),this,SLOT(otherenterwarehouseFun()));


    otherOutWarehouseAct=new QAction(QIcon(":/mainImag/ChaXun.png"), tr("其他出库查询"), this);
    otherOutWarehouseAct->setStatusTip(tr("其他出库查询"));
    connect(otherOutWarehouseAct,SIGNAL(triggered()),this,SLOT(otheroutwarehouseFun()));

    aboutAct=new QAction(QIcon(":/mainImag/help.png"), tr("帮助"), this);
    aboutAct->setStatusTip(tr("帮助"));
    connect(aboutAct,SIGNAL(triggered()),this,SLOT(aboutFun()));

    systemAct=new QAction(QIcon(":/mainImag/set.png"), tr("初始化系统"), this);
    systemAct->setStatusTip(tr("初始化系统"));
    connect(systemAct,SIGNAL(triggered()),this,SLOT(systemFun()));


}

void MainWindow::createMenus()
{

    basicManagementMenu=menuBar()->addMenu(tr("基础管理"));
    basicManagementMenu->addAction(customerAct);
    basicManagementMenu->addAction(goodsAct);

    menuBar()->addSeparator();

    enteringManagementMenu=menuBar()->addMenu(tr("入库管理"));
    enteringManagementMenu->addAction(purchasestableAct);
    menuBar()->addSeparator();
    salesManagementMenu=menuBar()->addMenu(tr("出库管理"));
    salesManagementMenu->addAction(salestableAct);

    menuBar()->addSeparator();

    selectMenu=menuBar()->addMenu(tr("报表"));
    selectMenu->addAction(enterWarehouseAct);
    selectMenu->addAction(outWarehouseAct);
    selectMenu->addAction(stockAct);
    selectMenu->addAction(otherOutWarehouseAct);
    selectMenu->addAction(otherEnterWarehouseAct);
    aboutMenu=menuBar()->addMenu(tr("关于"));
    aboutMenu->addAction(aboutAct);
    aboutMenu->addAction(systemAct);

}

void MainWindow::createToolBars()
{
    manageToolBar=addToolBar(tr("管理"));
    manageToolBar->addAction(customerAct);
    manageToolBar->addAction(goodsAct);
    manageToolBar->addAction(purchasestableAct);
    manageToolBar->addAction(salestableAct);


    otherToolBar=addToolBar(tr("其他"));
    otherToolBar->addAction(enterWarehouseAct);
    otherToolBar->addAction(outWarehouseAct);
    otherToolBar->addAction(stockAct);
    otherToolBar->addAction(otherOutWarehouseAct);
    otherToolBar->addAction(otherEnterWarehouseAct);
}
void MainWindow::paintEvent(QPaintEvent*)

{
    QPainter painter(this);
    QPixmap pix;
    pix.load(":/mainImag/mainbackground.png");
    painter.drawPixmap(0,selectMenu->height()+manageToolBar->height(),this->width(),this->height(),pix);
    //painter.drawPixmap(0,selectMenu->height(),this->width(),this->height(),pix);

}
void MainWindow::aboutFun()
{

}
void MainWindow::createTable()
{
    QSqlQuery query;
    query.exec("CREATE TABLE if not exists goods (goodsid VARCHAR (50) PRIMARY KEY NOT NULL,\
               goodsname VARCHAR (100) NOT NULL, goodsformat VARCHAR (100), goodsclass VARCHAR (100),\
               goodsunit VARCHAR (100),goodssave DOUBLE, goodsprice DOUBLE, \
               goodsremarks VARCHAR (100),goodsstatus VARCHAR (50),goodsstatusid INTEGER)");
    if(!query.isActive())
    {
        qDebug("goods");
    }
    query.exec("CREATE TABLE  if not exists users (id INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL,\
               username VARCHAR (30) NOT NULL, password VARCHAR (30) NOT NULL)");
    if(!query.isActive())
    {
        qDebug("user");
    }

//goods  goodsstorage customs  goodsoutput  goodsinput


    query.exec("CREATE TABLE if not exists goodsstorage (id INTEGER PRIMARY KEY AUTOINCREMENT, storagecount DOUBLE NOT NULL,\
               storagprice DOUBLE NOT NULL, storagetotal DOUBLE NOT NULL, goodsid VARCHAR (50)\
               CONSTRAINT goods_id_goodsstorage REFERENCES goods (goodsid), goodsname VARCHAR (100) NOT NULL)");

    if(!query.isActive())
    {
        qDebug()<< "goodsstorage";
    }

    query.exec("CREATE TABLE if not exists customs (id integer primary key autoincrement, \
               name VARCHAR (50) NOT NULL, company VARCHAR (100) NOT NULL, address VARCHAR (100) NOT NULL, \
               phonenumber VARCHAR (100) NOT NULL, customstype VARCHAR (50) NOT NULL)");
    if(!query.isActive())
    {
        qDebug()<< "customs";

    }
    query.exec("CREATE TABLE if not exists goodsoutput (id INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL,\
               goodsid VARCHAR (50) CONSTRAINT goods_id_goodsout REFERENCES goods (goodsid), \
               goodsname VARCHAR (100) NOT NULL, outputcount DOUBLE NOT NULL, outputprice DOUBLE NOT NULL, \
               outputtotal DOUBLE NOT NULL, outputtime DATE NOT NULL, outputtype VARCHAR (100) NOT NULL,\
               customsid INTEGER CONSTRAINT customs_id_goodsoutput REFERENCES customs (id))");
    if(!query.isActive())
    {
        qDebug()<< "goodsoutput";

    }
    query.exec("CREATE TABLE if not exists  goodsinput (id INTEGER PRIMARY KEY \
               AUTOINCREMENT , inputcount DOUBLE NOT NULL, inputtime DATE NOT NULL,\
               inputprice DOUBLE NOT NULL, inputtotal DOUBLE NOT NULL, goodsid VARCHAR (50) CONSTRAINT goodsinput_id_goods \
               REFERENCES goods (goodsid), goodsname VARCHAR (100) NOT NULL, inputtype VARCHAR (100) NOT NULL, \
               customsid INTEGER CONSTRAINT customs_id_goodsinput REFERENCES customs (id))");
    if(!query.isActive())
    {
        qDebug() << "goodsinput";
    }

}
void MainWindow::systemFun()
{

    QMessageBox msgBox(QMessageBox::Warning, tr("警告"),"初始化系统将会删除你以前的所有信息,是否继续进行？", 0, this);
    msgBox.addButton(tr("取消"), QMessageBox::AcceptRole);
    msgBox.addButton(tr("继续"), QMessageBox::RejectRole);
    if (msgBox.exec() == QMessageBox::AcceptRole)
    {

        return;
    }
    else
    {
        QSqlQuery query;
        query.exec("drop table goods");
        query.exec("drop table goodsstorage");
        query.exec("drop table customs");

        query.exec("drop table goodsoutput");

        query.exec("drop table goodsinput");

        createTable();

    }




}
void MainWindow::customerManageFun()//客户管理
{


    customer=new CustomsManage();
    customer->show();

}

void MainWindow::stockmanagementFun()
{
    stockmanagement=new StockManagement();
    stockmanagement->show();
}

void MainWindow::goodsmanagementFun()
{
    goodsmanagement=new GoodsManagement();
    goodsmanagement->show();
}

void MainWindow::warehouseanagementFun()
{
    warehouseanagement=new Warehouseanagement();
    warehouseanagement->show();
}

void MainWindow::enterwarehouseFun()//入库
{
    enterwarehouse=new StockSelect();
    enterwarehouse->setWindowTitle("入库查询");
    enterwarehouse->show();
}
void MainWindow::outwarehouseFun()//出库
{
    outwarehouse=new WareHouseSelect();
    outwarehouse->setWindowTitle("出库查询");
    outwarehouse->show();
}
void MainWindow::stockFun()//库存
{
    stock=new StorgeSelect();
    stock->setWindowTitle("库存查询");
    stock->show();
}
void MainWindow::otherenterwarehouseFun()//其他入
{
    otherenterwarehouse=new OtherStockSelect();
    otherenterwarehouse->setWindowTitle("其他入库查询");
    otherenterwarehouse->show();
}
void MainWindow::otheroutwarehouseFun()//其他出
{
    otheroutwarehouse=new OtherWarehouseSelect();
    otheroutwarehouse->setWindowTitle("其他出库查询");
    otheroutwarehouse->show();
}
MainWindow::~MainWindow()
{
}
