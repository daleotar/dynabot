#ifndef QDYNROBOTPATH_H
#define QDYNROBOTPATH_H

#include <Classes/QDynPath.h>

class QDynRobotPath
{
public:
    QDynRobotPath(int nLinks, QDynPath *trajectory, int link, double appSpeed, double velocity);
    ~QDynRobotPath();

    double *qIni;
    double *rIni;
    QDynPath *path;
    int linkID;
    double approachSpeed;
    double speed;
};

#endif // QDYNROBOTPATH_H
