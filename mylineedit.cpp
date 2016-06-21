#include "mylineedit.h"

MyLineEdit::MyLineEdit(QWidget *parent):
    QLineEdit(parent)
{
    setFixedSize(100,30);
}
void MyLineEdit::mousePressEvent(QMouseEvent *event)
{
    //如果单击了就触发clicked信号
    if (event->button() == Qt::LeftButton)
    {
        //触发clicked信号
       emit clicked();
    }
    //将该事件传给父类处理
    QLineEdit::mousePressEvent(event);
}
