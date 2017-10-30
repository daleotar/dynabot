#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QCoreApplication>
#include <QMainWindow>
#include <QtGui>
#include <qwt_plot.h>
#include <qwt_plot_curve.h>
#include <qwt_plot_renderer.h>
#include <qwt_plot_grid.h>
#include "ui_mainwindow.h"
#include <Classes/QDynScene.h>
#include <Classes/QDynGeneric.h>
#include <Widgets/QDynSpinSliderDelegate.h>
#include <Widgets/QDynLineEditDelegate.h>
#include <Widgets/QDynWindowStyles.h>
#include <Widgets/QDynDialogPath.h>
#include <Widgets/QDynDialogRobotPath.h>
#include <Widgets/QDynDialogRobotTable.h>

const QString alphaSymbol = QString::fromWCharArray(L"\u03B1");
const QString thetaSymbol = QString::fromWCharArray(L"\u03B8");
const QString derivSymbol = QString::fromWCharArray(L"\u2202");
const QString tauSymbol   = QString::fromWCharArray(L"\u03C4");

class MainWindow : public QMainWindow, private Ui::MainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();
    QDynScene *Scene;

    // File dialogs variables
    QFileDialog *fileDialog;
    QStringList filterOBJ;
    QStringList filterXML;
    QStringList filterCSV;

    // Custom Dialogs
    QDynDialogPath          *pathDialog;
    QDynDialogRobotPath     *robotPathDialog;
    QDynDialogRobotTable    *robotTableDialog;

    // Menus pointers
    QActionGroup *typeCollideGroup;

    // Window Styles
    QDynStyleCleanlooks *styleCleanlooks;
    QDynStylePlastique *stylePlastique;
    QDynStyleWindowsVista *styleWindowsVista;
    QDynStyleWindowsXP *styleWindowsXP;

    // Plotting Dock Widget
    QwtPlot         *plot;
    QwtPlotGrid     *plotGrid;
    QwtPlotCurve    *plotJointRefData;
    QwtPlotCurve    *plotJointSimData;
    QWidget         *plotDummyWidget;
    QGridLayout     *plotWidgetLayout;
    QCheckBox       *plotDynResponse;
    bool            cleaningPlot;
    bool            settingCombo;

    // Status Bar Elements
    QLabel          *statusMessage;
    QProgressBar    *statusProgress;

private:
    bool flagObstacleTree;
    bool flagRobotTree;
    bool flagPathTree;

public slots:
    void updateObstacleTree();
    void updateRobotTree();
    void refreshRobotTree();
    void updatePathTree();
    void addPathFromFile(QString filename);
    void addPathFromPoints(double xI,double yI, double zI, double xF, double yF, double zF, int n);
    void addRobotPath(int robotIndex, int pathNumber, int linkNumber, double approachSpeed, double speed);
    void simulationStarted();
    void simulationStopped();
    void simulationRunning();
    void simulationPaused();
    void processUpdated(QString process, int percentage);
    void deletePlot();
    void showPlot();
    void setPlot();
    void updatePlot();

private slots:
    void on_robotTree_itemSelectionChanged();
    void on_actionOpenRobotCreator_triggered();
    void on_actionViewRobotDHTable_triggered();
    void on_actionExportGraph_triggered();
    void on_actionExportJointData_triggered();
    void plotContextMenu(QPoint pos);
    void on_actionNewScene_triggered();
    void on_plotComboTypes_currentIndexChanged(int index);
    void on_plotComboJoint_currentIndexChanged(int index);
    void on_plotComboRobot_currentIndexChanged(int index);
    void on_actionSetInitialSimulationConfiguration_triggered();
    void on_actionPauseSimulation_triggered();
    void on_actionStopSimulation_triggered();
    void on_actionStartSimulation_triggered();
    void on_actionDeleteRobotPath_triggered();
    void on_actionAddRobotPath_triggered();
    void on_actionDeletePath_triggered();
    void on_pathTree_customContextMenuRequested(QPoint pos);
    void on_pathTree_clicked(QModelIndex index);
    void on_obstacleTree_clicked(QModelIndex index);
    void on_robotTree_clicked(QModelIndex index);
    void on_pathTree_itemChanged(QTreeWidgetItem* item, int column);
    void on_actionAddPath_triggered();
    void on_robotTree_customContextMenuRequested(QPoint pos);
    void on_actionResetRobot_triggered();
    void on_actionDeleteRobot_triggered();
    void on_robotTree_itemChanged(QTreeWidgetItem* item, int column);
    void on_obstacleTree_itemChanged(QTreeWidgetItem* item, int column);
    void on_obstacleTree_customContextMenuRequested(QPoint pos);
    void on_actionCollideNone_triggered();
    void on_actionCollideEndEffector_triggered();
    void on_actionCollideAllLinks_triggered();
    void on_actionAddRobot_triggered();
    void on_actionResetObstacle_triggered();
    void on_actionDeleteObstacle_triggered();
    void on_actionToggleGrid_triggered();
    void on_actionToggleObjectCoordinates_triggered();
    void on_actionToggleLocalAxes_triggered();
    void on_actionToggleGlobalAxis_triggered();
    void on_actionToggleBlend_triggered();
    void on_actionAddObstacle_triggered();
    void on_actionExit_triggered();
    void on_actionResetCamera_triggered();
};

#endif // MAINWINDOW_H
