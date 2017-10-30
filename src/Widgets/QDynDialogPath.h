#ifndef QDYNDIALOGPATH_H
#define QDYNDIALOGPATH_H

#include <QDialog>
#include "ui_QDynDialogPath.h"
#include <QFileDialog>
#include <QFileInfo>
#include <QTreeWidget>
#include <QMessageBox>
#include <Classes/QDynRobot.h>
#include <Classes/QDynGeneric.h>
#include <QDebug>

class QDynDialogPath : public QDialog, private Ui::QDynDialogPath
{
    Q_OBJECT

public:
    QDynDialogPath(QWidget *parent = 0);
    ~QDynDialogPath();

    QFileDialog *fileDialog;
    QStringList filterTXT;
    QTreeWidget *robotTree;

    void setFileDialog(QFileDialog *dialog);
    void openDialog();

signals:
    void addPathFromFile(QString filename);
    void addPathFromPoints(double xI,double yI, double zI, double xF, double yF, double zF, int n);

private:
    double xSel;
    double ySel;
    double zSel;

private slots:
    void on_getFinFromLink_clicked();
    void on_getIniFromLink_clicked();
    void on_cancel_clicked();
    void on_ok_clicked();
    void on_pathOpenFile_clicked();
    void updateSelectedXYZ();
};

#endif // QDYNDIALOGPATH_H
