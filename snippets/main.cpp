#include <QCoreApplication>

#include "benchprimenums.h"
#include "benchrandmarks.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    runAllPrimeNumsBench();
    runAllRandomMarksBench();
    return 0;
}
