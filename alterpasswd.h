#ifndef ALTERPASSWD_H
#define ALTERPASSWD_H

#include <QWidget>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QMouseEvent>
#include <QSqlQuery>
#include <QSqlError>
#include <QMessageBox>
#include <QStatusBar>
#include <QSqlDatabase>
#include <QPainter>
#include <QToolButton>
#include <QStyle>
#include <QStatusBar>


class AlterPasswd : public QWidget
{
    Q_OBJECT
public:
    explicit AlterPasswd(QWidget *parent = 0);
    ~AlterPasswd();
    void paintEvent(QPaintEvent*);
private:
    QPushButton *entryButton;
    QPushButton *resetlButton;

    QLabel *accountLabel;
    QLabel *oldPasswdLabel;
    QLabel *newPasswdLabel;
    QLabel *renewPasswdLabel;

    QLineEdit *accountLineEdit;
    QLineEdit *oldPasswdLineEdit;
    QLineEdit *newPasswdLineEdit;
    QLineEdit *renewPasswdLineEdit;
    QPoint last;
    QStatusBar *statusBar;
    QLabel *msgLabel;




protected:
    void mousePressEvent(QMouseEvent *e);
    void mouseMoveEvent(QMouseEvent *e);
    void mouseReleaseEvent(QMouseEvent *e);
public slots:
    void pressEnter();
    void pressReset();

};

#endif // ALTERPASSWD_H
