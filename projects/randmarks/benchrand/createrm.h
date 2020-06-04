#ifndef CREATERM_H
#define CREATERM_H

#include <vector>

#include <QString>

#include "randmark.h"

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
    void Create(int dbSize, int setSize);

private:
    SetMark createMark(int setSize);
};

void createRandomMarkDb();

void createSetupFile();

#endif // CREATERM_H
