#include "polinom_builder.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Polinom_builder w;
    w.show();
    return a.exec();
}
