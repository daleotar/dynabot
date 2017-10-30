#include "QDynRobotPath.h"

QDynRobotPath::QDynRobotPath(int nLinks, QDynPath *trajectory, int link, double appSpeed, double velocity)
{
    qIni = new double[nLinks];
    rIni = new double[6];
    path = trajectory;
    approachSpeed = appSpeed;
    speed = velocity;
    linkID = link+1;
}

QDynRobotPath::~QDynRobotPath()
{
    delete [] qIni;
}
