#include <QApplication>
#include "program.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Program window;
    window.show();
    return a.exec();
}
