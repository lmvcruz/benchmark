#include "benchmarkengine.h"

#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QProcess>
#include <QDebug>

#include "benchmarklib/benchmarklib.h"

BenchmarkProgram::BenchmarkProgram(QObject *par)
    : QObject(par)
{
    QObject::connect(&m_process, SIGNAL(finished(int,QProcess::ExitStatus)),
                     this, SLOT(finished()));
    QObject::connect(&m_process, SIGNAL(readyReadStandardOutput()),
                     this, SLOT(readProcessOutput()));
}

void BenchmarkProgram::clear()
{
    m_exec.clear();
    m_args.clear();
    m_val.clear();
    //
    m_procTime = 0;
    m_out.clear();
}

void BenchmarkProgram::read(QString filename)
{
    QFile readFile(filename);
    if (!readFile.open(QIODevice::ReadOnly))
    {
        qWarning("Writing Error!!!\nCouldn't open file.");
        return;
    }
    QByteArray jsonData = readFile.readAll();
    QJsonDocument readDoc(QJsonDocument::fromJson(jsonData));
    readFile.close();
    //
    QJsonObject json = readDoc.object();
    if ( json.contains("exec") ) {
        m_exec = json["exec"].toString();
    }
    if ( json.contains("args") ) {
        QJsonArray argJson = json["args"].toArray();
        m_args.clear();
        for (int i=0; i<argJson.size(); i++) {
            m_args.push_back( argJson[i].toString() );
        }
    }
    if ( json.contains("validation") ) {
        m_val = json["validation"].toString();
    }
}

void BenchmarkProgram::run()
{
    if (fileExists(m_exec)) {
        m_time.start();
        m_process.start(m_exec, m_args, QIODevice::ReadWrite);
        m_process.waitForFinished();
    }
    else {
        qDebug() << "File does not exists:" << m_exec;
    }
}

void BenchmarkProgram::showReport()
{
    qDebug() << "Process name:" << m_exec;
    qDebug() << "Process args:" << m_args;
    qDebug() << "Processing time:" << m_procTime;
    qDebug() << "Process output: "<< m_out;
    qDebug() << "Output validtion: " << (m_out==m_val);
}

void BenchmarkProgram::finished()
{
    m_procTime = m_time.elapsed();
}

void BenchmarkProgram::readProcessOutput()
{
    m_out = QString(m_process.readAllStandardOutput());
}

void BenchmarkEngine::read(QString &filename)
{
    QFile readFile(filename);
    if (!readFile.open(QIODevice::ReadOnly))
    {
        qWarning("Reading Error!!!\nCouldn't open file.");
        return;
    }
    QByteArray jsonData = readFile.readAll();
    QJsonDocument readDoc(QJsonDocument::fromJson(jsonData));
    readFile.close();
    //
    QJsonObject json = readDoc.object();
    if ( json.contains("exec") ) {}
}
