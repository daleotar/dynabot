#include "QDynGeneric.h"

QDynGeneric::QDynGeneric()
{
}

QString QDynGeneric::double2meters(double value)
{
    return QString::number(value) + " m";
}

QString QDynGeneric::double2degree(double value)
{
    return QString::number(value) + " °";
}

QString QDynGeneric::double2linspeed(double value)
{
    return QString::number(value) + " m/s";
}

QString QDynGeneric::double2angspeed(double value)
{
    return QString::number(value) + " °/s";
}

QString QDynGeneric::double2kilogram(double value)
{
    return QString::number(value) + " kg";
}

double QDynGeneric::meters2double(QString value)
{
    value = value.simplified();
    value.chop(1);
    return value.toDouble();
}

double QDynGeneric::degree2double(QString value)
{
    value = value.simplified();
    value.chop(1);
    return value.toDouble();
}

double QDynGeneric::kilogram2double(QString value)
{
    value = value.simplified();
    value.chop(2);
    return value.toDouble();
}

QDynMatrix* QDynGeneric::matrixFromString(QString matStr)
{
    matStr.remove(0,1);
    matStr.chop(1);
    QList<QString> strRows;
    QList<QString> strColsActRow;
    strRows = matStr.split(";");
    strColsActRow = strRows[0].split(" ");

    QDynMatrix *R = new QDynMatrix(strRows.length(),strColsActRow.length());
    strColsActRow.clear();

    for(int i=0; i<strRows.length(); i++)
    {
        strColsActRow = strRows[i].split(" ");

        for(int j=0; j<R->cols; j++)
        {
            R->data[i][j] = strColsActRow[j].toDouble();
        }

        strColsActRow.clear();
    }

    return R;
}
