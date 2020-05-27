#include <iostream>
#include <vector>
#include <algorithm>

#include <QCoreApplication>
#include <QCommandLineParser>
#include <QFile>
#include <QTextStream>
#include <QString>
#include <QDebug>


#include "ctk/ctkmath.h"
#include "ctk/ctkpoint.h"
#include "ctk/utils/filesys/filesystem.h"

#include "mark.h"
#include "randmark.h"

using namespace std;

SetMark createMark(int setSize)
{
    SetMark set;
    SampleMark m;
    m.createUniformSampleMark(5 + (rand() % 20), 0.0, 100.0, 0.0, 100.0);
    set.addMark(m);
    for (auto i=1; i<setSize; i++) {
        SampleMark nm = m;
        nm.addRandomTranslationNoise(0.3, 2.0);
        float dr = static_cast<double>((rand() % 5)-2)*0.1;
        nm.addDeletionNoise(dr);
        float ir = static_cast<double>((rand() % 5)-2)*0.1;
        nm.addInsertionNoise(ir, 0.0, 100.0, 0.0, 100.0);
        set.addMark(nm);
    }
    return set;
}

MarkDB createMarkDb(int dbSize, int setSize)
{
    qDebug() << "Creating Mark DB";
    MarkDB db;
    for (auto i=0; i<dbSize; i++) {
        qDebug() << "Mark:" << i;
        SetMark set = createMark(setSize);
        db.addSetMark(set);
    }
    return db;
}

int main(int argc, char *argv[])
{
    QCoreApplication app(argc, argv);
    MarkDB db = createMarkDb(10, 5);
    db.Save("../../benchmark/projects/randmarks/data");
    //
    return 0;
}
