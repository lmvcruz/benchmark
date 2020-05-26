#include <iostream>
#include <vector>
#include <algorithm>

#include <QCoreApplication>
#include <QCommandLineParser>

#include "ctk/ctkmath.h"

using namespace std;

int main(int argc, char *argv[])
{
    QCoreApplication app(argc, argv);
    QCommandLineParser parser;
    parser.process(app);
    //
    QStringList args = parser.positionalArguments();
    std::cout << ctk::countPrimeNumbers( args[0].toInt() );
    return 0;
}
