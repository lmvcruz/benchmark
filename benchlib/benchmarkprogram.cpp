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

BenchmarkProgram::~BenchmarkProgram()
{
    if (m_eval!=nullptr) delete m_eval;
}

void BenchmarkProgram::set_evaluation(BenchmarkEvaluation *eval)
{
    m_eval = eval;
}

QString BenchmarkProgram::program_name()
{
    return m_eval->name();
}

void BenchmarkProgram::Clear()
{
    m_args.clear();
    m_expectedOutput.clear();
}

int BenchmarkProgram::CasesQuantities()
{
    return m_args.size();
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
    m_eval->Run(args);
    return Compare(out);
}

bool BenchmarkProgram::Validate(QStringList args, QString out)
{
    m_eval->Run(args);
    return Compare(out);
}

bool BenchmarkProgram::ValidateCase(int idx)
{
    m_eval->Run(m_args[idx]);
    return Compare(m_expectedOutput[idx]);
}

QString BenchmarkProgram::output()
{
    return m_eval->output();
}

void BenchmarkProgram::Run(QString arg)
{
    QStringList arglist = {arg};
    m_eval->Run(arglist);
}

void BenchmarkProgram::Run(QStringList arg)
{
    m_eval->Run(arg);
}

int BenchmarkProgram::time()
{
    return m_eval->time();
}

float BenchmarkProgram::ValidationRate()
{
    int corrects = 0;
    for (auto j=0; j<m_args.size(); j++) {
        try {
            if (Validate(m_args[j], m_expectedOutput[j])) {
                corrects++;
            }
        } catch (std::exception&) {
            //It is not necessary catch this exception
        }
    }
    return static_cast<float>(corrects)/static_cast<float>(m_args.size());

}

int BenchmarkProgram::EvalCasePerformance(int idx)
{
    Run(m_args[idx]);
    return time();
}

int BenchmarkProgram::EvalFullPerformance()
{
    int spent_time = 0;
    for (auto j=0; j<m_args.size(); j++) {
        spent_time += EvalCasePerformance(j);
    }
    return spent_time;
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

//StringEqualsCompProg::~StringEqualsCompProg()
//{
//    if (m_eval!=nullptr) delete m_eval;
//}

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

//NumberEqualsCompProg::~NumberEqualsCompProg()
//{
//    if (m_eval!=nullptr) delete m_eval;
//}

bool NumberEqualsCompProg::Compare(QString out)
{
    double evalout = m_eval->output().toDouble();
    double expectout = out.toDouble();
    return std::fabs(evalout-expectout)<FLT_EPSILON;
}
