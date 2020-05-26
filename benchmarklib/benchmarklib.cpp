#include "benchmarklib.h"

#include <cstdlib>

#include <QStringList>
#include <QDir>
#include <QDebug>


void pwd(QString path)
{
    QDir dir(path);
    qDebug() << dir.absolutePath();
}

void ls(QString path)
{
    QDir dir(path);
    QVector<QFileInfo> allfiles = dir.entryInfoList().toVector();
    for ( int i=0; i<allfiles.size(); i++ ) {
        qDebug() << allfiles[i].absoluteFilePath();
    }
}

bool fileExists(QString filename)
{
    return QFileInfo(filename).exists();
}


void generateRandVec(std::vector<int> &vec, unsigned int size,
                     int minv, int maxv, unsigned int seed)
{
    srand(seed);
    vec.resize(size);
    int range = maxv-minv+1;
    for (unsigned int i=0; i<size; i++) {
        vec[i] = (rand()%range) + minv;
    }
}

std::vector<int> string2vecint(const QString &str)
{
    QStringList strsplit = str.split(",");
    std::vector<int> vec;
    vec.resize(strsplit.size());
    for (unsigned i=0; i<vec.size(); i++) {
        vec[i] = strsplit[i].toInt();
    }
    return vec;
}


