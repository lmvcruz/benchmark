#include <iostream>

#include <QCoreApplication>

//#include "benchmarklib/benchmarklib.h"
#include "benchmarkengine.h"

using namespace std;

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
//    BenchmarkProgram prog;
//    prog.read("../../benchmark/projects/genomicrangequery/setup/grq1_1.json");
//    prog.run();
//    prog.showReport();
    //
    BenchmarkEngine engine;
    engine.read("../../benchmark/projects/genomicrangequery/setup/bench1.json");
    engine.run();
    return 0;
}
