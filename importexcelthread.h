#ifndef IMPORTEXCELTHREAD_H
#define IMPORTEXCELTHREAD_H

#include <QThread>
#include <QMainWindow>
#include <QtXlsx/xlsxdocument.h>
#include <QtXlsx/QtXlsx>
#include <QDebug>
#include <QSqlQuery>
#include <QSqlError>


class ImportExcelThread : public QThread
{
    Q_OBJECT
public:
    explicit ImportExcelThread(QObject *parent = 0, QString file=NULL);
    void importExcel();
protected:
    void run();
private:
    QString fileName;
signals:
    void sendBuf(const QString QBuf);
    void sendOk();
public slots:

};

#endif // IMPORTEXCELTHREAD_H
