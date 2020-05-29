#include "benchrand.h"

#include <vector>
#include <float.h>

#include "ctk/utils/filesys/filesystem.h"

#include "benchlib/benchmarkevaluation.h"
#include "benchlib/benchmarkprogram.h"
#include "benchlib/benchmarkengine.h"

#include "randmark.h"

//TODO: improve the management of files (no global variables)
QVector<QString> files;


class QuantityRmEval : public BenchmarkEvaluation
{
private:
    Descriptor* desc;

public:
    QuantityRmEval() : BenchmarkEvaluation(){
        desc = new QuantityDescriptor;
        desc->setRange(1, 0, 1);
    }

    void eval(QStringList args) {
        int sreg = args[0].toInt();
        SetMark reg;
        reg.Open(files[sreg]);
        Histogram h1 = desc->Calculate(reg.get(0));
        //
        int sval = args[1].toInt();
        SetMark val;
        val.Open(files[sval]);
        int smp = args[2].toInt();
        Histogram h2 = desc->Calculate(val.get(smp));
        //
        int thresh = args[3].toInt();
        //
        m_time.start();
        int d = h1.Distance(h2);
        if (d<=thresh) m_out = "1";
        else m_out = "0";
        m_procTime = m_time.elapsed();
    }
};

float ValidationAllMarksQuantityDesc(int thresh)
{
    QString dirdb = "../../benchmark/projects/randmarks/data";
    files = createFileList(dirdb, "txt");
    //
    BenchmarkEngine engine;
    BenchmarkProgram *progQty = new StringEqualsCompProg;
    BenchmarkEvaluation* evalQty = new QuantityRmEval;
    progQty->setEvaluation(evalQty);
    engine.addProgram(progQty);
    //
    for (auto i=0; i<files.size(); i++) {
        for (auto j=0; j<files.size(); j++) {
            if (i==j) {
                //TODO: improve the control of this constant
                // (defined in other class :o)
                for (auto k=1; k<5; k++) {
                    QStringList args;
                    args << QString::number(i)
                         << QString::number(j)
                         << QString::number(k)
                         << QString::number(thresh);
                    engine.addInstance(args, "1");
                }
            }
            else {
                for (auto k=0; k<5; k++) {
                    QStringList args;
                    args << QString::number(i)
                         << QString::number(j)
                         << QString::number(k)
                         << QString::number(thresh);
                    engine.addInstance(args, "0");
                }
            }
        }
    }
    float rate = engine.ValidationRate(0);
    return rate;
}

class DistanceRmEval : public BenchmarkEvaluation
{
private:
    Descriptor* desc;

public:
    DistanceRmEval() : BenchmarkEvaluation(){
        desc = new DistanceDescriptor;
        desc->setRange(151, 0., 150.0);
    }

    void eval(QStringList args) {
        int sreg = args[0].toInt();
        SetMark reg;
        reg.Open(files[sreg]);
        Histogram h1 = desc->Calculate(reg.get(0));
        //
        int sval = args[1].toInt();
        SetMark val;
        val.Open(files[sval]);
        int smp = args[2].toInt();
        Histogram h2 = desc->Calculate(val.get(smp));
        //
        int thresh = args[3].toInt();
        //
        m_time.start();
        int d = h1.Distance(h2);
        if (d<=thresh) m_out = "1";
        else m_out = "0";
        m_procTime = m_time.elapsed();
    }
};

float ValidationAllMarksDistanceDesc(int thresh)
{
    QString dirdb = "../../benchmark/projects/randmarks/data";
    files = createFileList(dirdb, "txt");
    //
    BenchmarkEngine engine;
    BenchmarkProgram *progQty = new StringEqualsCompProg;
    BenchmarkEvaluation* evalQty = new DistanceRmEval;
    progQty->setEvaluation(evalQty);
    engine.addProgram(progQty);
    //
    for (auto i=0; i<files.size(); i++) {
        for (auto j=0; j<files.size(); j++) {
            if (i==j) {
                for (auto k=1; k<5; k++) {
                    QStringList args;
                    args << QString::number(i)
                         << QString::number(j)
                         << QString::number(k)
                         << QString::number(thresh);
                    engine.addInstance(args, "1");
                }
            }
            else {
                for (auto k=0; k<5; k++) {
                    QStringList args;
                    args << QString::number(i)
                         << QString::number(j)
                         << QString::number(k)
                         << QString::number(thresh);
                    engine.addInstance(args, "0");
                }
            }
        }
    }
    float rate = engine.ValidationRate(0);
    return rate;
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
//    CrossValidationQuantity();
    CrossValidationDistance();
}
