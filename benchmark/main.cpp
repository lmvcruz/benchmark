#include <iostream>

#include <QCoreApplication>

//#include "benchmarklib/benchmarklib.h"
#include "benchmarkengine.h"

using namespace std;

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    BenchmarkEngine engine;
    // EX: "../../benchmark/projects/genomicrangequery/setup/bench1.json"
    if (argc>1) {
        QString args(argv[1]);
        engine.read(args);
        engine.run();
    }
    return 0;
}
