#ifndef QDYNMESH_H
#define QDYNMESH_H

#include <QString>
#include <QFile>
#include <QFileInfo>
#include <math.h>
#include <QDebug>
#include <RAPID/RAPID.H>

typedef struct QDynMeshVertex
{
    float x;
    float y;
    float z;
}
QDynMeshVertex;


typedef struct QDynMeshFace
{
    int material;
    double normal[3];
    double offset;
}
QDynMeshFace;

typedef struct QDynMeshMaterial
{
    float r;
    float g;
    float b;
    float a;
    QString name;
}
QDynMeshMaterial;


class QDynMesh
{
public:

    int nVert;
    int nFace;
    int nMate;

    double xMin,xMax,yMin,yMax,zMin,zMax;

    QDynMeshFace        *faces;
    QDynMeshMaterial    *materials;

    RAPID_model         *triangles;

    QDynMesh(QString filename);
    ~QDynMesh();

private:
    QDynMeshVertex      *vertices;
    void computeFaceNormals();
};

#endif // QDYNMESH_H
