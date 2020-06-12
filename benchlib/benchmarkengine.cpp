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

BenchmarkEngine::~BenchmarkEngine()
{
//    m_inputs.clear();
//    m_stringsexpected.clear();
    for (auto &v: m_programs) delete v;
    m_programs.clear();
}

void BenchmarkEngine::Read(QString filename)
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
    //TODO: improve the program initialization by JSON
    // define a better way to cuntruct it (comparison att)
    if ( json.contains("programs") ) {
        inputsJsonArray = json["programs"].toArray();
        m_programs.clear();
        m_programs.resize(inputsJsonArray.size());
    }
    // Initialize all programs and their evaluation
    if ( json.contains("comparison") ) {
        QString comp = json["comparison"].toString();
        if (comp=="STRING_EQUALS") {
            for (int i=0; i<inputsJsonArray.size(); i++) {
                QString exec = inputsJsonArray[i].toString();
                BenchmarkEvaluation* eval = new SystemProcessEvaluation(exec);
                m_programs[i] = new StringEqualsCompProg;
                m_programs[i]->set_evaluation(eval);
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
    if ( json.contains("inputs") && json.contains("output")) {
        QJsonArray inputsJson = json["inputs"].toArray();
        QJsonArray outputJson = json["output"].toArray();
        //TODO: improve it (use exceptions)
        assert(inputsJson.size()==outputJson.size());
        for (int i=0; i<inputsJson.size(); i++) {
            QString arg = inputsJson[i].toString();
            QString out = outputJson[i].toString();
            for (int j=0; j<m_programs.size(); j++) {
                m_programs[j]->add_instance(arg, out);
            }
        }
    }
    else if (json.contains("inputs")) {
        QJsonArray inputsJson = json["inputs"].toArray();
        for (int i=0; i<inputsJson.size(); i++) {
            QString arg = inputsJson[i].toString();
            for (int j=0; j<m_programs.size(); j++) {
                m_programs[j]->add_instance(arg, "");
            }
        }
    }
    else {
        //TODO: throw exception????
        qDebug() << "Invalid JSON!!! Missing <args> attribute.";
    }
}

void BenchmarkEngine::add_program(BenchmarkProgram *p)
{
    m_programs.push_back(p);
}

void BenchmarkEngine::add_arg(QString in)
{
//    QStringList arg = {in};
//    m_inputs.push_back(arg);
    for (auto i=0; i<m_programs.size(); i++) {
        m_programs[i]->add_instance(in, "");
    }
}

void BenchmarkEngine::add_arg(QStringList in)
{
//    m_inputs.push_back(in);
    for (auto i=0; i<m_programs.size(); i++) {
        m_programs[i]->add_instance(in, "");
    }
}

void BenchmarkEngine::add_args(QVector<QString> args)
{
    for (auto &a: args) add_arg(a);
}

void BenchmarkEngine::add_instance(QString in, QString out)
{
//    add_arg(in);
//    m_stringsexpected.push_back(out);
    for (auto i=0; i<m_programs.size(); i++) {
        m_programs[i]->add_instance(in, out);
    }
}

void BenchmarkEngine::add_instance(QStringList in, QString out)
{
//    add_arg(in);
//    m_stringsexpected.push_back(out);
    for (auto i=0; i<m_programs.size(); i++) {
        m_programs[i]->add_instance(in, out);
    }
}

void BenchmarkEngine::add_instances(QVector<QString> ins, QVector<QString> outs)
{
    //TODO: replace to an exception
    assert(ins.size()==outs.size());
    for (auto i=0; i<ins.size(); i++) {
        add_instance(ins[i], outs[i]);
    }
}

float BenchmarkEngine::ValidationRate(int idx)
{
    return m_programs[idx]->ValidationRate();
}

void BenchmarkEngine::ValidateAll()
{
//    for (auto i=0; i<m_programs.size(); i++) {
//        for (auto j=0; j<m_inputs.size(); j++) {
//            if (m_programs[i]->Validate(m_inputs[j], m_stringsexpected[j])) {
//                qDebug() << "Arg:" << i << j << "is VALID!!!";
//            }
//            else {
//                qDebug() << "Arg:" << i << j << "is NOT valid.";
//            }
//        }
//    }
    for (auto i=0; i<m_programs.size(); i++) {
        BenchmarkProgram *prog = m_programs[i];
        int cqty = prog->CasesQuantities();
        for (auto j=0; j<cqty; j++) {
            if (prog->ValidateCase(j)) {
                qDebug() << "Arg:" << i << j << "is VALID!!!";
            }
            else {
                qDebug() << "Arg:" << i << j << "is NOT valid.";
            }
        }
    }
}

void BenchmarkEngine::EvalPerformance(QString csvname)
{
//    ctk::NumericMatrix timeMatrix;
//    timeMatrix.Create(m_programs.size(), m_inputs.size());
//    for (auto i=0; i<m_programs.size(); i++) {
//        BenchmarkProgram *prog = m_programs[i];
//        for (auto j=0; j<m_inputs.size(); j++) {
//            timeMatrix.set(i, j, prog->EvalCasePerformance(j));
//        }
//    }
//    saveCsvFile(timeMatrix, csvname);
    ctk::NumericMatrix timeMatrix;
    int maxCases = 0;
    for (auto i=0; i<m_programs.size(); i++) {
        BenchmarkProgram *prog = m_programs[i];
        maxCases = std::max(maxCases, prog->CasesQuantities());
    }
    timeMatrix.Create(m_programs.size(), maxCases);
    timeMatrix.Fill(0.0);
    for (auto i=0; i<m_programs.size(); i++) {
        BenchmarkProgram *prog = m_programs[i];
        int cqty = prog->CasesQuantities();
        for (auto j=0; j<cqty; j++) {
            timeMatrix.set(i, j, prog->EvalCasePerformance(j));
        }
    }
    saveCsvFile(timeMatrix, csvname);
}
