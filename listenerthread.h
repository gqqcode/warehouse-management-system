#ifndef LISTENERTHREAD_H
#define LISTENERTHREAD_H

#include <QThread>

class ListenerThread : public QThread
{
    Q_OBJECT
public:
    explicit ListenerThread(QObject *parent = 0);
    void run();
signals:
    void sendcustomChanged();
    void sendgoodsChanged();
public slots:


};

#endif // LISTENERTHREAD_H
