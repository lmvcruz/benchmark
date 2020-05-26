#ifndef BENCHMARKENGINE_H
#define BENCHMARKENGINE_H

#include <QtCore/QtCore>
#include <QObject>
#include <QProcess>
#include <QString>
#include <QStringList>
#include <QTime>

#include "ctk/ctknumericmatrix.h"

class BenchmarkProgram : public QObject
{
    Q_OBJECT

public:
    BenchmarkProgram(QObject *par = nullptr);
    BenchmarkProgram(const BenchmarkProgram &that);

    BenchmarkProgram & operator=(const BenchmarkProgram &that);

    void setExecutable(QString ex);
    void setArgs(QString args);
    void setValidation(QString val);

    QString output();
    QString expectedOutput();
    int time();

    void clear();
    void read(QString filename);
    void run();
    bool validate();
    void showReport();

public slots:
    void finished();
    void readProcessOutput();

public:
    QString m_exec;
    QStringList m_args;
    QString m_val;

    QProcess m_process;
    QTime m_time;
    int m_procTime;
    QString m_out;
};

class BenchmarkEngine
{
public:
    BenchmarkEngine() = default;

    void read(QString filename);

    void run();

private:
    QVector<BenchmarkProgram> m_programs;
    QVector<QString> m_inputs;
    QVector<QString> m_evaluations;
    QString m_output;

    bool m_evalTime;

    bool m_stringcomp;
    QVector<QString> m_stringsexpected;

    ctk::NumericMatrix m_timeMatrix;
};

#endif // BENCHMARKENGINE_H
