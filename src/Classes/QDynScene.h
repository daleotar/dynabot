#ifndef _QDYNSCENE_H
#define _QDYNSCENE_H

#include <Classes/QDynObstacle.h>
#include <Classes/QDynRobot.h>
#include <Classes/QDynPath.h>
#include <Threads/QDynRobotThread.h>
#include <QtOpenGL/QGLWidget>
#include <QtGui/QMouseEvent>
#include <QTime>
#include <QMessageBox>

class QDynScene : public QGLWidget {

    Q_OBJECT

public:

    enum QDynTypeCollision{CollideAllLinks, CollideEndEffector, CollideNone};

    QList<QDynObstacle*>        Obstacles;
    QList<QDynRobot*>           Robots;
    QList<QDynRobotThread*>   	RobotsProcesses;
    QList<QDynPath*>            Paths;

    QDynScene(QWidget *parent = NULL);
    ~QDynScene();

    // Camera functions
    void resetView();

    // Robot functions
    void addRobot(QString filename);
    void setRobotLinkQ(double q, int robot, int link, bool refreshBounds = false);
    void setRobotProp(int prop, QVariant value, int robot);
    void resetRobot(int index);
    void deleteRobot(int index);
    void addRobotPath(int robotIndex, QDynPath *path, int linkIndex, double appSpeed, double speed);
    void deleteRobotPath(int robotIndex, int pathIndex);
    void setInitialPathConfig(int robotIndex);

    // Simulation functions
    void startSimulation();
    void stopSimulation();
    void pauseSimulation();
    void resumeSimulation();

    // Obstacle functions
    void addObstacle(QString filename);
    void setObstacleProperties(QString newname, double tx, double ty, double tz, double rx, double ry, double rz, int index);
    void setObstacleProperties(QDynObstacle::QDynLocRotProps propertie, QVariant value, int index);
    void deleteObstacle(int index);

    // Path functions
    void addPath(QString filename);
    void addPath(double xIni,double yIni, double zIni, double xFin, double yFin, double zFin, int n);
    void setPathProperties(int prop, QVariant value, int index);
    void deletePath(int index);

    // Toggle functions
    void toggleBlend(bool state);
    void toggleGlobalAxis(bool state);
    void toggleLocalAxes(bool state);
    void toggleGrid(bool state);
    void toggleObjectCoordinates(bool state);

    // Collision functions
    void checkCollisions();
    void setCollisionType(QDynTypeCollision type);

    // General functions
    void resetScene();

    bool simStarted;
    bool simRunning;

private:

    QPoint lastMousePos;
    float xRot;
    float yRot;
    float zRot;

    float xPos;
    float yPos;
    float zPos;

    float angle;
    double aspect;
    double fovy;

    bool painting;

    bool enabledBlend;
    bool enabledGlobalAxis;
    bool enabledLocalAxes;
    bool enabledObjectCoordinates;
    bool enabledGrid;

    QDynTypeCollision collisionType;

    QTime fpsTime_;
    unsigned int fpsCounter_;
    QString fpsString_;
    float f_p_s_;

signals:
    void simulationStarted();
    void simulationStopped();
    void simulationPaused();
    void simulationResumed();
    void processUpdated(QString process, int percentage);

public slots:
    void robotProcessFinished();
    void robotProcessUpdated(int procType, int percentage);

protected:
    void initializeGL();
    void resizeGL(int w, int h);
    void paintGL();

    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void wheelEvent(QWheelEvent *event);

    void drawCoordinates(double x, double y, double z);
    void drawBox(double xMin, double xMax, double yMin, double yMax, double zMin, double zMax);
    void drawGrid(float size, int nbSubdivisions = 10);
    void drawMesh(QDynMesh *mesh, bool isColliding = false, int type = 0);
    void drawAxis(double length, bool opaque = true);
    void drawArrow(float length, int nbSubdivisions = 10);
};

#endif  /* _QDYNSCENE_H */
