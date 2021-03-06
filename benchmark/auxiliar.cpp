#include "auxiliar.h"

#include <QFile>
#include <QTextStream>

bool CompareStringEquals(QString str1, QString str2)
{
    return (str1==str2);
}

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
