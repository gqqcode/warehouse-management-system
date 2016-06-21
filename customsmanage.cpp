#include "customsManage.h"
extern bool customsisChange;

CustomsManage::CustomsManage(QWidget *parent)
    : QWidget(parent)
{
    setWindowIcon(QIcon(":/mainImag/nuoya.png"));
    this->setAttribute(Qt::WA_QuitOnClose,false);
    oper=0;
    this->setFixedSize(1000,700);
    this->setWindowTitle("客户管理");

    createAction();

    createLabel_LineEdit();
    createButton();

    createTableView();
    selectShow();
}
void CustomsManage::createTableView()
{
    mainTableView=new QTableView(this);
    mainTableView->setGeometry(100,200,810,450);
    mainTableView->setContextMenuPolicy(Qt::CustomContextMenu);
    mainTableView->setEditTriggers(QTableView::NoEditTriggers);
    msgLabel=new QLabel();
    msgLabel->setMinimumSize(msgLabel->sizeHint());
    msgLabel->setAlignment(Qt::AlignLeft);
    myStatusBar=new QStatusBar(this);
    myStatusBar->setGeometry(0,660,1000,40);

    QFont ft;
    ft.setPointSize(12);

    //设置颜色
    QPalette pa;
    pa.setColor(QPalette::WindowText,Qt::red);
    myStatusBar->addWidget(msgLabel);
    myStatusBar->setFixedHeight(40);
    myStatusBar->setFont(ft);
    myStatusBar->setPalette(pa);

    connect(mainTableView, SIGNAL(customContextMenuRequested(const QPoint&)),this, SLOT(showContextMenu(const QPoint&)));

    mainTableView->setContextMenuPolicy(Qt::CustomContextMenu);
    tableModel = new QStandardItemModel();
    tableModel->setHorizontalHeaderItem(0, new QStandardItem(QObject::tr("客户编号 ")));
    tableModel->setHorizontalHeaderItem(1, new QStandardItem(QObject::tr("客户姓名 ")));
    tableModel->setHorizontalHeaderItem(2, new QStandardItem(QObject::tr("客户单位 ")));
    tableModel->setHorizontalHeaderItem(3, new QStandardItem(QObject::tr("客户地址 ")));
    tableModel->setHorizontalHeaderItem(4, new QStandardItem(QObject::tr("客户电话 ")));
    tableModel->setHorizontalHeaderItem(5, new QStandardItem(QObject::tr("客户类型 ")));


    mainTableView->setModel(tableModel);
}
void CustomsManage::createButton()
{
    resetButton=new QPushButton(tr("重置"),this);
    resetButton->setGeometry(800,50,100,40);
    connect(resetButton,SIGNAL(clicked()),this,SLOT(resetFun()));


    saveButton=new QPushButton(tr("保存"),this);
    saveButton->setGeometry(800,100,100,40);
    connect(saveButton,SIGNAL(clicked()),this,SLOT(savaFun()));


}
void CustomsManage::createLabel_LineEdit()
{
    nameLabel=new QLabel(tr("客户姓名:"),this);
    nameLabel->setGeometry(100,55,80,40);
    nameLineEdit=new QLineEdit(this);
    nameLineEdit->setGeometry(180,57,200,30);

    companyLabel=new QLabel(tr("客户单位:"),this);
    companyLabel->setGeometry(450,55,80,40);
    companyLineEdit=new QLineEdit(this);
    companyLineEdit->setGeometry(530,57,200,30);


    addressLabel=new QLabel(tr("客户地址:"),this);

    addressLabel->setGeometry(100,90,80,40);
    addressLineEdit=new QLineEdit(this);
    addressLineEdit->setGeometry(180,95,200,30);



    phonenumLabel=new QLabel(tr("客户电话:"),this);
    phonenumLabel->setGeometry(450,90,80,40);
    phonenumLineEdit=new QLineEdit(this);
    phonenumLineEdit->setGeometry(530,95,200,30);
    QRegExp regExp("[1-9][0-9]+$");
    QValidator *validator = new QRegExpValidator(regExp,phonenumLineEdit );//正则表达式

    phonenumLineEdit->setValidator(validator);


    customstypeLabel=new QLabel(tr("客户类型:"),this);

    customstypeLabel->setGeometry(100,130,80,40);
    customstypeComboBox=new QComboBox(this);
    //customstypeComboBox->setAutoCompletion(true);
    //customstypeComboBox->setEditable(true);
    customstypeComboBox->addItem(tr("销售"));
    customstypeComboBox->addItem(tr("赠送"));

    customstypeComboBox->setGeometry(180,132,200,30);
}

void CustomsManage::paintEvent(QPaintEvent*)

{
    QPainter painter(this);
    QPixmap pix;
    pix.load(":/mainImag/background.png");
    painter.drawPixmap(0,0,this->width(),this->height(),pix);
}

void CustomsManage::createAction()
{

    alterAct=new QAction(QIcon(":/image/alter.png"),tr("修改"),this);
    connect(alterAct,SIGNAL(triggered()),this,SLOT(alterRecord()));

    deleteAct=new QAction(QIcon(":/image/alter.png"),tr("删除"),this);
    connect(deleteAct,SIGNAL(triggered()),this,SLOT(deleteRecord()));


}



void CustomsManage::alterRecord()
{
    rowNum= mainTableView->currentIndex().row();

    updatedId=tableModel->item(rowNum, 0)->text().toInt();
    nameLineEdit->setText(tableModel->item(rowNum, 1)->text());
    companyLineEdit->setText(tableModel->item(rowNum, 2)->text());
    addressLineEdit->setText(tableModel->item(rowNum, 3)->text());
    phonenumLineEdit->setText(tableModel->item(rowNum, 4)->text());

    customstypeComboBox->setCurrentText(tableModel->item(rowNum, 5)->text());
    //msgLabel->setText("<h3><font color=red>当前操作：修改顾客信息</font></h3>");
    oper=1;
}


void CustomsManage::deleteRecord()
{
    QSqlQuery query;
    int row=mainTableView->currentIndex().row();
    QString delete_sql = "delete from customs where id = ?";

    query.prepare(delete_sql);
    query.addBindValue(tableModel->item(row, 0)->text().toInt());
    if(!query.exec())
    {
        QMessageBox::warning(this,"警告","客户信息删除失败,可能不存在该客户信息！");
    }
    else
    {
        tableModel->removeRow(row);
        msgLabel->setText("<h3><font color=red>客户信息删除成功！</font></h3>");
    }
}

void CustomsManage::showContextMenu(const QPoint& pos)//contextMenuEvent(QContextMenuEvent * event)
{
    if(rightMenu)//保证同时只存在一个menu，及时释放内存
    {
        delete rightMenu;
        rightMenu = NULL;
    }
    if( mainTableView->currentIndex().isValid())
    {


        rightMenu = new QMenu(this);
        rightMenu->addAction(alterAct);
        rightMenu->addAction(deleteAct);
        rightMenu->exec(QCursor::pos()); // 菜单出现的位置为当前鼠标的位置
    }
}

void CustomsManage::resetFun()
{
    nameLineEdit->clear();
    companyLineEdit->clear();
    addressLineEdit->clear();
    phonenumLineEdit->clear();

}

void CustomsManage::savaFun()
{
    QSqlQuery query;
    if(nameLineEdit->text().isEmpty())
    {
        QMessageBox::warning(this,"警告","请输入客户的姓名");
        return;
    }

    switch(oper)
    {
    case 1:
    {


        QString update_sql="update customs set name =:name, company =:company ,  address =:address ,\
                phonenumber =:phonenumber  , customstype =:customstype  where id = :updatedId";
        query.prepare(update_sql);
        query.bindValue(":updatedId",updatedId);
        qDebug() << updatedId;
        query.bindValue(":name", nameLineEdit->text());
        query.bindValue(":company", companyLineEdit->text());
        query.bindValue(":address",addressLineEdit->text() );
        query.bindValue(":phonenumber",phonenumLineEdit->text());
        query.bindValue(":customstype", customstypeComboBox->currentText());

        if(!query.exec())
        {
            qDebug() << query.lastError();
            resetFun();
        }
        else
        {
            msgLabel->setText("<h3><font color=red>客户信息修改成功！</font></h3>");

            tableModel->item(rowNum, 1)->setText(nameLineEdit->text());
            tableModel->item(rowNum, 2)->setText(companyLineEdit->text());
            tableModel->item(rowNum, 3)->setText(addressLineEdit->text());
            tableModel->item(rowNum, 4)->setText(phonenumLineEdit->text());
            tableModel->item(rowNum, 5)->setText(customstypeComboBox->currentText());
            resetFun();
        }

            oper=0;
            break;
    }
    case 0:
    {
        msgLabel->setText("<h3><font color=red>当前操作：添加客户信息</font></h3>");
        QString insert_sql = "insert into customs(name ,company, address,phonenumber, customstype )  values (?,?,?,?,?)";//


        query.prepare(insert_sql);

        query.addBindValue(nameLineEdit->text());
        query.addBindValue(companyLineEdit->text());
        query.addBindValue(addressLineEdit->text());
        query.addBindValue(phonenumLineEdit->text());
        query.addBindValue(customstypeComboBox->currentText());

        if(!query.exec())
        {
            qDebug() << query.lastError();
            resetFun();
        }
        else
        {
            int rowCount=tableModel->rowCount();
            tableModel->setItem(rowCount,0,new QStandardItem(query.lastInsertId().toString()));
            tableModel->setItem(rowCount,1,new QStandardItem(nameLineEdit->text()));
            tableModel->setItem(rowCount,2,new QStandardItem(companyLineEdit->text()));
            tableModel->setItem(rowCount,3,new QStandardItem(addressLineEdit->text()));
            tableModel->setItem(rowCount,4,new QStandardItem(phonenumLineEdit->text()));
            tableModel->setItem(rowCount,5,new QStandardItem(customstypeComboBox->currentText()));

            msgLabel->setText("<h3><font color=red>商品信息添加成功！</font></h3>");
            resetFun();
        }

    break;
    }
    }

}


void CustomsManage::selectShow()
{
    QString select_sql = "select * from customs";
    QSqlQuery query;
    int i=0;
    if(!query.exec(select_sql))
    {
        qDebug()<<query.lastError();
    }
    else
    {
        //name ,company, address,phonenumber, customstype

        while(query.next())
        {
            tableModel->setItem(i,0,new QStandardItem(query.value("id").toString()));
            tableModel->setItem(i,1,new QStandardItem(query.value("name").toString()));
            tableModel->setItem(i,2,new QStandardItem(query.value("company").toString()));
            tableModel->setItem(i,3,new QStandardItem(query.value("address").toString()));
            tableModel->setItem(i,4,new QStandardItem(query.value("phonenumber").toString()));
            tableModel->setItem(i,5,new QStandardItem(query.value("customstype").toString()));

            i++;
        }
    }
}
CustomsManage::~CustomsManage()
{
    qDebug() << "customs";
}
