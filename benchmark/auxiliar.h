#ifndef AUXILIAR_H
#define AUXILIAR_H

#include <QString>

#include "ctk/ctknumericmatrix.h"

bool CompareStringEquals(QString str1, QString str2);

void saveCsvFile(ctk::NumericMatrix &mat, QString filename);

#endif // AUXILIAR_H
