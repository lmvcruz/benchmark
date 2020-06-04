#ifndef BENCHMARKEVALUATION_H
#define BENCHMARKEVALUATION_H


#include <QVector>
#include <QString>
#include <QObject>
#include <QProcess>
#include <QTime>

class BenchmarkEvaluation: public QObject
{
    Q_OBJECT

protected:
    QString m_out;
    QTime m_time;
    int m_procTime;

public:
    BenchmarkEvaluation(QObject *par = nullptr);
    virtual ~BenchmarkEvaluation();

    virtual QString name();

    void Run(QStringList args);
    QString output();
    int time();

    virtual void Eval(QStringList args) = 0;
};

class SystemProcessEvaluation : public BenchmarkEvaluation
{
    Q_OBJECT

private:
    QProcess m_process;
    QString m_exec;

public:
    SystemProcessEvaluation(QObject *par = nullptr);
    SystemProcessEvaluation(QString exec, QObject *par = nullptr);
    virtual ~SystemProcessEvaluation();

    QString name();

    void Eval(QStringList args);

public slots:
    void finished();
    void readProcessOutput();
};



#endif // BENCHMARKEVALUATION_H
