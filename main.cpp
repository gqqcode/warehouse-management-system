#include <QApplication>
#include "login.h"
#include "mainwindow.h"
int main(int argc, char *argv[])
{


    QApplication a(argc, argv);
    //QApplication::addLibraryPath("./plugins");
    LoginWidget login;
    login.show();


    return a.exec();
}
