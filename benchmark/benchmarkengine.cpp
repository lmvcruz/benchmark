#include "benchmarkengine.h"

#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QProcess>
#include <QDebug>

//#include "benchmarklib/benchmarklib.h"
#include "ctk/utils/filesys/filesystem.h"

BenchmarkProgram::BenchmarkProgram(QObject *par)
    : QObject(par)
{
    QObject::connect(&m_process, SIGNAL(finished(int,QProcess::ExitStatus)),
                     this, SLOT(finished()));
    QObject::connect(&m_process, SIGNAL(readyReadStandardOutput()),
                     this, SLOT(readProcessOutput()));
}

BenchmarkProgram::BenchmarkProgram(const BenchmarkProgram &that)
    : QObject(that.parent())
{
    QObject::connect(&m_process, SIGNAL(finished(int,QProcess::ExitStatus)),
                     this, SLOT(finished()));
    QObject::connect(&m_process, SIGNAL(readyReadStandardOutput()),
                     this, SLOT(readProcessOutput()));
    //
    m_exec = that.m_exec;
    m_args = that.m_args;
    m_val = that.m_val;
//    m_process = that.m_process;
    m_time = that.m_time;
    m_procTime = that.m_procTime;
    m_out = that.m_out;
}

BenchmarkProgram &BenchmarkProgram::operator=(const BenchmarkProgram &that)
{
    setParent(that.parent());
    m_exec = that.m_exec;
    m_args = that.m_args;
    m_val = that.m_val;
//    m_process = that.m_process;
    m_time = that.m_time;
    m_procTime = that.m_procTime;
    m_out = that.m_out;
    return *this;
}

void BenchmarkProgram::setExecutable(QString ex)
{
    m_exec = ex;
}

void BenchmarkProgram::setArgs(QStringList args)
{
    m_args = args;
}

void BenchmarkProgram::setValidation(QString val)
{
    m_val = val;
}

QString BenchmarkProgram::output()
{
    return m_out;
}

QString BenchmarkProgram::expectedOutput()
{
    return m_val;
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
    if (checkFile(m_exec)) {
        m_time.start();
        m_process.start(m_exec, m_args, QIODevice::ReadWrite);
        m_process.waitForFinished();
    }
    else {
        qDebug() << "File does not exists:" << m_exec;
    }
}

bool BenchmarkProgram::validate()
{
    return (m_out==m_val);
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

void BenchmarkEngine::read(QString filename)
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
    QJsonArray inputsJsonArray;
    QStringList args;
    QString val;
    if ( json.contains("programs") ) {
        inputsJsonArray = json["programs"].toArray();
    }
    else {
        qDebug() << "Invalid JSON!!! Missing <programs> attribute.";
    }
    //
    if ( json.contains("args") ) {
        QJsonArray argJson = json["args"].toArray();
        for (int i=0; i<argJson.size(); i++) {
            args.push_back( argJson[i].toString() );
        }
    }
    else {
        qDebug() << "Invalid JSON!!! Missing <args> attribute.";
    }
    //
    if ( json.contains("validation") ) {
        val = json["validation"].toString();
    }
    else {
        qDebug() << "Invalid JSON!!! Missing <args> attribute.";
    }
    //
    m_programs.clear();
    m_programs.resize(inputsJsonArray.size());
    for (int i=0; i<inputsJsonArray.size(); i++) {
        BenchmarkProgram &p = m_programs[i];
        p.setExecutable(inputsJsonArray[i].toString());
        p.setArgs(args);
        p.setValidation(val);
    }
}

void BenchmarkEngine::run()
{
    for (auto i=0; i<m_programs.size(); i++) {
        m_programs[i].run();
        if(m_programs[i].validate()) qDebug() << "Valid!" << m_programs[i].output() << m_programs[i].expectedOutput();
        else qDebug() << "Not Valid!" << m_programs[i].output() << m_programs[i].expectedOutput();
    }
}
