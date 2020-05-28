#include <iostream>
#include <vector>
#include <algorithm>

#include <QCoreApplication>
#include <QCommandLineParser>

#include "ctk/ctkmath.h"

#include "mark.h"
#include "randmark.h"

using namespace std;

int main(int argc, char *argv[])
{
    QCoreApplication app(argc, argv);
    QCommandLineParser parser;
    parser.process(app);
    //
    QStringList args = parser.positionalArguments();
    MarkDB db;
    db.Open("../../benchmark/projects/randmarks/data");
    Descriptor* desc = new QuantityDescriptor;
    desc->setRange(1, 0, 1000);
    db.CreateDescriptor(desc);
    //
    for (int i=1; i<=10; i++) {
        std::cout << "Thresh: " << i << std::endl;
        db.Compare(i);
    }
    //
    return 0;
}
