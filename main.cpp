#include "aamrec.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    AAMrec w;
    w.show();

    return a.exec();
}
