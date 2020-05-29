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

void BenchmarkProgram::setEvaluation(BenchmarkEvaluation *eval)
{
    m_eval = eval;
}

void BenchmarkProgram::addInstance(QString arg, QString out)
{
    QStringList args = {arg};
    m_args.push_back(args);
    m_expectedOutput.push_back(out);
}

void BenchmarkProgram::addInstance(QStringList args, QString out)
{
    m_args.push_back(args);
    m_expectedOutput.push_back(out);
}

bool BenchmarkProgram::validate(QString arg, QString out)
{
    QStringList args = {arg};
    m_eval->run(args);
    return compare(out);
}

bool BenchmarkProgram::validate(QStringList args, QString out)
{
    m_eval->run(args);
    return compare(out);
}

QString BenchmarkProgram::output()
{
    return m_eval->output();
}

void BenchmarkProgram::run(QString arg)
{
    QStringList arglist = {arg};
    m_eval->run(arglist);
}

void BenchmarkProgram::run(QStringList arg)
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
StringEqualsEvaluation::StringEqualsEvaluation()
{
}

bool StringEqualsEvaluation::compare(QString out)
{
    return (m_eval->output() == out);
}

//
// StringEqualsEvaluation Class
//
NumberEqualsEvaluation::NumberEqualsEvaluation()
{

}

bool NumberEqualsEvaluation::compare(QString out)
{
    double evalout = m_eval->output().toDouble();
    double expectout = out.toDouble();
    return std::fabs(evalout-expectout)<FLT_EPSILON;
}
