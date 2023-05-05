#include "mainwindow.h"
#include <QFile>
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QFile file(":/MainStyle.css");
    file.open(QFile::ReadOnly);
    a.setStyleSheet(file.readAll());

    MainWindow w;
    w.show();
    return a.exec();
}
