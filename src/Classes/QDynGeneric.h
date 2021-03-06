#ifndef QDYNGENERIC_H
#define QDYNGENERIC_H

#include <QStringList>
#include <Classes/QDynMatrix.h>

class QDynGeneric
{
public:
    QDynGeneric();

    // Generic functions
    static QString double2meters(double value);
    static QString double2degree(double value);
    static QString double2linspeed(double value);
    static QString double2angspeed(double value);
    static QString double2kilogram(double value);
    static double meters2double(QString value);
    static double degree2double(QString value);
    static double kilogram2double(QString value);
    static QDynMatrix* matrixFromString(QString matStr);
};

#endif // QDYNGENERIC_H
