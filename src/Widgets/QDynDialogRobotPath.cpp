#include "QDynDialogRobotPath.h"

QDynDialogRobotPath::QDynDialogRobotPath(QWidget *parent) : QDialog(parent)
{
    setupUi(this);
}

QDynDialogRobotPath::~QDynDialogRobotPath()
{

}

void QDynDialogRobotPath::showDialog(QDynRobot *&Robot, int robotIndex, QList<QDynPath *> &pathList)
{
    comboPath->clear();
    for(int i=0; i<pathList.length(); i++)
    {
        comboPath->addItem(pathList[i]->name);
    }

    comboLink->clear();
    for(int i=1; i<Robot->nLinks; i++)
    {
        comboLink->addItem(Robot->Links[i]->name);
    }
    comboLink->setCurrentIndex(Robot->nLinks - 2);
    robotID = robotIndex;
    show();
}

void QDynDialogRobotPath::on_cancel_clicked()
{
    this->close();
}

void QDynDialogRobotPath::on_ok_clicked()
{
    emit addRobotPath(robotID, comboPath->currentIndex(), comboLink->currentIndex(), spinApproach->value(), spinSpeed->value());
    this->close();
}
