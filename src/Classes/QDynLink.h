#ifndef QDYNLINK_H
#define QDYNLINK_H

#include <QString>
#include <Classes/QDynMath.h>
#include <Classes/QDynMesh.h>
#include <Classes/QDynGeneric.h>

class QDynLink
{
public:

    enum QDynJointType{Revolute, Prismatic};

    QDynLink(QString meshfile, QString linkName);
    ~QDynLink();

    // Link Properties Functions
    void computeInertiaAndCenterOfMass();

    // Matrices Functions
    void updateDH();
    void updateP();
    void setBaseFrame(double T[4][4], bool secondaryMatrices = false);
    void updateglMatrices();

    // Debugging Functions
    void printLinkFeatures();


    QDynMesh *mesh;

    int parentId;
    int id;

    QString name;

    QDynJointType jointType;
    double qMin;
    double qMax;

    double a;
    double alpha;
    double d;
    double theta;
    double plusTheta;

    double defaultD;
    double defaultTheta;

    double roll, pitch, yaw;

    double T0a[4][4];
    double T0b[4][4];
    double Tab[4][4];
    double Tbn[4][4];
    QDynMatrix *R0a, *R0b, *Rab, *Ra0, *Rb0, *Rba;

    QDynMatrix *I, *s, *p;
    double mass, density;

    double RLink[3][3];
    double PLink[3];

    double glMat[16];

    QDynMatrix *Asys;
    QDynMatrix *Bsys;
    QDynMatrix *Csys;
    QDynMatrix *Dsys;

    bool isColliding;

};

#endif // QDYNLINK_H
