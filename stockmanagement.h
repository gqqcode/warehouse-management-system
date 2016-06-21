#ifndef STOCKMANAGEMENT_H
#define STOCKMANAGEMENT_H

#include <QMainWindow>
#include <QLineEdit>
#include <QLabel>
#include <QTableView>
#include <QPushButton>
#include <QStandardItemModel>
#include <QPainter>
#include <QComboBox>
#include <QStatusBar>
#include <QMessageBox>
#include <QMenu>
#include <QStringList>
#include<QCompleter>
#include <QSqlQuery>
#include <QKeyEvent>
#include <QDateTime>
#include <QSqlError>
#include "listenerthread.h"

class StockManagement : public QMainWindow
{
    Q_OBJECT

public:
    StockManagement(QWidget *parent = 0);
    ~StockManagement();
    void paintEvent(QPaintEvent*);
    void createAction();
    void createLabel_LineEdit();
    void createButton();
    void createTableView();
    void resetFun();
    void selectShow();
    bool isExist(QString selectedId);
    bool isExistGoods(QString selectedId);

private:
    QLabel *goodsnameLabel;
    QLabel *goodsidLabel;
    QLabel *inputcountLabel;
    QLabel *inputtimeLabel;
    QLabel *inputpriceLabel;
    QLabel *inputtotalLabel;
    QLabel *inputtypeLabel;
    QLabel *customsnameLabel;

    QLineEdit *goodsnameLineEdit;
    QLineEdit *goodsidLineEdit;
    QLineEdit *inputcountLineEdit;
    QLineEdit *inputtimeLineEdit;
    QLineEdit *inputpriceLineEdit;
    QLineEdit *inputtotalLineEdit;
    QComboBox *inputtypeComboBox;
    QLineEdit *customsnameLineEdit;

    QTableView *mainTableView;
    QStandardItemModel *tableModel;

    QPushButton *enterButton;
    QLabel *msgLabel;


    QMenu *rightMenu=NULL;//右键菜单


    QAction *alterAct;//修改
    QAction *deleteAct;
protected:
    QStringList goodsIdList;
    QStringList goodsNameList;
    QStringList customsNameList;
    QStringList customsIdList;
    QStringList goodspriceList;
    QCompleter *goodscompleter;
    QCompleter *customsNamecompleter;


public slots:
    void alterRecord();
    void deleteRecord();
    void showContextMenu(const QPoint& pos);
    void saveFun();
    void setGoodsName(QString goodsid);//设置产品名字的函数
    void setinputTotal(const QString count);
    void createIdList(QString temp);




};

#endif // STOCKMANAGEMENT_H
