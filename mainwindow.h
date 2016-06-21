#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSqlQuery>
#include <QtSql>
#include <QStandardItemModel>
#include <QSqlDatabase>
#include <QDebug>
#include <QMenu>
#include <QMenuBar>
#include <QToolBar>
#include <QLabel>
#include <QStatusBar>
#include <QTableView>
#include <QLabel>
#include "customsmanage.h"
#include "stockmanagement.h"
#include "goodsmanagement.h"
#include "warehouseanagement.h"
#include "otherstockselect.h"
#include "otherwarehouseselect.h"
#include "stockselect.h"
#include "warehouseselect.h"
#include "storgeselect.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void createMenus();
    void createActions();
    void createToolBars();
    void paintEvent(QPaintEvent*);
    void createTable();
private:
    QLabel *msgLabel;
    QMenu *basicManagementMenu;//基础管理
    QMenu *enteringManagementMenu;//进货管理
    QMenu *salesManagementMenu;//销售管理
    QMenu *selectMenu;//报表
    QMenu *aboutMenu;

    QAction *customerAct;
    QAction *goodsAct;


    QAction *purchasestableAct;

    QAction *salestableAct;


    QAction *enterWarehouseAct;//入库
    QAction *outWarehouseAct;
    QAction *otherEnterWarehouseAct;//其他入库
    QAction *otherOutWarehouseAct;
    QAction *stockAct;
    QAction *aboutAct;
    QAction *systemAct;

    QToolBar *manageToolBar;
    QToolBar *otherToolBar;


    CustomsManage * customer=NULL;
    StockManagement *stockmanagement=NULL;
    GoodsManagement *goodsmanagement=NULL;
    Warehouseanagement *warehouseanagement=NULL;
    StockSelect *enterwarehouse=NULL;//进
    WareHouseSelect *outwarehouse=NULL;// 出
    StorgeSelect *stock=NULL;//库存
    OtherStockSelect *otherenterwarehouse=NULL;//其他进
    OtherWarehouseSelect *otheroutwarehouse=NULL;//其他出


private slots:
    void customerManageFun();
    void stockmanagementFun();
    void goodsmanagementFun();
    void warehouseanagementFun();
    void enterwarehouseFun();
    void outwarehouseFun();
    void stockFun();
    void otherenterwarehouseFun();
    void otheroutwarehouseFun();
    void aboutFun();
    void systemFun();


};

#endif // MAINWINDOW_H
