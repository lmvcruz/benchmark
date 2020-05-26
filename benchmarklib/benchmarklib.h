#ifndef BENCHMARKLIB_H
#define BENCHMARKLIB_H

#include <vector>
#include <QString>

void pwd(QString path);
void ls(QString path);
bool fileExists(QString filename);

void generateRandVec(std::vector<int> &vec, unsigned int size,
                     int minv, int maxv, unsigned int seed=0);


std::vector<int> string2vecint(const QString &str);

#endif // BENCHMARKLIB_H
