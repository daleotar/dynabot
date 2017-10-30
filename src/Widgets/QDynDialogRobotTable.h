#ifndef QDYNDIALOGROBOTTABLE_H
#define QDYNDIALOGROBOTTABLE_H

#include <QDialog>
#include <QMenu>
#include <QFileDialog>
#include <QFile>
#include "ui_QDynDialogRobotTable.h"
#include <Classes/QDynRobot.h>
#include <Widgets/QDynRobotTableDelegate.h>

class QDynDialogRobotTable : public QDialog, private Ui::QDynDialogRobotTable
{
    Q_OBJECT

public:
    QDynDialogRobotTable(QWidget *parent = 0);
    ~QDynDialogRobotTable();

    QFileDialog *fileDialog;
    QStringList filterXML;

    bool settingTable;
    void openDialog(QDynRobot *robot= 0);
    void setFileDialog(QFileDialog *dialog);


public slots:
    void jointChanged(int row);

private slots:
    void on_robotTable_itemChanged(QTableWidgetItem* item);
    void on_closeDialog_clicked();
    void on_actionClearTable_triggered();
    void on_actionDeleteLink_triggered();
    void on_actionAddLink_triggered();
    void on_robotTable_customContextMenuRequested(QPoint pos);
    void on_save_clicked();
};

#endif // QDYNDIALOGROBOTTABLE_H
