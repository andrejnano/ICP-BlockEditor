#include "mainwindow.h"
#include <QApplication>
#include <QGraphicsScene>
#include <QGraphicsRectItem>
#include <QGraphicsView>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    // main app window
    MainWindow w;
    w.show();

    return a.exec();
}
