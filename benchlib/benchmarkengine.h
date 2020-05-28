#ifndef BENCHMARKENGINE_H
#define BENCHMARKENGINE_H

#include <QtCore/QtCore>
#include <QObject>
#include <QProcess>
#include <QString>
#include <QStringList>
#include <QTime>

#include "ctk/ctknumericmatrix.h"

//#include "benchlib/benchmarkevaluation.h"
#include "benchlib/benchmarkprogram.h"

class BenchmarkEngine
{
public:
    BenchmarkEngine() = default;

    void addProgram(BenchmarkProgram* p);
    void addArg(QString in);
    void addArg(QStringList in);
    void addInstance(QString in, QString out);
    void addInstance(QStringList in, QString out);

    void read(QString filename);

    void ValidateAll();

    float ValidationRate();

    void performance();

private:
    QVector<BenchmarkProgram*> m_programs;
    QVector<QStringList> m_inputs;
    QVector<QString> m_stringsexpected;
};


#endif // BENCHMARKENGINE_H
