#include "benchmarkevaluation.h"

#include <QDebug>

#include "ctk/utils/filesys/filesystem.h"

//
// BenchmarkEvaluation Class
//
BenchmarkEvaluation::BenchmarkEvaluation(QObject *par)
    : QObject(par)
{

}

BenchmarkEvaluation::~BenchmarkEvaluation()
{

}

QString BenchmarkEvaluation::name()
{
    return "Abstract Program";
}

void BenchmarkEvaluation::Run(QStringList args)
{
    m_time.start();
    Eval(args);
}

QString BenchmarkEvaluation::output()
{
    return m_out;
}

int BenchmarkEvaluation::time()
{
    return m_procTime;
}

//
// BenchmarkEvaluation Class
//
SystemProcessEvaluation::SystemProcessEvaluation(QObject *par)
    : BenchmarkEvaluation(par)
{
    QObject::connect(&m_process, SIGNAL(finished(int,QProcess::ExitStatus)),
                     this, SLOT(finished()));
    QObject::connect(&m_process, SIGNAL(readyReadStandardOutput()),
                     this, SLOT(readProcessOutput()));
}

SystemProcessEvaluation::SystemProcessEvaluation(QString exec, QObject *par)
    : BenchmarkEvaluation(par)
{
    m_exec = exec;
    //
    QObject::connect(&m_process, SIGNAL(finished(int,QProcess::ExitStatus)),
                     this, SLOT(finished()));
    QObject::connect(&m_process, SIGNAL(readyReadStandardOutput()),
                     this, SLOT(readProcessOutput()));
}

SystemProcessEvaluation::~SystemProcessEvaluation()
{

}

QString SystemProcessEvaluation::name()
{
    return m_exec;
}

void SystemProcessEvaluation::Eval(QStringList args)
{
    if (checkFile(m_exec)) {
        m_out = "";
        m_time.start();
        m_process.start(m_exec, args, QIODevice::ReadWrite);
        m_process.waitForFinished(-1);
    }
    else {
        qDebug() << "File does not exists:" << m_exec;
    }
}

void SystemProcessEvaluation::finished()
{
    m_procTime = m_time.elapsed();
}

void SystemProcessEvaluation::readProcessOutput()
{
    m_out = QString(m_process.readAllStandardOutput());
}
