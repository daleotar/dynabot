#ifndef QDYNROBOT_H
#define QDYNROBOT_H

#include <Classes/QDynLink.h>
#include <Classes/QDynRobotPath.h>
#include <Classes/QDynGeneric.h>
#include <QVariant>
#include <QTimer>
#include <qdom.h>

class QDynRobot : public QObject
{
    Q_OBJECT

public:

    enum QDynDerivType{Second,Fourth};

    QDynRobot(QString filename, QObject *parent = 0);
    ~QDynRobot();

    void updateMatricesFrom(int link, bool secondaryMatrices = false, bool refreshRobotBounds = false);
    void setQ(double q, int link, bool secondaryMatrices = false, bool refreshRobotBounds = false);
    void setProp(int prop, QVariant value);
    void resetRobot();
    void addPath(QDynPath *path, int link, double appSpeed, double speed);
    void deletePath(int index);
    void calculateFullPath();
    void calculateInverseKinematics();
    void calculateRobotDynamics();
    void calculateDynamicResponses();
    void findMinimumError(QDynLink *LinkA, QDynLink *LinkB, double xf, double yf, double zf, double &qA, double &qB);
    void setInitialPathConfig(bool resetIK = false);
    void refreshBounds();


    double x;
    double y;
    double z;

    double rotX;
    double rotY;
    double rotZ;

    double T[4][4];
    double glMat[16];

    double xMin,xMax,yMin,yMax,zMin,zMax;

    double         *xRef;
    double         *yRef;
    double         *zRef;

    QList<double*>  qRef;
    QList<double*>  qSim;
    QList<double*>  qDot;
    QList<double*>  qDotDot;
    QList<double*>  qTorque;

    double         *tRef;
    double         *tAcu;

    int             nPoints;
    int             actSimState;
    bool            ikSolved;

    QString         name;
    int             nLinks;
    int             nPaths;
    int             realLinks;
    bool            stopped;
    int             selectedLink;
    bool            isSelected;

    QList<QDynLink*> Links;
    QList<QDynRobotPath*> Paths;

signals:
    void processState(int procType, int percentage);

public slots:
    void simulationStep();
    void stopCalculation();

};

#endif // QDYNROBOT_H
