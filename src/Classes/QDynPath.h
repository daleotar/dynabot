#ifndef QDYNPATH_H
#define QDYNPATH_H

#include <QString>
#include <QFile>
#include <QFileInfo>
#include <QTreeWidget>
#include <QVariant>
#include "math.h"

typedef struct QDynPathPoint
{
    double pos[3];
}
QDynPathPoint;

class QDynPath
{
public:
    QDynPath(QString filename);
    QDynPath(double xIni,double yIni, double zIni, double xFin, double yFin, double zFin, int n);
    ~QDynPath();

    void setProp(int prop, QVariant value);

    int nPoints;
    bool visible;
    double totalDistance;
    QDynPathPoint *points;
    QString name;

};

#endif // QDYNPATH_H
