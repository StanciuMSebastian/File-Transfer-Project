#include "LoginWindow.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    Client* C = C->getInstance();

    QApplication a(argc, argv);

    LoginWindow w;
    w.show();

    return a.exec();
}
