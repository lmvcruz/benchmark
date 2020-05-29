#ifndef BENCHMARKPROGRAM_H
#define BENCHMARKPROGRAM_H

#include <QVector>
#include <QString>

#include "benchmarkevaluation.h"

class BenchmarkProgram
{
protected:
    BenchmarkEvaluation *m_eval;
    QVector<QStringList> m_args;
    QVector<QString> m_expectedOutput;
    bool m_valid;

public:
    BenchmarkProgram();

    void setEvaluation(BenchmarkEvaluation *eval);

    void addInstance(QString arg, QString out);
    void addInstance(QStringList args, QString out);

    bool validate(QString arg, QString out);
    bool validate(QStringList args, QString out);

    QString output();

    void run(QString arg);
    void run(QStringList arg);
    int time();

    virtual bool compare(QString out) = 0;
protected:
};

class StringEqualsEvaluation : public BenchmarkProgram
{
public:
    StringEqualsEvaluation();

    bool compare(QString out);

protected:
};

class NumberEqualsEvaluation : public BenchmarkProgram
{
public:
    NumberEqualsEvaluation();

    bool compare(QString out);

protected:
};

#endif // BENCHMARKPROGRAM_H
