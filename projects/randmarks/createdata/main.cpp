#include <iostream>
#include <vector>
#include <algorithm>

#include <QCoreApplication>
#include <QCommandLineParser>
#include <QFile>
#include <QTextStream>
#include <QString>
#include <QDebug>


#include "ctk/ctkmath.h"
#include "ctk/ctkpoint.h"
#include "ctk/utils/filesys/filesystem.h"

#include "randmark.h"

using namespace std;

class MarkDB {
private:
    std::vector<SetMark> m_db;

public:
    MarkDB(){}

    int size(){return m_db.size();}

    void addSetMark(SetMark &m){m_db.push_back(m);}
    SetMark &get(int i){return m_db[i];}

    void Open(QString dirdb) {
        QVector<QString> files = createFileList(dirdb, "txt");
        m_db.resize(files.size());
        for (int i=0; i<files.size(); i++) {
            m_db[i].Open(files[i]);
        }
    }

    void Save(QString dirdb){
        checkAndCreateDirectory(dirdb);
        int dsize = m_db.size();
        for (auto i=0; i<dsize; i++) {
            QString mfilename = dirdb + "/" + QString::number(i).rightJustified(3, '0') + ".txt";
            m_db[i].Save(mfilename);
        }
    }

    void Create(int dbSize, int setSize) {
        for (auto i=0; i<dbSize; i++) {
            SetMark set = createMark(setSize);
            addSetMark(set);
        }
    }

private:
    SetMark createMark(int setSize)
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
};


int main(int argc, char *argv[])
{
    QCoreApplication app(argc, argv);
    MarkDB db;
    db.Create(10, 5);
    db.Save("../../benchmark/projects/randmarks/data");
    //
    return 0;
}
