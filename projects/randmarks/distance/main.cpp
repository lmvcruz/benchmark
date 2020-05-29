#include <iostream>

#include <QCoreApplication>
#include <QCommandLineParser>
#include <QStringList>
#include <QString>
#include <QDebug>

#include "ctk/ctkmath.h"
#include "ctk/utils/filesys/filesystem.h"

#include "randmark.h"

int main(int argc, char *argv[])
{
    QCoreApplication app(argc, argv);
    QCommandLineParser parser;
    parser.process(app);
    //
    Descriptor* desc = new DistanceDescriptor;
    desc->setRange(151, 0, 150);
    //
    QStringList preargs = parser.positionalArguments();
    QStringList args = preargs[0].split(" ");
    QString datadb = args[0];
    QString setregname = datadb+"/"+args[1];
    QString setvalname = datadb+"/"+args[2];

    SetMark reg;
    reg.Open(setregname);
    Histogram h1 = desc->Calculate(reg.get(0));
    //
    SetMark val;
    val.Open(setvalname);
    int smp = args[3].toInt();
    Histogram h2 = desc->Calculate(val.get(smp));
    //
    int thresh = args[4].toInt();
    thresh = 80;
    //
    int d = h1.Distance(h2);
    if (d<=thresh) {
        std::cout << "1";
    }
    else {
        std::cout << "0";
    }
    //
    return 0;
}
