#include "randmark.h"

#include <iostream>

#include <QFile>
#include <QTextStream>
#include <QString>

#include "ctk/utils/filesys/filesystem.h"


//
// SetMark
//

SetMark::SetMark()
{

}

int SetMark::size()
{
    return m_marks.size();
}

void SetMark::addMark(SampleMark &m)
{
    m_marks.push_back(m);
    m_hists.push_back(Histogram());
}

SampleMark &SetMark::get(int idx)
{
    return m_marks[idx];
}

void SetMark::setHistogram(int idx, const Histogram &h)
{
    m_hists[idx] = h;
}

Histogram &SetMark::getHistogram(int idx)
{
    return m_hists[idx];
}

void SetMark::Open(QString filename)
{
    QFile file(filename);
    if(file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        QTextStream in(&file);
        m_marks.clear();
        int ssize;
        in >> ssize;
        for (int i=0; i<ssize; i++) {
            SampleMark m;
            std::vector<ctk::PointD> &data = m.get_data();
            int dsize;
            in >> dsize;
            data.resize(dsize);
            double x, y;
            for (auto j=0; j<dsize; j++) {
                in >> x >> y;
                data[j].set(x,y);
            }
            addMark(m);
        }
    }
    file.close();
}

void SetMark::Save(QString filename)
{
    QFile file(filename);
    if(file.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        QTextStream out(&file);
        int ssize = m_marks.size();
        out << ssize << "\n";
        for (int i=0; i<ssize; i++) {
            std::vector<ctk::PointD> &data = m_marks[i].get_data();
            int dsize = data.size();
            out << dsize << "\n";
            for (auto j=0; j<dsize; j++) {
                out << data[j].getX() << " " << data[j].getY() << "\n";
            }
        }
    }
    file.close();
}

void SetMark::Show()
{
    std::cout << "SetMark (" << m_marks.size() << ")" << std::endl;
    for (auto i=0; i<m_marks.size(); i++) {
        std::vector<ctk::PointD> &data = m_marks[i].get_data();
        int dsize = data.size();
        std::cout << "Mark: " << i << std::endl;
        for (auto j=0; j<dsize; j++) {
            std::cout << data[j].getX() << " " << data[j].getY() << std::endl;
        }
        std::cout << std::endl;
    }
    std::cout << "  --------  " << std::endl << std::endl;
}

//
// MarkDB
//

MarkDB::MarkDB()
{

}

int MarkDB::size()
{
    return m_db.size();
}

void MarkDB::addSetMark(SetMark &m)
{
    m_db.push_back(m);
}

SetMark &MarkDB::get(int i)
{
    return m_db[i];
}

void MarkDB::Open(QString dirdb)
{
    QVector<QString> files = createFileList(dirdb, "txt");
//    std::cout << dirdb.toStdString() << " " << files.size() << std::endl;
    m_db.resize(files.size());
    for (int i=0; i<files.size(); i++) {
//        std::cout << files[i].toStdString() << std::endl;
        m_db[i].Open(files[i]);
    }
}

void MarkDB::Save(QString dirdb)
{
    checkAndCreateDirectory(dirdb);
    int dsize = m_db.size();
    for (auto i=0; i<dsize; i++) {
        QString mfilename = dirdb + "/" + QString::number(i).rightJustified(3, '0') + ".txt";
        m_db[i].Save(mfilename);
    }
}

void MarkDB::Show()
{
    std::cout << "MarkDB (" << m_db.size() << ")" << std::endl;
    for (auto i=0; i<m_db.size(); i++) {
        m_db[i].Show();
    }
    std::cout << "==========" << std::endl;
}

void MarkDB::CreateDescriptor(Descriptor *desc)
{
//    std::cout << "Creating Descriptors" << std::endl;
    for (auto i=0; i<m_db.size(); i++) {
        for (auto j=0; j<m_db[i].size(); j++) {
            SampleMark& m = m_db[i].get(j);
            Histogram h = desc->Calculate(m);
            m_db[i].setHistogram(j, h);
        }
    }
}

void MarkDB::Compare(int thresh, bool show)
{
    if(show) std::cout << "Comparing Descriptors" << std::endl;
    int tp = 0;
    int fp = 0;
    int tn = 0;
    int fn = 0;
    for (auto i=0; i<m_db.size(); i++) {
        if(show)std::cout << "Mark: " << i << std::endl;
        SetMark& set1 = m_db[i];
        Histogram& h1 = set1.getHistogram(0);
        for (auto j=0; j<m_db.size(); j++) {
            SetMark& set2 = m_db[j];
            if (i==j) {
                for (auto k=1; k<set2.size(); k++) {
                    Histogram& h2 = set2.getHistogram(k);
                    int d = h1.Distance(h2);
                    if(show) {
                        std::cout << i << " " << j << " " << k << " ";
                        std::cout << d << " " << h1.get_data()[0] << " " ;
                        std::cout << h2.get_data()[0] << " " << thresh << std::endl;
                    }
                    if (d<=thresh) tp++;
                    else fp++;
                }
            }
            else {
                for (auto k=0; k<set2.size(); k++) {
                    Histogram& h2 = set2.getHistogram(k);
                    int d = h1.Distance(h2);
                    if(show) {
                        std::cout << i << " " << j << " " << k << " ";
                        std::cout << d << " " << h1.get_data()[0] << " " ;
                        std::cout << h2.get_data()[0] << " " << thresh << std::endl;
                    }
                    if (d<=thresh) fp++;
                    else tn++;
                }
            }
        }
    }
//    std::cout << "True Positives: " << tp << std::endl;
//    std::cout << "True Negatives: " << tn << std::endl;
//    std::cout << "False Positives: " << fp << std::endl;
//    std::cout << "False Negatives: " << fn << std::endl;
    std::cout << tp << " " << tn << " " << fp << " " << fn << std::endl;
}
