#include "login.h"

LoginWidget::LoginWidget(QWidget *parent)
    : QWidget(parent)
{
    setWindowIcon(QIcon(":/mainImag/nuoya.png"));

    this->setFixedSize(613,346);


    if(!createDatabase())
    {
        QMessageBox::warning(this,"警告","系统已经故障！");
        exit(-1);
    }
    createTable();

    this->setWindowFlags(windowFlags()|Qt::FramelessWindowHint|Qt::WindowTitleHint);

    QToolButton *minButton = new QToolButton(this);
    QToolButton *closeButton= new QToolButton(this);

    minButton->setGeometry( 540,3,25,25);
    closeButton->setGeometry( 580,5,40,25);
    minButton->setToolTip(tr("最小化"));
    closeButton->setToolTip(tr("关闭"));
    minButton->setStyleSheet("background-color:transparent;");
    closeButton->setStyleSheet("background-color:transparent;");
    setWidget();

    QFont ft;
    ft.setPointSize(12);

    QPalette pa;
    pa.setColor(QPalette::WindowText,Qt::red);
    msgLabel=new QLabel();
    msgLabel->setMinimumSize(msgLabel->sizeHint());
    msgLabel->setAlignment(Qt::AlignLeft);
    statusBar=new QStatusBar(this);
    statusBar->setGeometry(0,310,613,30);
    statusBar->addWidget(msgLabel);
    statusBar->setFont(ft);
    statusBar->setPalette(pa);






    connect(minButton,SIGNAL(clicked()),this,SLOT(showMinimized()));//,Qt::UniqueConnection);
    connect(closeButton,SIGNAL(clicked()),this,SLOT(close()));//,Qt::UniqueConnection);
    connect(chgpasswdButton,SIGNAL(clicked()),this,SLOT(alterPasswd()));
}
bool LoginWidget::createDatabase()
{
    dba=QSqlDatabase::addDatabase("QSQLITE");
    dba.setDatabaseName("./WMS.db");
    if(!dba.open())
        return false;
    return true;
}
void LoginWidget::createTable()
{
    QSqlQuery query;
    query.exec("CREATE TABLE if not exists goods (goodsid VARCHAR (50) PRIMARY KEY NOT NULL,\
               goodsname VARCHAR (100) NOT NULL, goodsformat VARCHAR (100), goodsclass VARCHAR (100),\
               goodsunit VARCHAR (100),goodssave DOUBLE, goodsprice DOUBLE, \
               goodsremarks VARCHAR (100),goodsstatus VARCHAR (50),goodsstatusid INTEGER)");
    if(!query.isActive())
    {
        qDebug("goods");
    }
    query.exec("CREATE TABLE  if not exists users (id INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL,\
               username VARCHAR (30) NOT NULL, password VARCHAR (30) NOT NULL)");
    if(!query.isActive())
    {
        qDebug("user");
    }

//goods  goodsstorage customs  goodsoutput  goodsinput


    query.exec("CREATE TABLE if not exists goodsstorage (id INTEGER PRIMARY KEY AUTOINCREMENT, storagecount DOUBLE NOT NULL,\
               storagprice DOUBLE NOT NULL, storagetotal DOUBLE NOT NULL, goodsid VARCHAR (50)\
               CONSTRAINT goods_id_goodsstorage REFERENCES goods (goodsid), goodsname VARCHAR (100) NOT NULL)");

    if(!query.isActive())
    {
        qDebug()<< "goodsstorage";
    }

    query.exec("CREATE TABLE if not exists customs (id integer primary key autoincrement, \
               name VARCHAR (50) NOT NULL, company VARCHAR (100) NOT NULL, address VARCHAR (100) NOT NULL, \
               phonenumber VARCHAR (100) NOT NULL, customstype VARCHAR (50) NOT NULL)");
    if(!query.isActive())
    {
        qDebug()<< "customs";

    }
    query.exec("CREATE TABLE if not exists goodsoutput (id INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL,\
               goodsid VARCHAR (50) CONSTRAINT goods_id_goodsout REFERENCES goods (goodsid), \
               goodsname VARCHAR (100) NOT NULL, outputcount DOUBLE NOT NULL, outputprice DOUBLE NOT NULL, \
               outputtotal DOUBLE NOT NULL, outputtime DATE NOT NULL, outputtype VARCHAR (100) NOT NULL,\
               customsid INTEGER CONSTRAINT customs_id_goodsoutput REFERENCES customs (id))");
    if(!query.isActive())
    {
        qDebug()<< "goodsoutput";

    }
    query.exec("CREATE TABLE if not exists  goodsinput (id INTEGER PRIMARY KEY \
               AUTOINCREMENT , inputcount DOUBLE NOT NULL, inputtime DATE NOT NULL,\
               inputprice DOUBLE NOT NULL, inputtotal DOUBLE NOT NULL, goodsid VARCHAR (50) CONSTRAINT goodsinput_id_goods \
               REFERENCES goods (goodsid), goodsname VARCHAR (100) NOT NULL, inputtype VARCHAR (100) NOT NULL, \
               customsid INTEGER CONSTRAINT customs_id_goodsinput REFERENCES customs (id))");
    if(!query.isActive())
    {
        qDebug() << "goodsinput";
    }

}
void LoginWidget::setWidget()
{

    //this->setStyleSheet("background-color: rgb(30,144,255);");


    accountLineEdit=new QLineEdit(this);
    accountLineEdit->setGeometry(207,120,207,32);
    accountLineEdit->setPlaceholderText("请输入账号");

    passwdLineEdit=new QLineEdit(this);
    passwdLineEdit->setGeometry(207,183,207,32);
    passwdLineEdit->setPlaceholderText("请输入密码");
    passwdLineEdit->setEchoMode(QLineEdit::Password);



    chgpasswdButton=new QPushButton(this);
    chgpasswdButton->setText(tr("修改密码"));
    chgpasswdButton->setGeometry(410,183,100,25);
    chgpasswdButton->setFlat(true);


    cancelButton=new QPushButton(this);
    cancelButton->setFlat(true);
    cancelButton->setGeometry(325,255,98,43);

    enterButton=new QPushButton(this);
    enterButton->setGeometry(145,255,98,43);
    enterButton->setFlat(true);
    enterButton->setShortcut(Qt::Key_Enter);
    enterButton->setShortcut(Qt::Key_Return);
    connect(enterButton,SIGNAL(clicked()),this,SLOT(pressEnter()));
    connect(cancelButton,SIGNAL(clicked()),this,SLOT(pressCancel()));

}

void LoginWidget::pressEnter()
{


    if(accountLineEdit->text().isEmpty())
    {
        msgLabel->setText("请输入账号");
        return ;
    }
    if(passwdLineEdit->text().isEmpty())
    {
        msgLabel->setText("请输入密码");
        return  ;
    }
    QString account=accountLineEdit->text();
    QString passwd=passwdLineEdit->text();
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
    if(dataaccount==account&&datapasswd==passwd)
    {
        w=new MainWindow();
        w->show();
        this->close();

    }
    else
    {
        msgLabel->setText("     账号或密码错误！        ");
        passwdLineEdit->clear();
        accountLineEdit->clear();
    }

}
void LoginWidget::alterPasswd()
{
    alter=new AlterPasswd();
    alter->show();
}
void LoginWidget::pressCancel()
{
    this->close();
}
void LoginWidget::paintEvent(QPaintEvent*)

{
    QPainter painter(this);
    QPixmap pix;
    pix.load(":/mainImag/login.png");
    painter.drawPixmap(0,0,this->width(),this->height(),pix);
}
void LoginWidget::mousePressEvent(QMouseEvent *e)
{
    last = e->globalPos();
}
void LoginWidget::mouseMoveEvent(QMouseEvent *e)
{
    int dx = e->globalX() - last.x();
    int dy = e->globalY() - last.y();

    last = e->globalPos();
    move(x()+dx, y()+dy);
}

void LoginWidget::mouseReleaseEvent(QMouseEvent *e)
{
    int dx = e->globalX() - last.x();
    int dy = e->globalY() - last.y();

    move(x()+dx, y()+dy);
}

LoginWidget::~LoginWidget()
{

}
