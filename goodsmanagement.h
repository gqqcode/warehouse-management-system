#ifndef GOODSMANAGEMENT_H
#define GOODSMANAGEMENT_H

#include <QMainWindow>
#include <QLabel>
#include <QPushButton>
#include <QLineEdit>
#include <QComboBox>
#include <QTextEdit>
#include <QTableView>
#include <QStandardItemModel>
#include <QPainter>
#include <QAction>
#include <QStatusBar>
#include <QMessageBox>
#include <QMenu>
#include <QFileDialog>
#include <QSqlError>
#include <QCloseEvent>
#include "importexcelthread.h"

class GoodsManagement : public QMainWindow
{
    Q_OBJECT

public:
    GoodsManagement(QWidget *parent = 0);
    ~GoodsManagement();
    void paintEvent(QPaintEvent*);
    void createLabel_LineEdit();
    void createButton();
    void createTableView();
    void createAction();
    int getrowCount();
    void clearEdit();
    bool isExist(QString id);
private:
    QLabel *goodsIdLabel;
    QLabel *goodsNameLabel;
    QLabel *goodsFormatLabel;
    QLabel *goodsClassLabel;
    QLabel *goodsUnitLabel;
    QLabel *goodsStatusLabel;
    QLabel *goodsSaveLabel;
    QLabel *goodsPriceLabel;
    QLabel *goodsremarksLabel;

    QLineEdit *goodsIdLineEdit;
    QLineEdit *goodsNameLineEdit;
    QLineEdit *goodsFormatLineEdit;
    QLineEdit *goodsClassLineEdit;
    QLineEdit *goodsUnitLineEdit;
    QComboBox *goodsStatusComboBox;
    QLineEdit *goodsSaveLineEdit;
    QLineEdit *goodsPriceLineEdit;
    QTextEdit *goodsremarksTextEdit;
    QTableView *mainTableView;
    QStandardItemModel *tableModel;

    QPushButton *enterPushButton;
    QPushButton *importPushButton;

    QLabel *msgLabel;
    QMenu *rightMenu=NULL;//右键菜单


    QAction *alterAct;//修改
    QAction *deleteAct;
    QAction *pauseAct;//停用
    QAction *availableAct;//启用
    ImportExcelThread *import;

public slots:
    void alterRecord();
    void deleteRecord();
    void availableFun();
    void pauseFun();
    void showContextMenu(const QPoint& pos);
    void saveFun();
    void importFun();
    void selectShow();
    void updataTabeleView(const QString Qbuf);
    void recvOk();
protected:
    QString goodsid;
    QString goodsname;
    QString goodsformat;
    QString goodsclass;
    QString goodsunit;
    QString goodsstatus;
    int goodsstatusid;
    QString goodssave;
    QString goodsprice;
    QString goodsremarks;

    int oper;
    QString updatedId;//记录修改的产品id
    int rowNum;//记录修改的tableview的行号

};

#endif // GOODSMANAGEMENT_H
