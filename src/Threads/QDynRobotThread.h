#ifndef QDYNROBOTTHREAD_H
#define QDYNROBOTTHREAD_H

#include <QThread>
#include <Classes/QDynRobot.h>

class QDynRobotThread : public QThread
{
    Q_OBJECT

public:

    QDynRobotThread(QObject *parent);
    void setRobot(QDynRobot *Bot);
    void setProcess(int proc);
    void run();
    void stopSimulation();
    void pauseSimulation();
    void resumeSimulation();

    QDynRobot *Robot;
    int process;
    int processPercentage;
    bool stopped;
    bool paused;

signals:
//    void ikSolved();
    void processUpdated(int procType, int percentage);

public slots:
    void processState(int procType, int percentage);
};

#endif // QDYNROBOTIKTHREAD_H
