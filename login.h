#ifndef LOGIN_H
#define LOGIN_H

#include <QWidget>
#include <QPushButton>
#include <QLineEdit>
#include <QLabel>
#include <QDebug>
#include <QPainter>
#include <QPixmap>
#include <QStyle>
#include <QToolButton>
#include <QMouseEvent>
#include <QSqlQuery>
#include <QSqlError>
#include <QMessageBox>
#include "mainwindow.h"
#include <QStatusBar>
#include <QSqlDatabase>
#include "alterpasswd.h"

class LoginWidget : public QWidget
{
    Q_OBJECT

public:
    LoginWidget(QWidget *parent = 0);
    ~LoginWidget();
    void setWidget();
    void paintEvent(QPaintEvent*);
    bool createDatabase();
    void createTable();
private:

    QLineEdit *accountLineEdit;
    QLineEdit *passwdLineEdit;
    QPushButton *cancelButton;
    QPushButton *enterButton;
    QPushButton *chgpasswdButton;
    QPoint last;
    MainWindow *w;
    QStatusBar *statusBar;
    QLabel *msgLabel;
    QSqlDatabase dba;
    AlterPasswd * alter;


protected:
    void mousePressEvent(QMouseEvent *e);
    void mouseMoveEvent(QMouseEvent *e);
    void mouseReleaseEvent(QMouseEvent *e);
public slots:
    void pressEnter();
    void pressCancel();
    void alterPasswd();

};

#endif // LOGIN_H
