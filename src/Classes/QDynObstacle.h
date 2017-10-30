#ifndef QDYNOBSTACLE_H
#define QDYNOBSTACLE_H

#include <QString>
#include <Classes/QDynMesh.h>
#include <Classes/QDynMath.h>
#include <QVariant>

class QDynObstacle
{
public:

    enum QDynLocRotProps{PropName,PropX,PropY,PropZ,PropRotX,PropRotY,PropRotZ};

    QDynObstacle(QString filename);
    ~QDynObstacle();

    void setProperties(QString name, double tx, double ty, double tz, double rx, double ry, double rz);
    void setProperties(QDynLocRotProps propertie, QVariant value);

    QString name;
    QDynMesh *mesh;

    float rotX;
    float rotY;
    float rotZ;

    double R[3][3];
    double T[3];
    double glMat[16];

    bool isColliding;
};

#endif // QDYNOBSTACLE_H
