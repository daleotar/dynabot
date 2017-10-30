#ifndef QDYNMATH_H
#define QDYNMATH_H

#include <math.h>
#include <QDebug>
#include <Classes/QDynMatrix.h>

class QDynMath
{
public:
    QDynMath();

    // Angle functions
    static double normalizeAngle(double angle);
    static double deg2Rad(double angle);
    static double rad2Deg(double angle);

    // Generic Matrix Functions
    static QDynMatrix* multMatrix(QDynMatrix *A, QDynMatrix *B);
    static QDynMatrix* addMatrix(QDynMatrix *A, QDynMatrix *B);
    static void multMatrix(QDynMatrix *A, QDynMatrix *B, QDynMatrix *R);
    static void addMatrix(QDynMatrix *A, QDynMatrix *B, QDynMatrix *R);
    static QDynMatrix* multMatScalar(QDynMatrix *M, double scalar);
    static void multMatScalar(QDynMatrix *M, double scalar, QDynMatrix *R);

    // Vector Functions
    static QDynMatrix* crossProd(QDynMatrix *V1, QDynMatrix *V2);
    static void crossProd(QDynMatrix *V1, QDynMatrix *V2, QDynMatrix *Vr);

    // Coordinate Transform Functions
    static void singleCoorTrans(double T[4][4], double P[4], double PNew[4]);

    // Matrix Copying Functions
    static void copyMatTrans(const double S[4][4], double D[4][4]);
    static void copyMatTrans(QDynMatrix *S, double D[4][4]);
    static void copyMatTrans(const double S[4][4], QDynMatrix *D);
    static void copyMatRot(const double S[3][3], double D[3][3]);
    static void copyMatRot(QDynMatrix *S, double D[3][3]);
    static void copyMatRot(const double S[3][3], QDynMatrix *D);
    static void copyVec(const double S[3], double D[3]);
    static void copyRotFromTrans(QDynMatrix *T, double R[3][3]);
    static void copyRotFromTrans(const double T[4][4], QDynMatrix *R);

    // Matrix Operations Functions
    static void multTransMat(double M1[4][4],double M2[4][4],double T[4][4]) ;
    static void multRotMat(double M1[3][3],double M2[3][3],double R[3][3]);

    // Matrix Creation Functions
    static void setTransIdentity(double T[4][4]);
    static void setIdentity(QDynMatrix *M);
    static void convRxRyRz2RotM(double rxDeg, double ryDeg, double rzDeg, double Rot[3][3], int rotOrder = 1);
    static void convDH2Trans(double a, double alphaDeg, double d, double thetaDeg, double T[4][4]);
    static void convDH2Trans(double a, double alphaDeg, double d, double thetaDeg, QDynMatrix *T);

    // Matrix Conversion Functions
    static void convRotTra2glMat(double R[3][3], double T[3], double glMat[16]);
    static void convTrans2glMat(double T[4][4], double glMat[16]);
    static void convTrans2glMat(QDynMatrix *T, double glMat[16]);
    static void convRotTra2Trans(double R[3][3], double T[3], double TT[4][4]);
    static void convRotTra2Trans(double R[3][3], double T[3], QDynMatrix *TT);
    static void convTrans2RotTra(double TT[4][4], double R[3][3], double T[3]);
    static void convTrans2RotTra(QDynMatrix *TT, double R[3][3], double T[3]);
    static void convRot2RPY(const double R[3][3],double &roll, double &pitch, double &yaw);

    // Joint pair function
    static double derFunErrRot(double TPre[4][4],double TNex[4][4],double xf, double yf, double zf, double a, double alphaDeg, double d, double thetaDeg);
    static double derFunErrPri(double TPre[4][4],double TNex[4][4],double xf, double yf, double zf, double a, double alphaDeg, double d, double thetaDeg);
    static void newtonRR(double &derErr, double &x, double &y, double TPrev[4][4], double TNext[4][4], double xf, double yf, double zf, double a1, double alpha1Deg, double d1, double theta1Deg, double a2, double alpha2Deg, double d2, double theta2Deg);
    static void newtonRP(double &derErr, double &x, double &y, double TPrev[4][4], double TNext[4][4], double xf, double yf, double zf, double a1, double alpha1Deg, double d1, double theta1Deg, double a2, double alpha2Deg, double d2, double theta2Deg);
    static void newtonPR(double &derErr, double &x, double &y, double TPrev[4][4], double TNext[4][4], double xf, double yf, double zf, double a1, double alpha1Deg, double d1, double theta1Deg, double a2, double alpha2Deg, double d2, double theta2Deg);
    static void newtonPP(double &derErr, double &x, double &y, double TPrev[4][4], double TNext[4][4], double xf, double yf, double zf, double a1, double alpha1Deg, double d1, double theta1Deg, double a2, double alpha2Deg, double d2, double theta2Deg);

    // Debugging Functions
    static void printTransMat(double T[4][4]);
    static void printMatrix(QDynMatrix *M);
};

#endif // QDYNMATH_H
