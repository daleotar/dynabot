#include "QDynObstacle.h"

QDynObstacle::QDynObstacle(QString filename)
{
    mesh = new QDynMesh(filename);

    QFileInfo fileInfo(filename);
    name = fileInfo.completeBaseName();

    setProperties(name,0,0,0,0,0,0);
}

void QDynObstacle::setProperties(QString newname, double tx, double ty, double tz, double rx, double ry, double rz)
{
    if(newname != QString(""))
    name = newname;

    T[0] = tx;
    T[1] = ty;
    T[2] = tz;

    rotX = QDynMath::normalizeAngle(rx);
    rotY = QDynMath::normalizeAngle(ry);
    rotZ = QDynMath::normalizeAngle(rz);

    isColliding = false;

    QDynMath::convRxRyRz2RotM(rotX,rotY,rotZ,R);
    QDynMath::convRotTra2glMat(R,T,glMat);
}

void QDynObstacle::setProperties(QDynLocRotProps propertie, QVariant value)
{
    switch(propertie)
    {
        case PropName:
        if(value.toString()!= QString(""))
        name = value.toString();
        break;

        case PropX:
        T[0] = value.toDouble();
        break;

        case PropY:
        T[1] = value.toDouble();
        break;

        case PropZ:
        T[2] = value.toDouble();
        break;

        case PropRotX:
        rotX = QDynMath::normalizeAngle(value.toDouble());
        QDynMath::convRxRyRz2RotM(rotX,rotY,rotZ,R);
        break;

        case PropRotY:
        rotY = QDynMath::normalizeAngle(value.toDouble());
        QDynMath::convRxRyRz2RotM(rotX,rotY,rotZ,R);
        break;

        case PropRotZ:
        rotZ = QDynMath::normalizeAngle(value.toDouble());
        QDynMath::convRxRyRz2RotM(rotX,rotY,rotZ,R);
        break;

        default:
        break;
    }

    if(propertie == PropRotX || propertie == PropRotY || propertie == PropRotZ)
    {
        QDynMath::convRxRyRz2RotM(rotX,rotY,rotZ,R);
    }
    if(propertie != PropName)
    {
        QDynMath::convRotTra2glMat(R,T,glMat);
    }

    isColliding = false;
}

QDynObstacle::~QDynObstacle()
{
    delete mesh;
}
