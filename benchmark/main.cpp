#include <iostream>

#include <QCoreApplication>

#include "benchmarklib/benchmarklib.h"
#include "benchmarkengine.h"

using namespace std;


int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    BenchmarkProgram prog;
    prog.read("../../projects/genomicrangequery/setup/grq1_1.json");
    prog.run();
    prog.showReport();
    return 0;
}
