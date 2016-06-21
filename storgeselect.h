#ifndef STORGESELECT_H
#define STORGESELECT_H

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
#include "exportexcelthread.h"
#include <QSqlQuery>
#include <QDebug>
#include <QMessageBox>
#include <QSqlError>
#include <QCompleter>

class StorgeSelect : public QMainWindow
{
    Q_OBJECT

public:
    StorgeSelect(QWidget *parent = 0);
    void paintEvent(QPaintEvent*);
    void createTableView();
    void createLabel_LineEdit();
    void createButton();

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
    QStringList storgeList;
    ExportExcelThread *exportthread;

public slots:

    void printFun();
    void exportFun();
    void selectFun();
    void createList();
    void clearTableView();
    void showStatus();
signals:

};

#endif // STORGESELECT_H
