#include "databaseapp.h"

#include <QApplication>

#include <thread>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    DatabaseApp w;

    w.show();

    return a.exec();
}
