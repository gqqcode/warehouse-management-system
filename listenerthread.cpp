#include "listenerthread.h"

extern bool customsisChange;
extern bool goodsisChange;

ListenerThread::ListenerThread(QObject *parent) :
    QThread(parent)
{
}
void ListenerThread::run()
{
    while(1)
    {
        if(customsisChange)
        {
            emit sendcustomChanged();
            customsisChange=false;
        }
        if(goodsisChange)
        {
            emit sendgoodsChanged();
            goodsisChange=false;
        }
    }
}
