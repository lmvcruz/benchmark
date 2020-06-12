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

public:
    BenchmarkProgram();
    BenchmarkProgram(BenchmarkEvaluation *eval);
    virtual ~BenchmarkProgram();

    void set_evaluation(BenchmarkEvaluation *eval);

    QString program_name();

    void Clear();
    int CasesQuantities();

    void add_instance(QString arg, QString out);
    void add_instance(QStringList args, QString out);


    bool Validate(QString arg, QString out);
    bool Validate(QStringList args, QString out);
    bool ValidateCase(int idx);

    QString output();

    void Run(QString arg);
    void Run(QStringList arg);
    int time();

    virtual bool Compare(QString out) = 0;

    float ValidationRate();
    int EvalCasePerformance(int idx);
    int EvalFullPerformance();
};

class StringEqualsCompProg : public BenchmarkProgram
{
public:
    StringEqualsCompProg();
    StringEqualsCompProg(BenchmarkEvaluation *eval);

//    virtual ~StringEqualsCompProg();

    bool Compare(QString out);
};

class NumberEqualsCompProg : public BenchmarkProgram
{
public:
    NumberEqualsCompProg();
    NumberEqualsCompProg(BenchmarkEvaluation *eval);

//    virtual ~NumberEqualsCompProg();

    bool Compare(QString out);
};

#endif // BENCHMARKPROGRAM_H
