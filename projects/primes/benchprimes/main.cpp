#include <QCoreApplication>
#include <QString>
#include <QDebug>

#include "ctk/ctkmath.h"

#include "benchlib/benchmarkevaluation.h"
#include "benchlib/benchmarkprogram.h"
#include "benchlib/benchmarkengine.h"

//
// Test Cases based on system call (SystemProcessEvaluation)
// Primes1: Brute Force;
// Primes 2: Erastotenes Sieve)
//
void evalPrimes1StringEquals()
{
    BenchmarkEvaluation* eval = new SystemProcessEvaluation("../primes1/primes1");
    BenchmarkProgram *prog = new StringEqualsCompProg(eval);
    qDebug() << prog->Validate("20000", "2262") << true;
    qDebug() << prog->Validate("20000", "1") << false;
    qDebug() << prog->Validate("40000", "4203") << true;
    qDebug() << prog->Validate("40000", "1") << false;
    qDebug() << prog->Validate("60000", "6057") << true;
    qDebug() << prog->Validate("80000", "7837") << true;
    qDebug() << prog->Validate("100000", "9592") << true;
}

void evalPrimes1NumberEquals()
{
    BenchmarkEvaluation* eval = new SystemProcessEvaluation("../primes2/primes2");
    BenchmarkProgram *prog = new StringEqualsCompProg(eval);
    qDebug() << prog->Validate("20000", "2262") << true;
    qDebug() << prog->Validate("20000", "1") << false;
    qDebug() << prog->Validate("40000", "4203") << true;
    qDebug() << prog->Validate("40000", "1") << false;
    qDebug() << prog->Validate("60000", "6057") << true;
    qDebug() << prog->Validate("80000", "7837") << true;
    qDebug() << prog->Validate("100000", "9592") << true;
}

void evalPrimes2StringEquals()
{
    BenchmarkEvaluation* eval = new SystemProcessEvaluation("../primes2/primes2");
    BenchmarkProgram *prog = new StringEqualsCompProg(eval);
    qDebug() << prog->Validate("20000", "2262") << true;
    qDebug() << prog->Validate("20000", "1") << false;
    qDebug() << prog->Validate("40000", "4203") << true;
    qDebug() << prog->Validate("40000", "1") << false;
    qDebug() << prog->Validate("60000", "6057") << true;
    qDebug() << prog->Validate("80000", "7837") << true;
    qDebug() << prog->Validate("100000", "9592") << true;
}

void multivalPrimesStringEquals()
{
    BenchmarkEngine engine;
    engine.add_program( new StringEqualsCompProg(new SystemProcessEvaluation("../primes1/primes1")) );
    engine.add_program( new StringEqualsCompProg(new SystemProcessEvaluation("../primes2/primes2")) );
    //
    QVector<QString> ins = {"20000", "20000", "40000", "40000", "60000", "80000", "100000"};
    QVector<QString> outs = {"2262", "1", "4203", "1", "6057", "7837", "9592"};
    engine.add_instances(ins, outs);
    // Show validatio if each
    engine.ValidateAll();
    // Show the overall validation rate
    qDebug() << engine.ValidationRate(0);
    // save a CSV file with the execution time
    engine.EvalPerformance("primes-system.csv");
}

//
// Test Cases based on classes that inherit from BenchmarkEvaluation
//  Using Benchmark Library
//
class PrimesBfEval : public BenchmarkEvaluation
{
private:

public:
    PrimesBfEval() : BenchmarkEvaluation() {}

    void Eval(QStringList args) {
        m_time.start();
        int qty = ctk::countPrimeNumbersBf( args[0].toInt() );
        m_out = QString::number(qty);
        m_procTime = m_time.elapsed();
    }
};

class PrimesEsEval : public BenchmarkEvaluation
{
private:

public:
    PrimesEsEval() : BenchmarkEvaluation() {}

    void Eval(QStringList args) {
        m_time.start();
        int qty = ctk::countPrimeNumbers( args[0].toInt() );
        m_out = QString::number(qty);
        m_procTime = m_time.elapsed();
    }
};

void evalBfPnEvalStringEquals()
{
    BenchmarkProgram *prog = new StringEqualsCompProg(new PrimesBfEval);
    qDebug() << prog->Validate("20000", "2262") << true;
    qDebug() << prog->Validate("20000", "1") << false;
    qDebug() << prog->Validate("40000", "4203") << true;
    qDebug() << prog->Validate("40000", "1") << false;
    qDebug() << prog->Validate("60000", "6057") << true;
    qDebug() << prog->Validate("80000", "7837") << true;
    qDebug() << prog->Validate("100000", "9592") << true;
}

void evalEsPnEvalStringEquals()
{
    BenchmarkEvaluation* eval = new PrimesEsEval;
    BenchmarkProgram *prog = new StringEqualsCompProg;
    prog->set_evaluation(eval);
    qDebug() << prog->Validate("20000", "2262") << true;
    qDebug() << prog->Validate("20000", "1") << false;
    qDebug() << prog->Validate("40000", "4203") << true;
    qDebug() << prog->Validate("40000", "1") << false;
    qDebug() << prog->Validate("60000", "6057") << true;
    qDebug() << prog->Validate("80000", "7837") << true;
    qDebug() << prog->Validate("100000", "9592") << true;
}

void multivalBfEsStringEquals()
{
    BenchmarkEngine engine;
    engine.add_program( new StringEqualsCompProg(new PrimesBfEval) );
    engine.add_program( new StringEqualsCompProg(new PrimesEsEval) );
    //
    QVector<QString> ins = {"20000", "20000", "40000", "40000", "60000", "80000", "100000"};
    QVector<QString> outs = {"2262", "1", "4203", "1", "6057", "7837", "9592"};
    engine.add_instances(ins, outs);
    // Show validatio if each
    engine.ValidateAll();
    // Show the overall validation rate
    qDebug() << engine.ValidationRate(0);
    // save a CSV file with the execution time
    engine.EvalPerformance("primes-benchlib.csv");
}

int main(int argc, char *argv[])
{
    QCoreApplication app(argc, argv);
    evalPrimes1StringEquals();
    evalPrimes1NumberEquals();
    evalPrimes2StringEquals();
    multivalPrimesStringEquals();
    //
    evalBfPnEvalStringEquals();
    evalEsPnEvalStringEquals();
    multivalBfEsStringEquals();
    //
    return 0;
}
