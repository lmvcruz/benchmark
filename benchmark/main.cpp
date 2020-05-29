#include <iostream>

#include <QCoreApplication>

#include "benchlib/benchmarkengine.h"

#include "ctk/utils/filesys/filesystem.h"

using namespace std;


int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    BenchmarkEngine engine;
    // EX: "../../benchmark/projects/genomicrangequery/setup/bench1.json"
    // EX: "../../benchmark/projects/genomicrangequery/setup/primes1_val.json"
    if (1) {
//        QString args = "../../benchmark/projects/primes/setup/primes1_val.txt";
//        QString args = "../../benchmark/projects/randmarks/setup/test1.txt";
        QString args = "../../benchmark/projects/randmarks/setup/full.txt";
        engine.read(args);
//        engine.ValidateAll();
//        engine.performance();
        qDebug() << engine.ValidationRate(0);
        qDebug() << engine.ValidationRate(1);
    }
    return 0;
}
