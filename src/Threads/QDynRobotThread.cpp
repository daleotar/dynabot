#include "QDynRobotThread.h"

QDynRobotThread::QDynRobotThread(QObject *parent) : QThread(parent)
{
    stopped = false;
}

void QDynRobotThread::setRobot(QDynRobot *Bot)
{
    Robot = Bot;
    connect(Robot,SIGNAL(processState(int,int)),this,SLOT(processState(int,int)));
}

void QDynRobotThread::setProcess(int proc)
{
    process = proc;
}

void QDynRobotThread::run()
{
    stopped = false;
    paused = false;

    switch(process)
    {
        case 0:
        break;
        case 1: // Inverse Kinematics

            if(!Robot->ikSolved)
            {
                Robot->calculateFullPath();

                if(stopped)
                return;

                Robot->calculateInverseKinematics();
                Robot->calculateRobotDynamics();
//                Robot->calculateDynamicResponses();

            }
            else
            {
                processPercentage = 100;
                emit processUpdated(1,100);
            }
        break;
        case 2: // Simulation
            Robot->actSimState = 0;
            while(Robot->actSimState < Robot->nPoints)
            {
                if(stopped)
                return;

                if(!paused)
                {
                    Robot->simulationStep();
                    msleep((int) floor((Robot->tRef[Robot->actSimState - 1] * 1000) + 0.5));
                }
                else
                {
                    msleep(15);
                }
            }
        break;
    }
}

void QDynRobotThread::stopSimulation()
{
    stopped = true;
    Robot->stopCalculation();
}

void QDynRobotThread::pauseSimulation()
{
    paused = true;
}

void QDynRobotThread::resumeSimulation()
{
    paused = false;
}

void QDynRobotThread::processState(int procType, int percentage)
{
    processPercentage = percentage;
    emit processUpdated(procType,percentage);
}
