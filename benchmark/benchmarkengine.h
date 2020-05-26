#ifndef BENCHMARKENGINE_H
#define BENCHMARKENGINE_H

#include <QtCore/QtCore>
#include <QObject>
#include <QProcess>
#include <QString>
#include <QStringList>
#include <QTime>

class BenchmarkProgram : public QObject
{
    Q_OBJECT

public:
    BenchmarkProgram(QObject *par = nullptr);

    void clear();
    void read(QString filename);
    void run();
    void showReport();

public slots:
    void finished();
    void readProcessOutput();

private:
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

    void read(QString &filename);

    QString executable();
    QStringList parametersList();

private:
    QString m_exec;
    QStringList m_params;
};

#endif // BENCHMARKENGINE_H
