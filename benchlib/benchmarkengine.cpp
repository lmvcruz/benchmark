#include "benchmarkengine.h"

#include <cstdlib>
#include <csignal>

#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QProcess>
#include <QDebug>

#include "ctk/utils/filesys/filesystem.h"

void saveCsvFile(ctk::NumericMatrix &mat, QString filename)
{
    QFile file(filename);
    if(file.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        QTextStream out(&file);
        for (auto y=0; y<mat.height(); y++) {
            for (auto x=0; x<mat.width()-1; x++) {
                out << mat.get(x,y) << ", ";
            }
            out << mat.get(mat.width()-1, y) << "\n";
        }
        file.close();
    }
}

void BenchmarkEngine::addProgram(BenchmarkProgram *p)
{
    m_programs.push_back(p);
}

void BenchmarkEngine::addArg(QString in)
{
    QStringList arg = {in};
    m_inputs.push_back(arg);
}

void BenchmarkEngine::addArg(QStringList in)
{
    m_inputs.push_back(in);
}

void BenchmarkEngine::addInstance(QString in, QString out)
{
    addArg(in);
    m_stringsexpected.push_back(out);
}

void BenchmarkEngine::addInstance(QStringList in, QString out)
{
    addArg(in);
    m_stringsexpected.push_back(out);
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
        std::raise(SIGABRT);
    }
    // Initialize all programs and their evaluation
    if ( json.contains("comparison") ) {
        m_programs.clear();
        m_programs.resize(inputsJsonArray.size());
        //
        QString comp = json["comparison"].toString();
        if (comp=="STRING_EQUALS") {
            for (int i=0; i<inputsJsonArray.size(); i++) {
                QString exec = inputsJsonArray[i].toString();
                BenchmarkEvaluation* eval = new SystemProcessEvaluation(exec);
                m_programs[i] = new StringEqualsEvaluation;
                m_programs[i]->setEvaluation(eval);
            }
        }
        else {
            qDebug() << "Invalid <comparison> attribute:" << comp;
            std::raise(SIGABRT);
        }
    }
    else {
        qDebug() << "Invalid JSON!!! Missing <comparison> attribute.";
        std::raise(SIGABRT);
    }
    //
    if ( json.contains("inputs") ) {
        QJsonArray inputsJson = json["inputs"].toArray();
        m_inputs.clear();
        for (int i=0; i<inputsJson.size(); i++) {
            QStringList arg = { inputsJson[i].toString() };
            m_inputs.push_back(arg);
        }
    }
    else {
        qDebug() << "Invalid JSON!!! Missing <args> attribute.";
    }
    //
    if ( json.contains("output") ) {
        QJsonArray outputJson = json["output"].toArray();
        m_stringsexpected.clear();
        for (int i=0; i<outputJson.size(); i++) {
            m_stringsexpected.push_back( outputJson[i].toString() );
        }
    }
}

float BenchmarkEngine::ValidationRate(int idx)
{
    int corrects = 0;
    for (auto j=0; j<m_inputs.size(); j++) {
        if (m_programs[idx]->validate(m_inputs[j], m_stringsexpected[j])) {
            corrects++;
        }
    }
    return static_cast<float>(corrects)/static_cast<float>(m_inputs.size());
}

void BenchmarkEngine::ValidateAll()
{
    for (auto i=0; i<m_programs.size(); i++) {
        for (auto j=0; j<m_inputs.size(); j++) {
            if (m_programs[i]->validate(m_inputs[j], m_stringsexpected[j])) {
                qDebug() << "Arg:" << i << j << "is VALID!!!";
            }
            else {
                qDebug() << "Arg:" << i << j << "is NOT valid.";
            }
        }
    }
}

void BenchmarkEngine::performance()
{
    ctk::NumericMatrix timeMatrix;
    timeMatrix.Create(m_programs.size(), m_inputs.size());
    for (auto i=0; i<m_programs.size(); i++) {
        BenchmarkProgram *prog = m_programs[i];
        for (auto j=0; j<m_inputs.size(); j++) {
            prog->run(m_inputs[j]);
            timeMatrix.set(i, j, prog->time());
        }
    }
    //TODO: add filename
    saveCsvFile(timeMatrix, "test.csv");
}
