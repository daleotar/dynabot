/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created: Wed 20. Jul 16:14:04 2011
**      by: Qt User Interface Compiler version 4.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QComboBox>
#include <QtGui/QDockWidget>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QMainWindow>
#include <QtGui/QMenu>
#include <QtGui/QMenuBar>
#include <QtGui/QStatusBar>
#include <QtGui/QToolBar>
#include <QtGui/QTreeWidget>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionResetCamera;
    QAction *actionExit;
    QAction *actionAddObstacle;
    QAction *actionToggleBlend;
    QAction *actionToggleGlobalAxis;
    QAction *actionToggleLocalAxes;
    QAction *actionToggleObjectCoordinates;
    QAction *actionToggleGrid;
    QAction *actionDeleteObstacle;
    QAction *actionResetObstacle;
    QAction *actionAddRobot;
    QAction *actionCollideAllLinks;
    QAction *actionCollideEndEffector;
    QAction *actionCollideNone;
    QAction *actionDeleteRobot;
    QAction *actionResetRobot;
    QAction *actionAddPath;
    QAction *actionAddRobotPath;
    QAction *actionDeletePath;
    QAction *actionDeleteRobotPath;
    QAction *actionStartSimulation;
    QAction *actionStopSimulation;
    QAction *actionPauseSimulation;
    QAction *actionSetInitialSimulationConfiguration;
    QAction *actionNewScene;
    QAction *actionExportJointData;
    QAction *actionExportGraph;
    QAction *actionOpenRobotCreator;
    QAction *actionSaveScene;
    QAction *actionLoadScene;
    QAction *actionViewRobotDHTable;
    QWidget *centralWidget;
    QToolBar *toolBar;
    QDockWidget *robotWidget;
    QWidget *robotWidgetContents;
    QTreeWidget *robotTree;
    QDockWidget *obstacleWidget;
    QWidget *obstacleWidgetContents;
    QTreeWidget *obstacleTree;
    QMenuBar *menuBar;
    QMenu *menuFile;
    QMenu *menuObstacles;
    QMenu *menuView;
    QMenu *menuRobots;
    QMenu *menuCollisions;
    QMenu *menuInverseKinematics;
    QMenu *menuTools;
    QMenu *menuPaths;
    QMenu *menuSimulation;
    QStatusBar *messageBar;
    QDockWidget *pathWidget;
    QWidget *dockWidgetContents;
    QTreeWidget *pathTree;
    QDockWidget *graphWidget;
    QWidget *dockWidgetContents_3;
    QLabel *label;
    QComboBox *plotComboJoint;
    QComboBox *plotComboTypes;
    QComboBox *plotComboRobot;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(588, 777);
        QFont font;
        font.setFamily(QString::fromUtf8("Segoe UI"));
        MainWindow->setFont(font);
        MainWindow->setAutoFillBackground(false);
        MainWindow->setStyleSheet(QString::fromUtf8(""));
        MainWindow->setIconSize(QSize(28, 28));
        actionResetCamera = new QAction(MainWindow);
        actionResetCamera->setObjectName(QString::fromUtf8("actionResetCamera"));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/resources/icons/reset_camera.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionResetCamera->setIcon(icon);
        actionExit = new QAction(MainWindow);
        actionExit->setObjectName(QString::fromUtf8("actionExit"));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/resources/icons/exit.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionExit->setIcon(icon1);
        actionAddObstacle = new QAction(MainWindow);
        actionAddObstacle->setObjectName(QString::fromUtf8("actionAddObstacle"));
        QIcon icon2;
        icon2.addFile(QString::fromUtf8(":/resources/icons/objects.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionAddObstacle->setIcon(icon2);
        actionToggleBlend = new QAction(MainWindow);
        actionToggleBlend->setObjectName(QString::fromUtf8("actionToggleBlend"));
        actionToggleBlend->setCheckable(true);
        QIcon icon3;
        icon3.addFile(QString::fromUtf8(":/resources/icons/alpha_blending.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionToggleBlend->setIcon(icon3);
        actionToggleGlobalAxis = new QAction(MainWindow);
        actionToggleGlobalAxis->setObjectName(QString::fromUtf8("actionToggleGlobalAxis"));
        actionToggleGlobalAxis->setCheckable(true);
        QIcon icon4;
        icon4.addFile(QString::fromUtf8(":/resources/icons/global.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionToggleGlobalAxis->setIcon(icon4);
        actionToggleLocalAxes = new QAction(MainWindow);
        actionToggleLocalAxes->setObjectName(QString::fromUtf8("actionToggleLocalAxes"));
        actionToggleLocalAxes->setCheckable(true);
        QIcon icon5;
        icon5.addFile(QString::fromUtf8(":/resources/icons/local.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionToggleLocalAxes->setIcon(icon5);
        actionToggleObjectCoordinates = new QAction(MainWindow);
        actionToggleObjectCoordinates->setObjectName(QString::fromUtf8("actionToggleObjectCoordinates"));
        actionToggleObjectCoordinates->setCheckable(true);
        QIcon icon6;
        icon6.addFile(QString::fromUtf8(":/resources/icons/coordinates.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionToggleObjectCoordinates->setIcon(icon6);
        actionToggleGrid = new QAction(MainWindow);
        actionToggleGrid->setObjectName(QString::fromUtf8("actionToggleGrid"));
        actionToggleGrid->setCheckable(true);
        actionToggleGrid->setChecked(true);
        QIcon icon7;
        icon7.addFile(QString::fromUtf8(":/resources/icons/grid.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionToggleGrid->setIcon(icon7);
        actionDeleteObstacle = new QAction(MainWindow);
        actionDeleteObstacle->setObjectName(QString::fromUtf8("actionDeleteObstacle"));
        QIcon icon8;
        icon8.addFile(QString::fromUtf8(":/resources/icons/delete.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionDeleteObstacle->setIcon(icon8);
        actionResetObstacle = new QAction(MainWindow);
        actionResetObstacle->setObjectName(QString::fromUtf8("actionResetObstacle"));
        QIcon icon9;
        icon9.addFile(QString::fromUtf8(":/resources/icons/reset.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionResetObstacle->setIcon(icon9);
        actionAddRobot = new QAction(MainWindow);
        actionAddRobot->setObjectName(QString::fromUtf8("actionAddRobot"));
        QIcon icon10;
        icon10.addFile(QString::fromUtf8(":/resources/icons/robot.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionAddRobot->setIcon(icon10);
        actionCollideAllLinks = new QAction(MainWindow);
        actionCollideAllLinks->setObjectName(QString::fromUtf8("actionCollideAllLinks"));
        actionCollideAllLinks->setCheckable(true);
        QIcon icon11;
        icon11.addFile(QString::fromUtf8(":/resources/icons/collide_all.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionCollideAllLinks->setIcon(icon11);
        actionCollideEndEffector = new QAction(MainWindow);
        actionCollideEndEffector->setObjectName(QString::fromUtf8("actionCollideEndEffector"));
        actionCollideEndEffector->setCheckable(true);
        actionCollideEndEffector->setChecked(true);
        QIcon icon12;
        icon12.addFile(QString::fromUtf8(":/resources/icons/collide_end.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionCollideEndEffector->setIcon(icon12);
        actionCollideNone = new QAction(MainWindow);
        actionCollideNone->setObjectName(QString::fromUtf8("actionCollideNone"));
        actionCollideNone->setCheckable(true);
        QIcon icon13;
        icon13.addFile(QString::fromUtf8(":/resources/icons/collide_none.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionCollideNone->setIcon(icon13);
        actionDeleteRobot = new QAction(MainWindow);
        actionDeleteRobot->setObjectName(QString::fromUtf8("actionDeleteRobot"));
        actionDeleteRobot->setIcon(icon8);
        actionResetRobot = new QAction(MainWindow);
        actionResetRobot->setObjectName(QString::fromUtf8("actionResetRobot"));
        actionResetRobot->setIcon(icon9);
        actionAddPath = new QAction(MainWindow);
        actionAddPath->setObjectName(QString::fromUtf8("actionAddPath"));
        QIcon icon14;
        icon14.addFile(QString::fromUtf8(":/resources/icons/path.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionAddPath->setIcon(icon14);
        actionAddRobotPath = new QAction(MainWindow);
        actionAddRobotPath->setObjectName(QString::fromUtf8("actionAddRobotPath"));
        QIcon icon15;
        icon15.addFile(QString::fromUtf8(":/resources/icons/robot_path.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionAddRobotPath->setIcon(icon15);
        actionDeletePath = new QAction(MainWindow);
        actionDeletePath->setObjectName(QString::fromUtf8("actionDeletePath"));
        actionDeletePath->setIcon(icon8);
        actionDeleteRobotPath = new QAction(MainWindow);
        actionDeleteRobotPath->setObjectName(QString::fromUtf8("actionDeleteRobotPath"));
        actionDeleteRobotPath->setIcon(icon8);
        actionStartSimulation = new QAction(MainWindow);
        actionStartSimulation->setObjectName(QString::fromUtf8("actionStartSimulation"));
        actionStartSimulation->setEnabled(false);
        QIcon icon16;
        icon16.addFile(QString::fromUtf8(":/resources/icons/play.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionStartSimulation->setIcon(icon16);
        actionStopSimulation = new QAction(MainWindow);
        actionStopSimulation->setObjectName(QString::fromUtf8("actionStopSimulation"));
        actionStopSimulation->setEnabled(false);
        QIcon icon17;
        icon17.addFile(QString::fromUtf8(":/resources/icons/stop.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionStopSimulation->setIcon(icon17);
        actionPauseSimulation = new QAction(MainWindow);
        actionPauseSimulation->setObjectName(QString::fromUtf8("actionPauseSimulation"));
        actionPauseSimulation->setEnabled(false);
        QIcon icon18;
        icon18.addFile(QString::fromUtf8(":/resources/icons/pause.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionPauseSimulation->setIcon(icon18);
        actionSetInitialSimulationConfiguration = new QAction(MainWindow);
        actionSetInitialSimulationConfiguration->setObjectName(QString::fromUtf8("actionSetInitialSimulationConfiguration"));
        QIcon icon19;
        icon19.addFile(QString::fromUtf8(":/resources/icons/home.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionSetInitialSimulationConfiguration->setIcon(icon19);
        actionNewScene = new QAction(MainWindow);
        actionNewScene->setObjectName(QString::fromUtf8("actionNewScene"));
        QIcon icon20;
        icon20.addFile(QString::fromUtf8(":/resources/icons/new.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionNewScene->setIcon(icon20);
        actionExportJointData = new QAction(MainWindow);
        actionExportJointData->setObjectName(QString::fromUtf8("actionExportJointData"));
        QIcon icon21;
        icon21.addFile(QString::fromUtf8(":/resources/icons/export_data.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionExportJointData->setIcon(icon21);
        actionExportGraph = new QAction(MainWindow);
        actionExportGraph->setObjectName(QString::fromUtf8("actionExportGraph"));
        QIcon icon22;
        icon22.addFile(QString::fromUtf8(":/resources/icons/export_graph.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionExportGraph->setIcon(icon22);
        actionOpenRobotCreator = new QAction(MainWindow);
        actionOpenRobotCreator->setObjectName(QString::fromUtf8("actionOpenRobotCreator"));
        QIcon icon23;
        icon23.addFile(QString::fromUtf8(":/resources/icons/new_robot.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionOpenRobotCreator->setIcon(icon23);
        actionSaveScene = new QAction(MainWindow);
        actionSaveScene->setObjectName(QString::fromUtf8("actionSaveScene"));
        QIcon icon24;
        icon24.addFile(QString::fromUtf8(":/resources/icons/save_as.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionSaveScene->setIcon(icon24);
        actionLoadScene = new QAction(MainWindow);
        actionLoadScene->setObjectName(QString::fromUtf8("actionLoadScene"));
        QIcon icon25;
        icon25.addFile(QString::fromUtf8(":/resources/icons/open.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionLoadScene->setIcon(icon25);
        actionViewRobotDHTable = new QAction(MainWindow);
        actionViewRobotDHTable->setObjectName(QString::fromUtf8("actionViewRobotDHTable"));
        QIcon icon26;
        icon26.addFile(QString::fromUtf8(":/resources/icons/table_link.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionViewRobotDHTable->setIcon(icon26);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        MainWindow->setCentralWidget(centralWidget);
        toolBar = new QToolBar(MainWindow);
        toolBar->setObjectName(QString::fromUtf8("toolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, toolBar);
        robotWidget = new QDockWidget(MainWindow);
        robotWidget->setObjectName(QString::fromUtf8("robotWidget"));
        robotWidget->setMinimumSize(QSize(285, 100));
        robotWidget->setAllowedAreas(Qt::LeftDockWidgetArea|Qt::RightDockWidgetArea);
        robotWidgetContents = new QWidget();
        robotWidgetContents->setObjectName(QString::fromUtf8("robotWidgetContents"));
        robotTree = new QTreeWidget(robotWidgetContents);
        robotTree->setObjectName(QString::fromUtf8("robotTree"));
        robotTree->setGeometry(QRect(10, 10, 256, 131));
        robotTree->setContextMenuPolicy(Qt::CustomContextMenu);
        robotTree->setRootIsDecorated(true);
        robotTree->setUniformRowHeights(true);
        robotTree->setAnimated(true);
        robotTree->header()->setDefaultSectionSize(140);
        robotTree->header()->setMinimumSectionSize(140);
        robotWidget->setWidget(robotWidgetContents);
        MainWindow->addDockWidget(static_cast<Qt::DockWidgetArea>(1), robotWidget);
        obstacleWidget = new QDockWidget(MainWindow);
        obstacleWidget->setObjectName(QString::fromUtf8("obstacleWidget"));
        obstacleWidget->setMinimumSize(QSize(200, 100));
        obstacleWidget->setMaximumSize(QSize(524287, 524287));
        obstacleWidget->setFeatures(QDockWidget::AllDockWidgetFeatures);
        obstacleWidget->setAllowedAreas(Qt::LeftDockWidgetArea|Qt::RightDockWidgetArea);
        obstacleWidgetContents = new QWidget();
        obstacleWidgetContents->setObjectName(QString::fromUtf8("obstacleWidgetContents"));
        obstacleTree = new QTreeWidget(obstacleWidgetContents);
        obstacleTree->setObjectName(QString::fromUtf8("obstacleTree"));
        obstacleTree->setGeometry(QRect(10, 10, 256, 151));
        obstacleTree->setFocusPolicy(Qt::StrongFocus);
        obstacleTree->setContextMenuPolicy(Qt::CustomContextMenu);
        obstacleTree->setRootIsDecorated(true);
        obstacleTree->setUniformRowHeights(true);
        obstacleTree->setAnimated(true);
        obstacleTree->header()->setDefaultSectionSize(75);
        obstacleTree->header()->setMinimumSectionSize(75);
        obstacleWidget->setWidget(obstacleWidgetContents);
        MainWindow->addDockWidget(static_cast<Qt::DockWidgetArea>(1), obstacleWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 588, 21));
        menuFile = new QMenu(menuBar);
        menuFile->setObjectName(QString::fromUtf8("menuFile"));
        menuFile->setStyleSheet(QString::fromUtf8(""));
        menuObstacles = new QMenu(menuBar);
        menuObstacles->setObjectName(QString::fromUtf8("menuObstacles"));
        menuView = new QMenu(menuBar);
        menuView->setObjectName(QString::fromUtf8("menuView"));
        menuRobots = new QMenu(menuBar);
        menuRobots->setObjectName(QString::fromUtf8("menuRobots"));
        menuCollisions = new QMenu(menuRobots);
        menuCollisions->setObjectName(QString::fromUtf8("menuCollisions"));
        QIcon icon27;
        icon27.addFile(QString::fromUtf8(":/resources/icons/collision.png"), QSize(), QIcon::Normal, QIcon::Off);
        menuCollisions->setIcon(icon27);
        menuInverseKinematics = new QMenu(menuRobots);
        menuInverseKinematics->setObjectName(QString::fromUtf8("menuInverseKinematics"));
        QIcon icon28;
        icon28.addFile(QString::fromUtf8(":/resources/icons/link_pos.png"), QSize(), QIcon::Normal, QIcon::Off);
        menuInverseKinematics->setIcon(icon28);
        menuTools = new QMenu(menuRobots);
        menuTools->setObjectName(QString::fromUtf8("menuTools"));
        QIcon icon29;
        icon29.addFile(QString::fromUtf8(":/resources/icons/tools.png"), QSize(), QIcon::Normal, QIcon::Off);
        menuTools->setIcon(icon29);
        menuPaths = new QMenu(menuBar);
        menuPaths->setObjectName(QString::fromUtf8("menuPaths"));
        menuSimulation = new QMenu(menuBar);
        menuSimulation->setObjectName(QString::fromUtf8("menuSimulation"));
        MainWindow->setMenuBar(menuBar);
        messageBar = new QStatusBar(MainWindow);
        messageBar->setObjectName(QString::fromUtf8("messageBar"));
        MainWindow->setStatusBar(messageBar);
        pathWidget = new QDockWidget(MainWindow);
        pathWidget->setObjectName(QString::fromUtf8("pathWidget"));
        pathWidget->setMinimumSize(QSize(80, 100));
        pathWidget->setAllowedAreas(Qt::LeftDockWidgetArea|Qt::RightDockWidgetArea);
        dockWidgetContents = new QWidget();
        dockWidgetContents->setObjectName(QString::fromUtf8("dockWidgetContents"));
        pathTree = new QTreeWidget(dockWidgetContents);
        pathTree->setObjectName(QString::fromUtf8("pathTree"));
        pathTree->setGeometry(QRect(10, 10, 256, 151));
        pathTree->setFocusPolicy(Qt::StrongFocus);
        pathTree->setContextMenuPolicy(Qt::CustomContextMenu);
        pathTree->setRootIsDecorated(true);
        pathTree->setUniformRowHeights(true);
        pathTree->setAnimated(true);
        pathTree->header()->setDefaultSectionSize(75);
        pathTree->header()->setMinimumSectionSize(75);
        pathWidget->setWidget(dockWidgetContents);
        MainWindow->addDockWidget(static_cast<Qt::DockWidgetArea>(1), pathWidget);
        graphWidget = new QDockWidget(MainWindow);
        graphWidget->setObjectName(QString::fromUtf8("graphWidget"));
        graphWidget->setMinimumSize(QSize(80, 100));
        graphWidget->setFloating(false);
        graphWidget->setAllowedAreas(Qt::LeftDockWidgetArea|Qt::RightDockWidgetArea);
        dockWidgetContents_3 = new QWidget();
        dockWidgetContents_3->setObjectName(QString::fromUtf8("dockWidgetContents_3"));
        label = new QLabel(dockWidgetContents_3);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(20, 10, 247, 16));
        QFont font1;
        font1.setPointSize(10);
        font1.setBold(true);
        font1.setWeight(75);
        label->setFont(font1);
        label->setFrameShape(QFrame::NoFrame);
        label->setScaledContents(true);
        label->setAlignment(Qt::AlignCenter);
        plotComboJoint = new QComboBox(dockWidgetContents_3);
        plotComboJoint->setObjectName(QString::fromUtf8("plotComboJoint"));
        plotComboJoint->setGeometry(QRect(120, 80, 69, 22));
        plotComboTypes = new QComboBox(dockWidgetContents_3);
        plotComboTypes->setObjectName(QString::fromUtf8("plotComboTypes"));
        plotComboTypes->setGeometry(QRect(120, 110, 69, 22));
        plotComboRobot = new QComboBox(dockWidgetContents_3);
        plotComboRobot->setObjectName(QString::fromUtf8("plotComboRobot"));
        plotComboRobot->setGeometry(QRect(120, 50, 69, 22));
        graphWidget->setWidget(dockWidgetContents_3);
        MainWindow->addDockWidget(static_cast<Qt::DockWidgetArea>(1), graphWidget);
        robotWidget->raise();
        obstacleWidget->raise();
        pathWidget->raise();
        graphWidget->raise();

        toolBar->addAction(actionNewScene);
        toolBar->addAction(actionLoadScene);
        toolBar->addAction(actionSaveScene);
        toolBar->addSeparator();
        toolBar->addAction(actionAddRobot);
        toolBar->addAction(actionAddObstacle);
        toolBar->addSeparator();
        toolBar->addAction(actionCollideAllLinks);
        toolBar->addAction(actionCollideEndEffector);
        toolBar->addAction(actionCollideNone);
        toolBar->addSeparator();
        toolBar->addAction(actionStartSimulation);
        toolBar->addAction(actionPauseSimulation);
        toolBar->addAction(actionStopSimulation);
        toolBar->addSeparator();
        toolBar->addAction(actionToggleGlobalAxis);
        toolBar->addAction(actionToggleLocalAxes);
        toolBar->addAction(actionToggleGrid);
        menuBar->addAction(menuFile->menuAction());
        menuBar->addAction(menuRobots->menuAction());
        menuBar->addAction(menuObstacles->menuAction());
        menuBar->addAction(menuPaths->menuAction());
        menuBar->addAction(menuSimulation->menuAction());
        menuBar->addAction(menuView->menuAction());
        menuFile->addAction(actionNewScene);
        menuFile->addAction(actionLoadScene);
        menuFile->addAction(actionSaveScene);
        menuFile->addSeparator();
        menuFile->addAction(actionExit);
        menuObstacles->addAction(actionAddObstacle);
        menuView->addAction(actionResetCamera);
        menuView->addSeparator();
        menuView->addAction(actionToggleBlend);
        menuView->addSeparator();
        menuView->addAction(actionToggleGlobalAxis);
        menuView->addAction(actionToggleLocalAxes);
        menuView->addAction(actionToggleObjectCoordinates);
        menuView->addAction(actionToggleGrid);
        menuRobots->addAction(actionAddRobot);
        menuRobots->addSeparator();
        menuRobots->addAction(menuTools->menuAction());
        menuRobots->addAction(menuCollisions->menuAction());
        menuRobots->addAction(menuInverseKinematics->menuAction());
        menuCollisions->addAction(actionCollideAllLinks);
        menuCollisions->addAction(actionCollideEndEffector);
        menuCollisions->addAction(actionCollideNone);
        menuInverseKinematics->addAction(actionAddRobotPath);
        menuTools->addAction(actionOpenRobotCreator);
        menuPaths->addAction(actionAddPath);
        menuSimulation->addAction(actionStartSimulation);
        menuSimulation->addAction(actionPauseSimulation);
        menuSimulation->addAction(actionStopSimulation);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "DynaBOT v1.0", 0, QApplication::UnicodeUTF8));
        actionResetCamera->setText(QApplication::translate("MainWindow", "Reset Camera", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        actionResetCamera->setToolTip(QApplication::translate("MainWindow", "Resets the rotation and location of the camera to its default values.", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        actionExit->setText(QApplication::translate("MainWindow", "Exit", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        actionExit->setToolTip(QApplication::translate("MainWindow", "Exits the program", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        actionAddObstacle->setText(QApplication::translate("MainWindow", "Add Obstacle from OBJ file...", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        actionAddObstacle->setToolTip(QApplication::translate("MainWindow", "Add Obstacle from OBJ file...", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        actionToggleBlend->setText(QApplication::translate("MainWindow", "Alpha Blending", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        actionToggleBlend->setToolTip(QApplication::translate("MainWindow", "Enables/Disables alpha blending for all objects in the scene", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        actionToggleGlobalAxis->setText(QApplication::translate("MainWindow", "Global Axis", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        actionToggleGlobalAxis->setToolTip(QApplication::translate("MainWindow", "Show/Hide Global reference frame", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        actionToggleLocalAxes->setText(QApplication::translate("MainWindow", "Local Axes", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        actionToggleLocalAxes->setToolTip(QApplication::translate("MainWindow", "Show/Hide local reference frame for all objects", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        actionToggleObjectCoordinates->setText(QApplication::translate("MainWindow", "Object Coordinates", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        actionToggleObjectCoordinates->setToolTip(QApplication::translate("MainWindow", "Show/Hide the lines of spatial coordinates for all objects", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        actionToggleGrid->setText(QApplication::translate("MainWindow", "Grid", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        actionToggleGrid->setToolTip(QApplication::translate("MainWindow", "Show/Hide the base Grid", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        actionDeleteObstacle->setText(QApplication::translate("MainWindow", "Delete obstacle", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        actionDeleteObstacle->setToolTip(QApplication::translate("MainWindow", "Deletes the selected Obstacle", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        actionResetObstacle->setText(QApplication::translate("MainWindow", "Reset obstacle values", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        actionResetObstacle->setToolTip(QApplication::translate("MainWindow", "Sets to Zero Obstacle's Rotation and Translation", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        actionAddRobot->setText(QApplication::translate("MainWindow", "Add Robot from a XML file...", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        actionAddRobot->setToolTip(QApplication::translate("MainWindow", "Add Robot from a XML file...", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        actionCollideAllLinks->setText(QApplication::translate("MainWindow", "All Links vs. all Obstacles", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        actionCollideAllLinks->setToolTip(QApplication::translate("MainWindow", "Checks collisions between all Links and all Obstacles", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        actionCollideEndEffector->setText(QApplication::translate("MainWindow", "End Effector vs. all Obstacles", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        actionCollideEndEffector->setToolTip(QApplication::translate("MainWindow", "Checks collisions just between end effector and all Obstacles", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        actionCollideNone->setText(QApplication::translate("MainWindow", "No Collisions", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        actionCollideNone->setToolTip(QApplication::translate("MainWindow", "Disables collision cheking", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        actionDeleteRobot->setText(QApplication::translate("MainWindow", "Delete robot", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        actionDeleteRobot->setToolTip(QApplication::translate("MainWindow", "Deletes the selected Robot", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        actionResetRobot->setText(QApplication::translate("MainWindow", "Reset robot", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        actionResetRobot->setToolTip(QApplication::translate("MainWindow", "Sets to Zero Robot's Rotation and Translation and the joint values to its default", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        actionAddPath->setText(QApplication::translate("MainWindow", "Add Path...", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        actionAddPath->setToolTip(QApplication::translate("MainWindow", "Adds a Path from a .txt file or from two points", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        actionAddRobotPath->setText(QApplication::translate("MainWindow", "Add a Path to be followed by Robot...", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        actionAddRobotPath->setToolTip(QApplication::translate("MainWindow", "Adds a Path to be followed by the selected Robot", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        actionDeletePath->setText(QApplication::translate("MainWindow", "Delete Path", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        actionDeletePath->setToolTip(QApplication::translate("MainWindow", "Deletes the selected Path", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        actionDeleteRobotPath->setText(QApplication::translate("MainWindow", "Delete this Robot Path", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        actionDeleteRobotPath->setToolTip(QApplication::translate("MainWindow", "Deletes the selected Robot Path", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        actionStartSimulation->setText(QApplication::translate("MainWindow", "Start Simulation", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        actionStartSimulation->setToolTip(QApplication::translate("MainWindow", "Starts the Simulation for all Robots in the Scene", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        actionStopSimulation->setText(QApplication::translate("MainWindow", "Stop Simulation", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        actionStopSimulation->setToolTip(QApplication::translate("MainWindow", "Stops the running the simulation", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        actionPauseSimulation->setText(QApplication::translate("MainWindow", "Pause Simulation", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        actionPauseSimulation->setToolTip(QApplication::translate("MainWindow", "Pauses the current running simulation", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        actionSetInitialSimulationConfiguration->setText(QApplication::translate("MainWindow", "Set initial simulation configuration", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        actionSetInitialSimulationConfiguration->setToolTip(QApplication::translate("MainWindow", "Sets the robot configuration to its simulation initial configuration", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        actionNewScene->setText(QApplication::translate("MainWindow", "New Scene", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        actionNewScene->setToolTip(QApplication::translate("MainWindow", "New Scene", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        actionExportJointData->setText(QApplication::translate("MainWindow", "Export Joint Data...", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        actionExportJointData->setToolTip(QApplication::translate("MainWindow", "Exports all Data for selected Joint", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        actionExportGraph->setText(QApplication::translate("MainWindow", "Export this Graph...", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        actionExportGraph->setToolTip(QApplication::translate("MainWindow", "Export the actual Graph", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        actionOpenRobotCreator->setText(QApplication::translate("MainWindow", "Robot Creator", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        actionOpenRobotCreator->setToolTip(QApplication::translate("MainWindow", "Open Robot Creator...", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        actionSaveScene->setText(QApplication::translate("MainWindow", "Save Scene...", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        actionSaveScene->setToolTip(QApplication::translate("MainWindow", "Save current Scene into XML file...", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        actionLoadScene->setText(QApplication::translate("MainWindow", "Load Scene...", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        actionLoadScene->setToolTip(QApplication::translate("MainWindow", "Load Scene from a XML file...", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        actionViewRobotDHTable->setText(QApplication::translate("MainWindow", "View Robot's DH Table", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        actionViewRobotDHTable->setToolTip(QApplication::translate("MainWindow", "Open a window containing the DH Table of the Robot", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        toolBar->setWindowTitle(QApplication::translate("MainWindow", "Tool Bar", 0, QApplication::UnicodeUTF8));
        robotWidget->setWindowTitle(QApplication::translate("MainWindow", "Robots", 0, QApplication::UnicodeUTF8));
        QTreeWidgetItem *___qtreewidgetitem = robotTree->headerItem();
        ___qtreewidgetitem->setText(1, QApplication::translate("MainWindow", "Value", 0, QApplication::UnicodeUTF8));
        ___qtreewidgetitem->setText(0, QApplication::translate("MainWindow", "Robots", 0, QApplication::UnicodeUTF8));
        obstacleWidget->setWindowTitle(QApplication::translate("MainWindow", "Obstacles", 0, QApplication::UnicodeUTF8));
        QTreeWidgetItem *___qtreewidgetitem1 = obstacleTree->headerItem();
        ___qtreewidgetitem1->setText(1, QApplication::translate("MainWindow", "Value", 0, QApplication::UnicodeUTF8));
        ___qtreewidgetitem1->setText(0, QApplication::translate("MainWindow", "Obstacle", 0, QApplication::UnicodeUTF8));
        menuFile->setTitle(QApplication::translate("MainWindow", "File", 0, QApplication::UnicodeUTF8));
        menuObstacles->setTitle(QApplication::translate("MainWindow", "Obstacles", 0, QApplication::UnicodeUTF8));
        menuView->setTitle(QApplication::translate("MainWindow", "View", 0, QApplication::UnicodeUTF8));
        menuRobots->setTitle(QApplication::translate("MainWindow", "Robots", 0, QApplication::UnicodeUTF8));
        menuCollisions->setTitle(QApplication::translate("MainWindow", "Collisions", 0, QApplication::UnicodeUTF8));
        menuInverseKinematics->setTitle(QApplication::translate("MainWindow", "Inverse Kinematics", 0, QApplication::UnicodeUTF8));
        menuTools->setTitle(QApplication::translate("MainWindow", "Tools", 0, QApplication::UnicodeUTF8));
        menuPaths->setTitle(QApplication::translate("MainWindow", "Paths", 0, QApplication::UnicodeUTF8));
        menuSimulation->setTitle(QApplication::translate("MainWindow", "Simulation", 0, QApplication::UnicodeUTF8));
        pathWidget->setWindowTitle(QApplication::translate("MainWindow", "Paths", 0, QApplication::UnicodeUTF8));
        QTreeWidgetItem *___qtreewidgetitem2 = pathTree->headerItem();
        ___qtreewidgetitem2->setText(1, QApplication::translate("MainWindow", "Value", 0, QApplication::UnicodeUTF8));
        ___qtreewidgetitem2->setText(0, QApplication::translate("MainWindow", "Path", 0, QApplication::UnicodeUTF8));
        graphWidget->setWindowTitle(QApplication::translate("MainWindow", "Graphs", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("MainWindow", "There is no simulation data to plot yet", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
