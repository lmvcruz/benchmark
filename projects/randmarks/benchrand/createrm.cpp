#include "createrm.h"

#include <QDebug>
#include <QVector>
#include <QString>
#include <QFileInfo>

#include "ctk/utils/filesys/filesystem.h"

MarkDB::MarkDB(){}

int MarkDB::size(){return m_db.size();}

void MarkDB::addSetMark(SetMark &m){m_db.push_back(m);}

SetMark &MarkDB::get(int i){return m_db[i];}

void MarkDB::Open(QString dirdb) {
    QVector<QString> files = createFileList(dirdb, "txt");
    m_db.resize(files.size());
    for (int i=0; i<files.size(); i++) {
        m_db[i].Open(files[i]);
    }
}

void MarkDB::Save(QString dirdb){
    checkAndCreateDirectory(dirdb);
    int dsize = m_db.size();
    for (auto i=0; i<dsize; i++) {
        QString mfilename = dirdb + "/" + QString::number(i).rightJustified(3, '0') + ".txt";
        m_db[i].Save(mfilename);
    }
}

void MarkDB::Create(int dbSize, int setSize) {
    for (auto i=0; i<dbSize; i++) {
        SetMark set = createMark(setSize);
        addSetMark(set);
    }
}

SetMark MarkDB::createMark(int setSize)
{
    SetMark set;
    SampleMark m;
    m.createUniformSampleMark(5 + (rand() % 20), 0.0, 100.0, 0.0, 100.0);
    set.addMark(m);
    for (auto i=1; i<setSize; i++) {
        SampleMark nm = m;
        nm.addRandomTranslationNoise(0.3, 2.0);
        float dr = static_cast<double>((rand() % 5)-2)*0.1;
        nm.addDeletionNoise(dr);
        float ir = static_cast<double>((rand() % 5)-2)*0.1;
        nm.addInsertionNoise(ir, 0.0, 100.0, 0.0, 100.0);
        set.addMark(nm);
    }
    return set;
}

void createRandomMarkDb()
{
    MarkDB db;
    db.Create(50, 5);
    db.Save("../../benchmark/projects/randmarks/data");
}

void createSetupFile()
{
    QString dirdb = "../../benchmark/projects/randmarks/data";
    QVector<QString> files = createFileList(dirdb, "txt");
    //
    QString filename = "../../benchmark/projects/randmarks/setup/full.txt";
    QFile file(filename);
    if(file.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        QTextStream out(&file);
        out << "{\n";
        out << "\t\"programs\": [\n";
        out << "\t\t\"../quantity/quantity\"\n";
        out << "\t],\n";
        out << "\t\"comparison\": \"STRING_EQUALS\",\n";
        out << "\t\"inputs\": [\n";
        QVector<QString> outputs;
        for (auto i=0; i<files.size(); i++) {
            QFileInfo reg(files[i]);
            for (auto j=0; j<files.size(); j++) {
                for (auto k=0; k<5; k++) {
                    if ((i==j) && (k==0)) continue;
                    QFileInfo val(files[j]);
                    QString inp = dirdb +" "+  reg.fileName() +" "+
                            val.fileName() +" "+ QString::number(k) +" "+ "1";
                    if((i==files.size()-1)&&(j==files.size()-1)&&(k==4)) {
                        out << "\t\t\"" << inp << "\"\n";
                    }
                    else {
                        out << "\t\t\"" << inp << "\",\n";
                    }
                    //
                    QString valout = (i==j ? "1" : "0");
                    outputs.push_back(valout);
                }
            }
        }
        out << "\t],\n";
        out << "\t\"output\": [\n\t\t";
        for (auto i=0; i<outputs.size()-1; i++) {
            out << "\"" << outputs[i] << "\", ";
        }
        out << "\"" << outputs.back() << "\"\n";
        out << "\t]\n";
        out << "}";
    }
    file.close();
}
