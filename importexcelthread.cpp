#include "importexcelthread.h"

//extern bool flag;//为数据写入时间进行标记，处理超时
extern bool isOK;
extern QString isError;//存储已经存在的货物的信息

ImportExcelThread::ImportExcelThread(QObject *parent,QString file) :
    QThread(parent)
{
    fileName=file;

}
void ImportExcelThread::importExcel()
{
    QXlsx::Document xlsx(fileName);//打开Test.xlsx表格


    int row=1;
    //char pos[2];// A1   .......
    int count=0;//记录是个空行为表结束
    QString A,B,C,D,E,F,G,H,I;
    QString insert_sql = "insert into goods values (?,?,?,?,?,?,?,?,?,?)";
    QSqlQuery query;
    QString status;
    QString MyA="";
    for(row=2;count<10;row++)
    {

        //sprintf(pos,"A%d",row);
        MyA=MyA+'A'+QString::number(row);
        if(xlsx.read(MyA).isNull())
        {
            count++;
        }
        else
        {


            QString Qbuf="";
            A=A+'A'+QString::number(row);
            B=B+'B'+QString::number(row);
            C=C+'C'+QString::number(row);
            D=D+'D'+QString::number(row);
            E=E+'E'+QString::number(row);
            F=F+'F'+QString::number(row);
            G=G+'G'+QString::number(row);
            H=H+'H'+QString::number(row);
            I=I+'I'+QString::number(row);

            query.prepare(insert_sql);

            query.addBindValue(xlsx.read(A).toString());
            query.addBindValue(xlsx.read(B).toString());
            query.addBindValue(xlsx.read(C).toString());
            query.addBindValue(xlsx.read(D).toString());
            query.addBindValue(xlsx.read(E).toString());
            query.addBindValue(xlsx.read(F).toDouble());
            query.addBindValue(xlsx.read(G).toDouble());
            query.addBindValue(xlsx.read(H).toString());
            query.addBindValue(xlsx.read(I).toString());
            status=xlsx.read(I).toString();
            status=status.simplified();
            if(status=="在售")
            {
                query.addBindValue(1);
            }
            else
            {
                query.addBindValue(0);
            }
            if(!query.exec())
            {

                //flag=true;
                //qDebug()  << query.lastError();


            }
            else
            {
                Qbuf=Qbuf+xlsx.read(A).toString()+'#'+xlsx.read(B).toString()+'#'+xlsx.read(C).toString()+'#'+xlsx.read(D).toString()+'#'+xlsx.read(E).toString()+'#'+xlsx.read(F).toString()+'#'+xlsx.read(G).toString()+'#'+xlsx.read(H).toString()+'#'+xlsx.read(I).toString();

                emit sendBuf(Qbuf);


            }
            A="";
            B="";
            C="";
            D="";
            E="";
            F="";
            G="";
            H="";
            I="";


        }
        this->sleep(0.5);
        //while(flag);//判断是否写入表格数据

        MyA="";
        //memset(pos,0,sizeof(pos));


    }
    emit sendOk();
    //isOK=true;

}
void ImportExcelThread::run()
{
    importExcel();
}
