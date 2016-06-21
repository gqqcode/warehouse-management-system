#ifndef WAREHOUSEANAGEMENT_H
#define WAREHOUSEANAGEMENT_H

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
#include <qDebug>
#include "listenerthread.h"


class Warehouseanagement : public QMainWindow
{
    Q_OBJECT
public:
    explicit Warehouseanagement(QWidget *parent = 0);
    void paintEvent(QPaintEvent*);
    void createAction();
    void createLabel_LineEdit();
    void createButton();
    void createTableView();
    void resetFun();
    void selectShow();
    double isExist(QString selectedId);
    double isExistGoods(QString selectedId);

private:
    QLabel *goodsnameLabel;
    QLabel *goodsidLabel;
    QLabel *outputcountLabel;
    QLabel *outputtimeLabel;
    QLabel *outputpriceLabel;
    QLabel *outputtotalLabel;
    QLabel *outputtypeLabel;
    QLabel *customsidLabel;

    QLineEdit *goodsnameLineEdit;
    QLineEdit *goodsidLineEdit;
    QLineEdit *outputcountLineEdit;
    QLineEdit *outputtimeLineEdit;
    QLineEdit *outputpriceLineEdit;
    QLineEdit *outputtotalLineEdit;
    QComboBox *outputtypeComboBox;
    QLineEdit *customsidLineEdit;

    QTableView *mainTableView;
    QStandardItemModel *tableModel;

    QPushButton *addInfoButton;
    QPushButton *enterButton;
    QMenu *rightMenu=NULL;//右键菜单


    QAction *alterAct;//修改
    QAction *deleteAct;
    QLabel *msgLabel;
protected:
    QStringList goodsIdList;
    QStringList goodsNameList;
    QStringList customsNameList;
    QStringList customsIdList;
    QStringList goodspriceList;
    QStringList goodssaveList;
    QCompleter *goodscompleter;
    QCompleter *customsNamecompleter;

signals:

public slots:
    void alterRecord();
    void deleteRecord();
    //void showContextMenu(const QPoint& pos);
    void saveFun();
    void setGoodsName(QString goodsid);//设置产品名字的函数
    void setoutputTotal(const QString count);
    void createIdList(QString temp);

};

#endif // WAREHOUSEANAGEMENT_H
