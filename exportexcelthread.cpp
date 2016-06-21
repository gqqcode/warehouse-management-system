#include "exportexcelthread.h"

ExportExcelThread::ExportExcelThread(QObject *parent, QString file,QStringList dataList,int r,int c) :
    QThread(parent)
{
    fileName=file;
    allList=dataList;
    row=r;
    cloumn=c;
}
void ExportExcelThread::run()
{

    int i,j,num=0;
    QStringList wordList;
    wordList<< "A" << "B" << "C" << "D" << "E" << "F" << "G" << \
               "H" << "I" << "J" << "K" << "L" << "M" << "N" << "O" << "P" << "Q" <<"R"\
               << "S" << "T" <<"U" <<"V" <<"W" << "X" << "Z";
    QXlsx::Document xlsx(fileName);
    for(i=0;i<=row;i++)
    {
        for(j=0;j<cloumn;j++)
        {

            wordList[j].insert(1,QString::number(i+1));
            xlsx.write(wordList[j],allList[num]);
            num++;

        }
        wordList.clear();
        wordList<< "A" << "B" << "C" << "D" << "E" << "F" << "G" << \
                   "H" << "I" << "J" << "K" << "L" << "M" << "N" << "O" << "P" << "Q" <<"R"\
                   << "S" << "T" <<"U" <<"V" <<"W" << "X" << "Z";
    }
    xlsx.saveAs(fileName);
    emit sendStatus();
    //this->exit();
}
