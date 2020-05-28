#include "benchprimenums.h"

#include "ctk/ctkmath.h"

#include "benchlib/benchmarkevaluation.h"
#include "benchlib/benchmarkprogram.h"
#include "benchlib/benchmarkengine.h"

void evalPrimes1StringEquals()
{
    BenchmarkEvaluation* eval = new SystemProcessEvaluation("../primes1/primes1");
    BenchmarkProgram *prog = new StringEqualsEvaluation;
    prog->setEvaluation(eval);
    qDebug() << prog->validate("20000", "2262") << true;
    qDebug() << prog->validate("20000", "1") << false;
    qDebug() << prog->validate("40000", "4203") << true;
    qDebug() << prog->validate("40000", "1") << false;
    qDebug() << prog->validate("60000", "6057") << true;
    qDebug() << prog->validate("80000", "7837") << true;
    qDebug() << prog->validate("100000", "9592") << true;
}

void evalPrimes1NumberEquals()
{
    BenchmarkEvaluation* eval = new SystemProcessEvaluation("../primes1/primes1");
    BenchmarkProgram *prog = new NumberEqualsEvaluation;
    prog->setEvaluation(eval);
    qDebug() << prog->validate("20000", "2262") << true;
    qDebug() << prog->validate("20000", "1") << false;
    qDebug() << prog->validate("40000", "4203") << true;
    qDebug() << prog->validate("40000", "1") << false;
    qDebug() << prog->validate("60000", "6057") << true;
    qDebug() << prog->validate("80000", "7837") << true;
    qDebug() << prog->validate("100000", "9592") << true;
}

void evalPrimes2StringEquals()
{
    BenchmarkEvaluation* eval = new SystemProcessEvaluation("../primes2/primes2");
    BenchmarkProgram *prog = new StringEqualsEvaluation;
    prog->setEvaluation(eval);
    qDebug() << prog->validate("20000", "2262") << true;
    qDebug() << prog->validate("20000", "1") << false;
    qDebug() << prog->validate("40000", "4203") << true;
    qDebug() << prog->validate("40000", "1") << false;
    qDebug() << prog->validate("60000", "6057") << true;
    qDebug() << prog->validate("80000", "7837") << true;
    qDebug() << prog->validate("100000", "9592") << true;
}


void multivalPrimesStringEquals()
{
    BenchmarkEngine engine;
    //
    BenchmarkProgram *progBf = new StringEqualsEvaluation;
    BenchmarkEvaluation* evalBf = new SystemProcessEvaluation("../primes1/primes1");
    progBf->setEvaluation(evalBf);
    engine.addProgram(progBf);
    //
    BenchmarkEvaluation* evalEs = new SystemProcessEvaluation("../primes2/primes2");
    BenchmarkProgram *progEs = new StringEqualsEvaluation;
    progEs->setEvaluation(evalEs);
    engine.addProgram(progEs);
    //
    engine.addInstance("20000", "2262");
    engine.addInstance("20000", "1");
    engine.addInstance("40000", "4203");
    engine.addInstance("40000", "1");
    engine.addInstance("60000", "6057");
    engine.addInstance("80000", "7837");
    engine.addInstance("100000", "9592");
    engine.ValidateAll();
    qDebug() << engine.ValidationRate();
    engine.performance();
}

void perfPrimesStringEquals()
{
    BenchmarkEngine engine;
    //
    BenchmarkProgram *progBf = new StringEqualsEvaluation;
    BenchmarkEvaluation* evalBf = new SystemProcessEvaluation("../primes1/primes1");
    progBf->setEvaluation(evalBf);
    engine.addProgram(progBf);
    //
    BenchmarkEvaluation* evalEs = new SystemProcessEvaluation("../primes2/primes2");
    BenchmarkProgram *progEs = new StringEqualsEvaluation;
    progEs->setEvaluation(evalEs);
    engine.addProgram(progEs);
    //
    engine.addArg("20000");
    engine.addArg("40000");
    engine.addArg("60000");
    engine.addArg("80000");
    engine.addArg("100000");
    engine.performance();
}

class BfPnEval : public BenchmarkEvaluation
{
public:
    BfPnEval() : BenchmarkEvaluation(){}

    void eval(QStringList args) {
        m_time.start();
        int qty = ctk::countPrimeNumbersBf( args[0].toInt() );
        m_procTime = m_time.elapsed();
        m_out = QString::number(qty);
    }
};

class EsPnEval : public BenchmarkEvaluation
{
public:
    EsPnEval() : BenchmarkEvaluation(){}

    void eval(QStringList args) {
        m_time.start();
        int qty = ctk::countPrimeNumbers( args[0].toInt() );
        m_procTime = m_time.elapsed();
        m_out = QString::number(qty);
    }
};

void evalBfPnEvalStringEquals()
{
    BenchmarkEvaluation* eval = new BfPnEval;
    BenchmarkProgram *prog = new StringEqualsEvaluation;
    prog->setEvaluation(eval);
    qDebug() << prog->validate("20000", "2262") << true;
    qDebug() << prog->validate("20000", "1") << false;
    qDebug() << prog->validate("40000", "4203") << true;
    qDebug() << prog->validate("40000", "1") << false;
    qDebug() << prog->validate("60000", "6057") << true;
    qDebug() << prog->validate("80000", "7837") << true;
    qDebug() << prog->validate("100000", "9592") << true;
}

void evalEsPnEvalStringEquals()
{
    BenchmarkEvaluation* eval = new EsPnEval;
    BenchmarkProgram *prog = new StringEqualsEvaluation;
    prog->setEvaluation(eval);
    qDebug() << prog->validate("20000", "2262") << true;
    qDebug() << prog->validate("20000", "1") << false;
    qDebug() << prog->validate("40000", "4203") << true;
    qDebug() << prog->validate("40000", "1") << false;
    qDebug() << prog->validate("60000", "6057") << true;
    qDebug() << prog->validate("80000", "7837") << true;
    qDebug() << prog->validate("100000", "9592") << true;
}

void multivalBfEsStringEquals()
{
    BenchmarkEngine engine;
    //
    BenchmarkProgram *progBf = new StringEqualsEvaluation;
    BenchmarkEvaluation* evalBf = new BfPnEval;
    progBf->setEvaluation(evalBf);
    engine.addProgram(progBf);
    //
    BenchmarkEvaluation* evalEs = new EsPnEval;
    BenchmarkProgram *progEs = new StringEqualsEvaluation;
    progEs->setEvaluation(evalEs);
    engine.addProgram(progEs);
    //
    engine.addInstance("20000", "2262");
    engine.addInstance("20000", "1");
    engine.addInstance("40000", "4203");
    engine.addInstance("40000", "1");
    engine.addInstance("60000", "6057");
    engine.addInstance("80000", "7837");
    engine.addInstance("100000", "9592");
    engine.ValidateAll();
    qDebug() << engine.ValidationRate();
    engine.performance();
}

void runAllPrimeNumsBench()
{
    evalPrimes1StringEquals();
    evalPrimes1NumberEquals();
    evalPrimes2StringEquals();
    multivalPrimesStringEquals();

    evalBfPnEvalStringEquals();
    evalEsPnEvalStringEquals();
    multivalBfEsStringEquals();
}
