#include "pemainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    PEMainWindow w;
    w.show();

    return a.exec();
}
