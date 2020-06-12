#ifndef BENCHMARKENGINE_H
#define BENCHMARKENGINE_H

#include <QtCore/QtCore>
#include <QObject>
#include <QProcess>
#include <QString>
#include <QStringList>
#include <QTime>

#include "ctk/ctknumericmatrix.h"

#include "benchlib/benchmarkprogram.h"

class BenchmarkEngine
{
public:
    BenchmarkEngine() = default;
    ~BenchmarkEngine();

    void Read(QString filename);

    void add_program(BenchmarkProgram* p);
    void add_arg(QString in);
    void add_arg(QStringList in);
    void add_args(QVector<QString> args);

    void add_instance(QString in, QString out);
    void add_instance(QStringList in, QString out);
    void add_instances(QVector<QString> ins, QVector<QString> outs);


    void ValidateAll();
    float ValidationRate(int idx);
    void EvalPerformance(QString csvname);

private:
    QVector<BenchmarkProgram*> m_programs;
    //TODO: evaluate where to storage this values (here or in program)
    // should be in program, but it creates a problem when the json has only io
    // and the program is passed as a parameter
//    QVector<QStringList> m_inputs;
//    QVector<QString> m_stringsexpected;
};


#endif // BENCHMARKENGINE_H
