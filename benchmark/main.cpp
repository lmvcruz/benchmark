#include <iostream>

#include <QCoreApplication>

#include "benchlib/benchmarkengine.h"

using namespace std;


int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    BenchmarkEngine engine;
    // EX: "../../benchmark/projects/genomicrangequery/setup/bench1.json"
    // EX: "../../benchmark/projects/genomicrangequery/setup/primes1_val.json"
    if (argc>1) {
        QString args = "../../benchmark/projects/primes/setup/primes1_val.txt";
        engine.read(args);
        engine.ValidateAll();
        engine.performance();
    }
    return 0;
}
