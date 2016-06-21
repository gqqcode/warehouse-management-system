#include "alterpasswd.h"

AlterPasswd::AlterPasswd(QWidget *parent) :
    QWidget(parent)
{
    this->setWindowFlags(windowFlags()|Qt::FramelessWindowHint|Qt::WindowTitleHint);
    setWindowIcon(QIcon(":/mainImag/nuoya.png"));

    this->setFixedSize(550,380);
    accountLabel=new QLabel(this);
    accountLabel->setText(tr("<h2><b>账     号:</b></h2>"));
    accountLabel->setGeometry(50,110,190,30);


    oldPasswdLabel=new QLabel(this);
    oldPasswdLabel->setText("<h2><b>旧  密码:</b></h2>");
    oldPasswdLabel->setGeometry(50,150,190,30);


    newPasswdLabel=new QLabel(this);
    newPasswdLabel->setText("<h2><b>新  密码:</b></h2>");
    newPasswdLabel->setGeometry(50,190,190,30);


    renewPasswdLabel=new QLabel(this);
    renewPasswdLabel->setText("<h2><b>验证密码:</b></h2>");
    renewPasswdLabel->setGeometry(50,230,190,30);



    accountLineEdit=new QLineEdit(this);
    accountLineEdit->setGeometry(162,110,230,30);
    accountLineEdit->setPlaceholderText("请输入账号");

    oldPasswdLineEdit=new QLineEdit(this);
    oldPasswdLineEdit->setGeometry(162,150,230,30);
    oldPasswdLineEdit->setPlaceholderText("请输入旧密码");
    oldPasswdLineEdit->setEchoMode(QLineEdit::Password);

    newPasswdLineEdit=new QLineEdit(this);
    newPasswdLineEdit->setGeometry(162,190,230,30);
    newPasswdLineEdit->setPlaceholderText("请输入新的密码");
    newPasswdLineEdit->setEchoMode(QLineEdit::Password);


    renewPasswdLineEdit=new QLineEdit(this);
    renewPasswdLineEdit->setGeometry(162,230,230,30);
    renewPasswdLineEdit->setPlaceholderText("请再次输入新密码");
    renewPasswdLineEdit->setEchoMode(QLineEdit::Password);



    QPixmap minPix  = style()->standardPixmap(QStyle::SP_TitleBarMinButton);
    QPixmap closePix = style()->standardPixmap(QStyle::SP_TitleBarCloseButton);
    QToolButton *minButton = new QToolButton(this);
    QToolButton *closeButton= new QToolButton(this);
    minButton->setIcon(minPix);
    closeButton->setIcon(closePix);
    minButton->setGeometry( 495,3,25,25);
    closeButton->setGeometry( 525,5,25,25);
    minButton->setToolTip(tr("最小化"));
    closeButton->setToolTip(tr("关闭"));
    minButton->setStyleSheet("background-color:transparent;");
    closeButton->setStyleSheet("background-color:transparent;");
    connect(minButton,SIGNAL(clicked()),this,SLOT(showMinimized()));//,Qt::UniqueConnection);
    connect(closeButton,SIGNAL(clicked()),this,SLOT(close()));//,Qt::UniqueConnection);
    entryButton=new QPushButton(this);
    entryButton->setText("确认修改");
    entryButton->setGeometry(100,280,100,50);
    resetlButton=new QPushButton(this);
    resetlButton->setText("重置");
    resetlButton->setGeometry(340,280,100,50);

    QFont ft;
    ft.setPointSize(12);

    //设置颜色
    QPalette pa;
    pa.setColor(QPalette::WindowText,Qt::red);



    msgLabel=new QLabel();
    msgLabel->setMinimumSize(msgLabel->sizeHint());
    msgLabel->setAlignment(Qt::AlignLeft);
    statusBar=new QStatusBar(this);
    statusBar->setGeometry(0,350,550,30);
    statusBar->addWidget(msgLabel);
    statusBar->setFont(ft);
    statusBar->setPalette(pa);
    connect(resetlButton,SIGNAL(clicked()),this,SLOT(pressReset()));
    connect(entryButton,SIGNAL(clicked()),this,SLOT(pressEnter()));



}
void AlterPasswd::pressEnter()
{
    if(accountLineEdit->text().isEmpty())
    {
        msgLabel->setText("请输入账号");
        return ;
    }
    if(oldPasswdLineEdit->text().isEmpty())
    {
        msgLabel->setText("请输入旧密码！");
        return  ;
    }
    if(newPasswdLineEdit->text().isEmpty())
    {
        msgLabel->setText("请输入新密码！");
        return  ;
    }
    if(renewPasswdLineEdit->text().isEmpty())
    {
        msgLabel->setText("请输入验证密码！");
        return  ;
    }
    QString account=accountLineEdit->text();
    QString oldpasswd=oldPasswdLineEdit->text();
    QString newpasswd=newPasswdLineEdit->text();
    QString renewpass=renewPasswdLineEdit->text();
    QString dataaccount,datapasswd;
    QSqlQuery query;
    if(!query.exec("select  username,password from users "))
        query.lastError();
    else
        while(query.next())
        {
            dataaccount=query.value("username").toString();
            datapasswd=query.value("password").toString();
        }
    if(dataaccount==account&&datapasswd==oldpasswd)
    {
        if(newpasswd==renewpass)
        {
            QString update_sql="update users set password=:newpasswd where username=:account ";
            query.prepare(update_sql);
            query.bindValue(":account",account);
            query.bindValue(":newpasswd",newpasswd);

            if(!query.exec())
            {
                msgLabel->setText("密码修改失败！");
                pressReset();

             }
            else
            {
                msgLabel->setText("密码修改成功！");
                pressReset();

            }
        }
        else
        {
            msgLabel->setText("两次输入的新密码不一致！");
            pressReset();
        }

    }
    else
    {
        msgLabel->setText("输入的账户和密码错误！");
        pressReset();
    }

}
void AlterPasswd::pressReset()
{
    accountLineEdit->clear();
    oldPasswdLineEdit->clear();
    newPasswdLineEdit->clear();
    renewPasswdLineEdit->clear();
}
void AlterPasswd::paintEvent(QPaintEvent*)

{
    QPainter painter(this);
    QPixmap pix;
    pix.load(":/mainImag/background.png");
    painter.drawPixmap(0,0,this->width(),this->height(),pix);
}
void AlterPasswd::mousePressEvent(QMouseEvent *e)
{
    last = e->globalPos();
}
void AlterPasswd::mouseMoveEvent(QMouseEvent *e)
{
    int dx = e->globalX() - last.x();
    int dy = e->globalY() - last.y();

    last = e->globalPos();
    move(x()+dx, y()+dy);
}

void AlterPasswd::mouseReleaseEvent(QMouseEvent *e)
{
    int dx = e->globalX() - last.x();
    int dy = e->globalY() - last.y();

    move(x()+dx, y()+dy);
}

AlterPasswd::~AlterPasswd()
{

}
