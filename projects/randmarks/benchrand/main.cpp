#include <QCoreApplication>

#include "createrm.h"
#include "benchrand.h"

int main(int argc, char *argv[])
{
    QCoreApplication app(argc, argv);
//    createRandomMarkDb();
//    createSetupFile();
    runAllRandomMarksBench();
    //
    return 0;
}
