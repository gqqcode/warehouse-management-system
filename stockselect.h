#ifndef STOCKSELECT_H
#define STOCKSELECT_H

#include <QMainWindow>

#include <QMainWindow>
#include <QLabel>
#include <QPushButton>
#include <QLineEdit>
#include <QTableView>
#include <QComboBox>
#include <QAction>
#include <QCalendarWidget>
#include <QFontComboBox>
#include <QStandardItemModel>
#include <QTableView>
#include <QPainter>
#include "mylineedit.h"
#include <QSqlQuery>
#include <QDebug>
#include <QMessageBox>
#include <QSqlError>
#include <QCompleter>
#include "exportexcelthread.h"

class StockSelect : public QMainWindow
{
    Q_OBJECT

public:
    StockSelect(QWidget *parent = 0);
    void paintEvent(QPaintEvent*);
    void createTableView();
    void createLabel_LineEdit();
    void createButton();
    void clearTableView();
    void createList();
private:
    QLabel *selectLabel;
    QComboBox *selectComboBox;
    QLineEdit *selectLineEdit;
    QPushButton *selectButton;
    QCalendarWidget *fromCaledar;
    QCalendarWidget *toCaledar;

    MyLineEdit *fromlineedit;
    MyLineEdit *tolineedit;

    QFontComboBox *hms;
    QString str;
    QLabel *setLabel;
    QLabel *fromLabel;
    QLabel *toLabel;

    QTableView *mainTableView;
    QStandardItemModel *tableModel;

    QPushButton *exportButton;
    QPushButton *printButton;
    QStringList selectList;
    QCompleter *selectCompleter;
    QStringList stockList;
    ExportExcelThread *exportthread;




public slots:
    void fromOk();
    void toOk();
    void printFun();
    void exportFun();
    void selectFun();
    void showStatus();
};

#endif // STOCKSELECT_H
