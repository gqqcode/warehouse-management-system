#ifndef CustomsManage_H
#define CustomsManage_H

#include <QMainWindow>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QWidget>
#include <QDialog>
#include <QPainter>
#include <QTableView>
#include <QStandardItemModel>
#include <QComboBox>
#include <QStatusBar>
#include <QMessageBox>
#include <QMenu>
#include <QSqlError>
#include <QSqlQuery>
#include <QStatusBar>
#include <QDebug>

class CustomsManage : public QWidget
{
    Q_OBJECT

public:
    CustomsManage(QWidget *parent = 0);
    ~CustomsManage();
    void paintEvent(QPaintEvent*);
    void createAction();
    void createButton();
    void createTableView();
    void createLabel_LineEdit();
    void selectShow();

private:
    QLabel *nameLabel;
    QLabel *companyLabel;
    QLabel *addressLabel;
    QLabel *phonenumLabel;
    QLabel *customstypeLabel;
    QLineEdit *nameLineEdit;
    QLineEdit *companyLineEdit;
    QLineEdit *addressLineEdit;
    QLineEdit *phonenumLineEdit;
    QComboBox *customstypeComboBox;
    QPushButton *resetButton;
    QPushButton *saveButton;
    QTableView *mainTableView;
    QStandardItemModel *tableModel;
    QStatusBar *myStatusBar;
    QLabel *msgLabel;
    QMenu *rightMenu=NULL;//右键菜单


    QAction *alterAct;//修改
    QAction *deleteAct;
public slots:
    void alterRecord();
    void deleteRecord();
    void showContextMenu(const QPoint& pos);
    void resetFun();
    void savaFun();
signals:
    void sendBuf(QString Qbuf);
    void sendStatus(const QString Status);//如果有信息更新发送信号给入库和出库
protected:
    int oper;//记录添加的保存还是修改的保存
    int updatedId;//记录修改的客户的id
    int rowNum;//记录修改的tableview的行号

};

#endif // CustomsManage_H
