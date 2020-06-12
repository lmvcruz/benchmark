#include "benchrand.h"

#include <iostream>
#include <float.h>

#include "benchlib/benchmarkevaluation.h"
#include "benchlib/benchmarkprogram.h"
#include "benchlib/benchmarkengine.h"

#include "randmark.h"

class QuantityRmEval : public BenchmarkEvaluation
{
private:
    Descriptor* desc;
    int m_thresh;

public:
    QuantityRmEval(int t) : BenchmarkEvaluation(){
        m_thresh = t;
        desc = new QuantityDescriptor;
        desc->setRange(1, 0, 1);
    }

    virtual ~QuantityRmEval() {
        if (desc!=nullptr) delete desc;
    }


    QString name() override {
        return "QuantityRmEval";
    }

    void Eval(QStringList args_non) {
        QStringList args = args_non[0].split(" ");
        QString dirdata = args[0];
        QString sreg = dirdata +"/"+ args[1];
        SetMark reg;
        reg.Open(sreg);
        Histogram h1 = desc->Calculate(reg.get(0));
        //
        QString sval = dirdata +"/"+ args[2];
        SetMark val;
        val.Open(sval);
        int smp = args[3].toInt();
        Histogram h2 = desc->Calculate(val.get(smp));
        //
        m_time.start();
        int d = h1.Distance(h2);
        if (d<=m_thresh) m_out = "1";
        else m_out = "0";
        m_procTime = m_time.elapsed();
    }
};

float ValidationAllMarksQuantityDesc(int thresh)
{
    BenchmarkEngine engine;
    engine.Read("../../benchmark/projects/randmarks/setup/full.txt");
    engine.add_program( new StringEqualsCompProg(new QuantityRmEval(thresh)) );
    return engine.ValidationRate(0);
}

class DistanceRmEval : public BenchmarkEvaluation
{
private:
    Descriptor* desc;
    int m_thresh;

public:
    DistanceRmEval(int t) : BenchmarkEvaluation(){
        m_thresh = t;
        desc = new DistanceDescriptor;
        desc->setRange(300, 0., 100.0);
    }

    virtual ~DistanceRmEval() {
        if (desc!=nullptr) delete desc;
    }

    void Eval(QStringList args_non) {
        QStringList args = args_non[0].split(" ");
        QString dirdata = args[0];
        QString sreg = dirdata +"/"+ args[1];
        SetMark reg;
        reg.Open(sreg);
        Histogram h1 = desc->Calculate(reg.get(0));
        //
        QString sval = dirdata +"/"+ args[2];
        SetMark val;
        val.Open(sval);
        int smp = args[3].toInt();
        Histogram h2 = desc->Calculate(val.get(smp));
        //
        m_time.start();
        int d = h1.Distance(h2);
        if (d<=m_thresh) m_out = "1";
        else m_out = "0";
        m_procTime = m_time.elapsed();
    }
};

float ValidationAllMarksDistanceDesc(int thresh)
{
    BenchmarkEngine engine;
    engine.Read("../../benchmark/projects/randmarks/setup/full.txt");
    engine.add_program( new StringEqualsCompProg(new DistanceRmEval(thresh)) );
    return engine.ValidationRate(0);
}

//TODO: use functors to avoid code duplication
void CrossValidationQuantity()
{
    int bthresh = -1;
    float brate = FLT_MAX;
    for (int i=1; i<=40; i++) {
        int thresh = i;
        float r = ValidationAllMarksQuantityDesc(thresh);
        if (r<brate) {
            brate = r;
            bthresh = thresh;
        }
    }
    qDebug() << "Best Threshold:" << bthresh;
    qDebug() << "Best Rate:" << brate;
}

void CrossValidationDistance()
{
    int bthresh = -1;
    float brate = FLT_MAX;
    for (int i=1; i<=40; i++) {
        int thresh = 2*i;
        float r = ValidationAllMarksDistanceDesc(thresh);
        if (r<brate) {
            brate = r;
            bthresh = thresh;
        }
    }
    qDebug() << "Best Threshold:" << bthresh;
    qDebug() << "Best Rate:" << brate;
}


void runAllRandomMarksBench()
{
    qDebug() << ValidationAllMarksQuantityDesc(1);
    qDebug() << ValidationAllMarksDistanceDesc(80);
    CrossValidationQuantity();
    CrossValidationDistance();
}
