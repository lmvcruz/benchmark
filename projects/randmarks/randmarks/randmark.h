#ifndef RANDMARK_H
#define RANDMARK_H

#include <QString>

#include <vector>

#include "mark.h"
#include "descriptor.h"

class SetMark {
private:
    std::vector<SampleMark> m_marks;
    std::vector<Histogram> m_hists;

public:
    SetMark();

    int size();

    void addMark(SampleMark &m);
    SampleMark &get(int idx);

    void setHistogram(int idx, const Histogram &h);
    Histogram &getHistogram(int idx);

    void Open(QString filename);
    void Save(QString filename);
    void Show();
};

class MarkDB {
private:
    std::vector<SetMark> m_db;

public:
    MarkDB();

    int size();

    void addSetMark(SetMark &m);
    SetMark &get(int i);

    void Open(QString dirdb);
    void Save(QString dirdb);
    void Show();

    void CreateDescriptor(Descriptor *desc);
    void Compare(int thresh);
};



#endif // RANDMARK_H
