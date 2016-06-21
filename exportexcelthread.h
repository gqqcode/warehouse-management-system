#ifndef EXPORTEXCELTHREAD_H
#define EXPORTEXCELTHREAD_H

#include <QThread>
#include <QString>
#include <QtXlsx/xlsxdocument.h>
#include <QtXlsx/QtXlsx>
#include <QDebug>


class ExportExcelThread : public QThread
{
    Q_OBJECT
public:
    explicit ExportExcelThread(QObject *parent , QString file, QStringList dataList, int r, int c);

protected:
    void run();
private:
    QString fileName;
    QStringList allList;
    int row;
    int cloumn;
signals:
    void sendStatus();
public slots:

};

#endif // EXPORTEXCELTHREAD_H
