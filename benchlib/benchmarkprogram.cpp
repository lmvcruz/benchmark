#include "benchmarkprogram.h"

#include <float.h>

#include <QDebug>

//
// BenchmarkProgram Class
//
BenchmarkProgram::BenchmarkProgram()
{
    m_eval = nullptr;
}

BenchmarkProgram::BenchmarkProgram(BenchmarkEvaluation *eval)
{
    m_eval = eval;
}

void BenchmarkProgram::set_evaluation(BenchmarkEvaluation *eval)
{
    m_eval = eval;
}

QString BenchmarkProgram::ProgramName()
{
    return m_eval->name();
}

void BenchmarkProgram::add_instance(QString arg, QString out)
{
    QStringList args = {arg};
    m_args.push_back(args);
    m_expectedOutput.push_back(out);
}

void BenchmarkProgram::add_instance(QStringList args, QString out)
{
    m_args.push_back(args);
    m_expectedOutput.push_back(out);
}

bool BenchmarkProgram::Validate(QString arg, QString out)
{
    QStringList args = {arg};
    m_eval->run(args);
    return Compare(out);
}

bool BenchmarkProgram::Validate(QStringList args, QString out)
{
    m_eval->run(args);
    return Compare(out);
}

QString BenchmarkProgram::output()
{
    return m_eval->output();
}

void BenchmarkProgram::Run(QString arg)
{
    QStringList arglist = {arg};
    m_eval->run(arglist);
}

void BenchmarkProgram::Run(QStringList arg)
{
    m_eval->run(arg);
}

int BenchmarkProgram::time()
{
    return m_eval->time();
}

//
// StringEqualsEvaluation Class
//
StringEqualsCompProg::StringEqualsCompProg()
{
}

StringEqualsCompProg::StringEqualsCompProg(BenchmarkEvaluation *eval)
    : BenchmarkProgram(eval)
{
}

bool StringEqualsCompProg::Compare(QString out)
{
    return (m_eval->output() == out);
}

//
// StringEqualsEvaluation Class
//
NumberEqualsCompProg::NumberEqualsCompProg()
{
}

NumberEqualsCompProg::NumberEqualsCompProg(BenchmarkEvaluation *eval)
    : BenchmarkProgram(eval)
{
}

bool NumberEqualsCompProg::Compare(QString out)
{
    double evalout = m_eval->output().toDouble();
    double expectout = out.toDouble();
    return std::fabs(evalout-expectout)<FLT_EPSILON;
}
