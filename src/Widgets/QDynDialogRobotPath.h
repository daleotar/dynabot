#ifndef QDYNDIALOGROBOTPATH_H
#define QDYNDIALOGROBOTPATH_H

#include "ui_QDynDialogRobotPath.h"
#include <QDialog>
#include <Classes/QDynRobot.h>
#include <Classes/QDynPath.h>

class QDynDialogRobotPath : public QDialog, private Ui::QDynDialogRobotPath
{
    Q_OBJECT

public:
    explicit QDynDialogRobotPath(QWidget *parent = 0);
    ~QDynDialogRobotPath();
    int robotID;

signals:
    void addRobotPath(int robotIndex, int pathNumber, int linkNumber, double approachSpeed, double speed);

public slots:
    void showDialog(QDynRobot *& Robot, int robotIndex, QList<QDynPath*> &pathList);

private slots:
    void on_ok_clicked();
    void on_cancel_clicked();
};

#endif // QDYNDIALOGROBOTPATH_H
