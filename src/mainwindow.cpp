#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
{
    setupUi(this);
    Scene = new QDynScene(this);
    this->setCentralWidget(Scene);
    this->setWindowState(Qt::WindowMaximized);

    connect(Scene,SIGNAL(simulationStarted()),this,SLOT(simulationStarted()));
    connect(Scene,SIGNAL(simulationStopped()),this,SLOT(simulationStopped()));
    connect(Scene,SIGNAL(simulationPaused()),this,SLOT(simulationPaused()));
    connect(Scene,SIGNAL(simulationResumed()),this,SLOT(simulationRunning()));
    connect(Scene,SIGNAL(processUpdated(QString,int)),this,SLOT(processUpdated(QString,int)));

    statusMessage = new QLabel(messageBar);
    statusMessage->setMinimumWidth(140);

    statusProgress = new QProgressBar(messageBar);
    statusProgress->setMinimumWidth(140);
    statusProgress->setFixedWidth(140);
    statusProgress->setRange(0,100);
    statusProgress->setAlignment(Qt::AlignHCenter);
    statusProgress->hide();

    messageBar->addPermanentWidget(statusMessage);
    messageBar->addPermanentWidget(statusProgress);

    typeCollideGroup = new QActionGroup(this);
    typeCollideGroup->addAction(actionCollideAllLinks);
    typeCollideGroup->addAction(actionCollideEndEffector);
    typeCollideGroup->addAction(actionCollideNone);

    fileDialog = new QFileDialog(this);
    fileDialog->setDirectory(QDir::currentPath());

    filterOBJ << "Wavefront OBJ (*.obj)";
    filterOBJ << "All files (*.*)";

    filterXML << "XML Files (*.xml)";
    filterXML << "All files (*.*)";

    filterCSV << "Comma Separated Values (*.csv)";
    filterCSV << "All files (*.*)";

    pathDialog = new QDynDialogPath(this);
    connect(pathDialog,SIGNAL(addPathFromFile(QString)),this,SLOT(addPathFromFile(QString)));
    connect(pathDialog,SIGNAL(addPathFromPoints(double,double,double,double,double,double,int)),this,SLOT(addPathFromPoints(double,double,double,double,double,double,int)));
    pathDialog->robotTree = robotTree;
    pathDialog->setFileDialog(fileDialog);

    robotPathDialog = new QDynDialogRobotPath(this);
    connect(robotPathDialog,SIGNAL(addRobotPath(int,int,int,double,double)),this,SLOT(addRobotPath(int,int,int,double,double)));

    robotTableDialog = new QDynDialogRobotTable(this);
    robotTableDialog->setFileDialog(fileDialog);

    obstacleTree->setItemDelegate(new QDynSpinSliderDelegate(obstacleTree,QDynSpinSliderDelegate::Obstacle));
    obstacleWidget->setWidget(obstacleTree);

    obstacleTree->setColumnWidth(0,75);
    obstacleTree->setColumnWidth(1,75);

    robotTree->setItemDelegate(new QDynSpinSliderDelegate(obstacleTree,QDynSpinSliderDelegate::Robot));
    robotWidget->setWidget(robotTree);

    robotTree->setColumnWidth(0,140);
    robotTree->setColumnWidth(1,140);

    pathTree->setItemDelegate(new QDynLineEditDelegate(pathTree));
    pathWidget->setWidget(pathTree);

    pathTree->setColumnWidth(0,140);
    pathTree->setColumnWidth(1,140);

    // Plot Widget Elements

    QLabel *plotLabelRobot      = new QLabel("Robot:");
    QLabel *plotLabelJoint      = new QLabel("Joint:");
    QLabel *plotLabelTypes      = new QLabel("Graph:");
    QLabel *plotLabelControl    = new QLabel("Control:");

    plotLabelRobot->setFixedWidth(43);
    plotLabelJoint->setFixedWidth(43);
    plotLabelTypes->setFixedWidth(43);
    plotLabelControl->setFixedWidth(43);

    plotLabelRobot->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
    plotLabelJoint->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
    plotLabelTypes->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
    plotLabelControl->setAlignment(Qt::AlignRight | Qt::AlignVCenter);

    plot                = new QwtPlot(this);
    plotDummyWidget     = new QWidget;
    plotWidgetLayout    = new QGridLayout;
    plotDynResponse     = new QCheckBox("View Dynamic Responses");

    plotDummyWidget->setLayout(plotWidgetLayout);
    plot->setContentsMargins(0,5,0,0);
    plot->setMinimumHeight(200);
    plot->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(plot,SIGNAL(customContextMenuRequested(QPoint)),this,SLOT(plotContextMenu(QPoint)));

    plotWidgetLayout->addWidget(plotLabelRobot,0,0);
    plotWidgetLayout->addWidget(plotComboRobot,0,1);
    plotWidgetLayout->addWidget(plotLabelJoint,1,0);
    plotWidgetLayout->addWidget(plotComboJoint,1,1);
    plotWidgetLayout->addWidget(plotLabelTypes,2,0);
    plotWidgetLayout->addWidget(plotComboTypes,2,1);
    plotWidgetLayout->addWidget(plotLabelControl,3,0);
    plotWidgetLayout->addWidget(plotDynResponse,3,1);
    plotWidgetLayout->addWidget(plot,4,0,1,2);

    plotJointRefData = 0;
    plotJointSimData = 0;

    QwtText title("Titulo");
    title.setFont(QFont("Segoe UI",8,QFont::StyleNormal));

    plot->setTitle(title);
    plot->setAxisTitle(QwtPlot::xBottom, title);
    plot->setAxisTitle(QwtPlot::yLeft, title);
    plot->setAxisFont(QwtPlot::xBottom,title.font());
    plot->setAxisFont(QwtPlot::yLeft,title.font());
    plot->setCanvasBackground(QColor(Qt::white));

    QPalette plotPalette = plot->palette();
    plotPalette.setColor(backgroundRole(), QColor( 255, 255, 255 ));
    plot->setPalette(plotPalette);
    plot->setAutoFillBackground(false);

    deletePlot();


    // Apply Styles

    styleCleanlooks = new QDynStyleCleanlooks();
    stylePlastique = new QDynStylePlastique();
    styleWindowsVista = new QDynStyleWindowsVista();
    styleWindowsXP = new QDynStyleWindowsXP();

    QApplication::setStyle(styleCleanlooks);
    QApplication::setPalette(QApplication::style()->standardPalette());
    QApplication::setFont(QFont("Segoe UI",8));

}

MainWindow::~MainWindow()
{
    QApplication::quit();
}

void MainWindow::on_actionResetCamera_triggered()
{
    Scene->resetView();
}

void MainWindow::on_actionExit_triggered()
{
    pathDialog->close();
    Scene->stopSimulation();
    QApplication::quit();
}

void MainWindow::on_actionToggleBlend_triggered()
{
    Scene->toggleBlend(actionToggleBlend->isChecked());
}

void MainWindow::on_actionToggleGlobalAxis_triggered()
{
    Scene->toggleGlobalAxis(actionToggleGlobalAxis->isChecked());
}

void MainWindow::on_actionToggleLocalAxes_triggered()
{
    Scene->toggleLocalAxes(actionToggleLocalAxes->isChecked());
}

void MainWindow::on_actionToggleObjectCoordinates_triggered()
{
    Scene->toggleObjectCoordinates(actionToggleObjectCoordinates->isChecked());
}

void MainWindow::on_actionToggleGrid_triggered()
{
    Scene->toggleGrid(actionToggleGrid->isChecked());
}

// Obstacle Slots & Functions

void MainWindow::on_actionAddObstacle_triggered()
{
    fileDialog->setFileMode(QFileDialog::ExistingFile);
    fileDialog->setFilters(filterOBJ);
    fileDialog->setOption(QFileDialog::DontUseNativeDialog,true);
    fileDialog->setAcceptMode(QFileDialog::AcceptOpen);
    fileDialog->setDirectory(QDir::currentPath() + "/../obstacles");

    if(fileDialog->exec())
    {
        Scene->addObstacle(fileDialog->selectedFiles().at(0));
        updateObstacleTree();
    }
}

void MainWindow::on_actionDeleteObstacle_triggered()
{
    if(obstacleTree->selectedItems().count()>0)
    {
        if(QMessageBox::question(0,"DynaBOT::Obstacles::Question","Do you really want to delete this obstacle?", QMessageBox::Yes | QMessageBox::No) == QMessageBox::Yes)
        {
            int index;
            if(obstacleTree->currentItem()->parent())
            {
                index = obstacleTree->indexOfTopLevelItem(obstacleTree->currentItem()->parent());
            }
            else
            {
                index = obstacleTree->indexOfTopLevelItem(obstacleTree->currentItem());
            }
            Scene->deleteObstacle(index);
            updateObstacleTree();
        }
    }
    else
    {
        QMessageBox::warning(0,"DynaBOT::Obstacles::Warning","There is no obstacles selected to delete.");
    }
}

void MainWindow::on_actionResetObstacle_triggered()
{
    if(obstacleTree->selectedItems().count()>0)
    {
        if(QMessageBox::question(0,"DynaBOT::Obstacles::Question","Do you really want to reset the location and rotation of the obstacle?", QMessageBox::Yes | QMessageBox::No) == QMessageBox::Yes)
        {
            int index;
            if(obstacleTree->currentItem()->parent())
            {
                index = obstacleTree->indexOfTopLevelItem(obstacleTree->currentItem()->parent());
            }
            else
            {
                index = obstacleTree->indexOfTopLevelItem(obstacleTree->currentItem());
            }
            Scene->setObstacleProperties("",0,0,0,0,0,0,index);
            updateObstacleTree();
        }
    }
    else
    {
        QMessageBox::warning(0,"DynaBOT::Obstacles::Warning","There is no obstacles selected to reset.");
    }
}

void MainWindow::on_obstacleTree_customContextMenuRequested(QPoint pos)
{
    robotTree->clearSelection();
    pathTree->clearSelection();

    QMenu menu(this);
    menu.addAction(actionAddObstacle);

    QTreeWidgetItem *selItem = obstacleTree->itemAt(pos);

    if(selItem)
    {
        menu.addSeparator();
        menu.addAction(actionDeleteObstacle);
        menu.addAction(actionResetObstacle);
    }
    else
    {
        obstacleTree->clearSelection();
    }

    menu.exec(obstacleTree->viewport()->mapToGlobal(pos));
}

void MainWindow::on_obstacleTree_itemChanged(QTreeWidgetItem* item, int column)
{
    if(flagObstacleTree)
    {
        if(item->parent())
        {
            QDynObstacle::QDynLocRotProps prop;

            if(item->parent()->indexOfChild(item) == 0) prop = QDynObstacle::PropX;
            if(item->parent()->indexOfChild(item) == 1) prop = QDynObstacle::PropY;
            if(item->parent()->indexOfChild(item) == 2) prop = QDynObstacle::PropZ;
            if(item->parent()->indexOfChild(item) == 3) prop = QDynObstacle::PropRotX;
            if(item->parent()->indexOfChild(item) == 4) prop = QDynObstacle::PropRotY;
            if(item->parent()->indexOfChild(item) == 5) prop = QDynObstacle::PropRotZ;

            QString value = item->text(1);
            value.chop(2);

            Scene->setObstacleProperties(prop,value.toDouble(),obstacleTree->indexOfTopLevelItem(item->parent()));
        }
        else
        {
            Scene->setObstacleProperties(QDynObstacle::PropName,item->text(0), obstacleTree->indexOfTopLevelItem(item));
        }
    }
}

void MainWindow::updateObstacleTree()
{
    flagObstacleTree = false;
    obstacleTree->clear();

    for (int i=0; i<Scene->Obstacles.length(); i++)
    {
        QTreeWidgetItem *actObstacle = new QTreeWidgetItem(obstacleTree);
        actObstacle->setText(0,Scene->Obstacles[i]->name);
        QTreeWidgetItem *x = new QTreeWidgetItem(actObstacle);
        QTreeWidgetItem *y = new QTreeWidgetItem(actObstacle);
        QTreeWidgetItem *z = new QTreeWidgetItem(actObstacle);
        QTreeWidgetItem *rotX = new QTreeWidgetItem(actObstacle);
        QTreeWidgetItem *rotY = new QTreeWidgetItem(actObstacle);
        QTreeWidgetItem *rotZ = new QTreeWidgetItem(actObstacle);

        actObstacle->setSizeHint(0,QSize(obstacleTree->columnWidth(0),24));
        actObstacle->setSizeHint(1,QSize(obstacleTree->columnWidth(1),24));

        for(int j=0; j<actObstacle->childCount(); j++)
        {
            actObstacle->child(j)->setSizeHint(0,actObstacle->sizeHint(0));
            actObstacle->child(j)->setSizeHint(1,actObstacle->sizeHint(1));
        }

        x->setIcon(0,QIcon(":/resources/icons/move_x.png"));
        y->setIcon(0,QIcon(":/resources/icons/move_y.png"));
        z->setIcon(0,QIcon(":/resources/icons/move_z.png"));
        rotX->setIcon(0,QIcon(":/resources/icons/rotate_x.png"));
        rotY->setIcon(0,QIcon(":/resources/icons/rotate_y.png"));
        rotZ->setIcon(0,QIcon(":/resources/icons/rotate_z.png"));

        actObstacle->setFlags(actObstacle->flags() | Qt::ItemIsEditable);
        x->setFlags(x->flags() | Qt::ItemIsEditable);
        y->setFlags(y->flags() | Qt::ItemIsEditable);
        z->setFlags(z->flags() | Qt::ItemIsEditable);
        rotX->setFlags(rotX->flags() | Qt::ItemIsEditable);
        rotY->setFlags(rotY->flags() | Qt::ItemIsEditable);
        rotZ->setFlags(rotZ->flags() | Qt::ItemIsEditable);

        x->setText(1,QString::number(Scene->Obstacles[i]->T[0]) + " m");
        y->setText(1,QString::number(Scene->Obstacles[i]->T[1]) + " m");
        z->setText(1,QString::number(Scene->Obstacles[i]->T[2]) + " m");
        rotX->setText(1,QString::number(Scene->Obstacles[i]->rotX) + " °");
        rotY->setText(1,QString::number(Scene->Obstacles[i]->rotY) + " °");
        rotZ->setText(1,QString::number(Scene->Obstacles[i]->rotZ) + " °");

        if(Scene->Obstacles[i]->isColliding)
        {
//            for(int j=0; j<7; j++)
//            {
//            obstacleTable->item(i,j)->setBackground(QBrush(QColor(255,120,120)));
//            }
        }
        else
        {
//            for(int j=0; j<7; j++)
//            {
//            obstacleTable->item(i,j)->setBackground(QBrush(QColor(255,255,255)));
//            }
        }
    }

    flagObstacleTree = true;
}

// End Obstacle Slots & Functions

// Robot Slots & Functions

void MainWindow::on_actionAddRobot_triggered()
{
    fileDialog->setFileMode(QFileDialog::ExistingFile);
    fileDialog->setFilters(filterXML);
    fileDialog->setOption(QFileDialog::DontUseNativeDialog,true);
    fileDialog->setAcceptMode(QFileDialog::AcceptOpen);
    fileDialog->setDirectory(QDir::currentPath() + "/../robots");

    if(fileDialog->exec())
    {
        Scene->addRobot(fileDialog->selectedFiles().at(0));
        updateRobotTree();
    }
}

void MainWindow::on_actionDeleteRobot_triggered()
{
    if(robotTree->selectedItems().count()>0)
    {
        if(QMessageBox::question(0,"DynaBOT::Robots::Question","Do you really want to delete this robot?", QMessageBox::Yes | QMessageBox::No) == QMessageBox::Yes)
        {
            int index;
            QTreeWidgetItem *parent = robotTree->selectedItems().at(0);

            while(parent->parent())
            {
                parent = parent->parent();
            }

            index = robotTree->indexOfTopLevelItem(parent);
            Scene->deleteRobot(index);
            updateRobotTree();
        }
    }
    else
    {
        QMessageBox::warning(0,"DynaBOT::Robots::Warning","There is no robot(s) selected to delete.");
    }
}

void MainWindow::on_actionResetRobot_triggered()
{
    if(robotTree->selectedItems().count()>0)
    {
        if(QMessageBox::question(0,"DynaBOT::Robots::Question","Do you really want to reset the location and rotation of the robot and its default joint values?", QMessageBox::Yes | QMessageBox::No) == QMessageBox::Yes)
        {
            int index;
            QTreeWidgetItem *parent = robotTree->selectedItems().at(0);

            while(parent->parent())
            {
                parent = parent->parent();
            }

            index = robotTree->indexOfTopLevelItem(parent);
            Scene->resetRobot(index);
            refreshRobotTree();
        }
    }
    else
    {
        QMessageBox::warning(0,"DynaBOT::Robots::Warning","There is no robot(s) selected to reset.");
    }
}

void MainWindow::on_robotTree_customContextMenuRequested(QPoint pos)
{
    obstacleTree->clearSelection();
    pathTree->clearSelection();

    QMenu menu(this);
    menu.addAction(actionAddRobot);

    QTreeWidgetItem *selItem = robotTree->itemAt(pos);

    if(selItem)
    {
        menu.addSeparator();
        menu.addAction(actionViewRobotDHTable);
        menu.addAction(actionAddRobotPath);

        if(robotTree->currentItem()->parent())
        {
            if(robotTree->currentItem()->parent()->parent())
            {
                if(robotTree->currentItem()->parent()->text(0) == "Paths" || robotTree->currentItem()->parent()->parent()->text(0) == "Paths")
                {
                    menu.addAction(actionDeleteRobotPath);
                }
            }
        }

        while(selItem->parent())
        {
            selItem = selItem->parent();
        }

        int robotIndex = robotTree->indexOfTopLevelItem(selItem);

        if(Scene->Robots[robotIndex]->nPaths > 0)
        menu.addAction(actionSetInitialSimulationConfiguration);

        menu.addSeparator();
        menu.addAction(actionResetRobot);
        menu.addAction(actionDeleteRobot);
    }
    else
    {
        robotTree->clearSelection();
    }

    menu.exec(robotTree->viewport()->mapToGlobal(pos));
}

void MainWindow::on_robotTree_itemChanged(QTreeWidgetItem* item, int column)
{
    if(flagRobotTree)
    {
        if(!item->parent()) // Setting the Robot's Name
        {
            // 0 Indicates that we're setting up the robot's name
            Scene->setRobotProp(0,item->text(0),robotTree->indexOfTopLevelItem(item));
            flagRobotTree = false;
            item->child(1)->child(0)->setText(1,item->text(0));
            flagRobotTree = true;
            if(graphWidget->widget() != label)
            {
                deletePlot();
                showPlot();
                setPlot();
            }
        }
        else
        {
            int robotIndex = robotTree->indexOfTopLevelItem(item->parent()->parent());
            int linkIndex = item->parent()->parent()->indexOfChild(item->parent()) - 1;

            QString value = item->text(1);
            value.chop(2);

            int updateFromIndex;

            if(linkIndex == -1) // If we're setting Robot's Loc/Rot because that items don't have text but X,Y,Z,RotX,RotY,RotZ Icons
            {
                if(Scene->Robots[robotIndex]->ikSolved)
                {
                    QMessageBox::warning(0,"DynaBOT::Robots::Information","Remember that if you change the location and/or rotation of a Robot, the Inverse Kinematics, Dynamics, and Simulation Data have to be erased and recomputed in another simulation.");
                    deletePlot();
                }

                // This is because X,Y,Z,RotX,RotY,RotZ are 0,1,2,3,4,5 and we actually need 1,2,3,4,5,6
                int prop = item->parent()->indexOfChild(item) + 1;
                Scene->setRobotProp(prop,value,robotIndex);
                updateFromIndex = 0;
            }
            else
            {
                Scene->setRobotLinkQ(value.toDouble(),robotIndex, linkIndex, true);
                updateFromIndex = linkIndex;
            }

            refreshRobotTree();
        }
    }
}

void MainWindow::updateRobotTree()
{

    deletePlot();

    flagRobotTree = false;
    robotTree->clear();
    bool anyPathExists = false;

    for (int i=0; i<Scene->Robots.length(); i++)
    {
        QTreeWidgetItem *actRobot = new QTreeWidgetItem(robotTree);
        QTreeWidgetItem *properties = new QTreeWidgetItem(actRobot);
        QTreeWidgetItem *x = new QTreeWidgetItem(properties);
        QTreeWidgetItem *y = new QTreeWidgetItem(properties);
        QTreeWidgetItem *z = new QTreeWidgetItem(properties);
        QTreeWidgetItem *rotX = new QTreeWidgetItem(properties);
        QTreeWidgetItem *rotY = new QTreeWidgetItem(properties);
        QTreeWidgetItem *rotZ = new QTreeWidgetItem(properties);

        actRobot->setText(0,Scene->Robots[i]->name);
        properties->setText(0,"Loc./Rot.");

        actRobot->setSizeHint(0,QSize(robotTree->columnWidth(0),24));
        actRobot->setSizeHint(1,QSize(robotTree->columnWidth(1),24));

        properties->setSizeHint(0,QSize(robotTree->columnWidth(0),24));
        properties->setSizeHint(1,QSize(robotTree->columnWidth(1),24));

        for(int j=0; j<properties->childCount(); j++)
        {
            properties->child(j)->setSizeHint(0,properties->sizeHint(0));
            properties->child(j)->setSizeHint(1,properties->sizeHint(1));
        }

        x->setIcon(0,QIcon(":/resources/icons/move_x.png"));
        y->setIcon(0,QIcon(":/resources/icons/move_y.png"));
        z->setIcon(0,QIcon(":/resources/icons/move_z.png"));
        rotX->setIcon(0,QIcon(":/resources/icons/rotate_x.png"));
        rotY->setIcon(0,QIcon(":/resources/icons/rotate_y.png"));
        rotZ->setIcon(0,QIcon(":/resources/icons/rotate_z.png"));

        actRobot->setFlags(actRobot->flags() | Qt::ItemIsEditable);
        x->setFlags(x->flags() | Qt::ItemIsEditable);
        y->setFlags(y->flags() | Qt::ItemIsEditable);
        z->setFlags(z->flags() | Qt::ItemIsEditable);
        rotX->setFlags(rotX->flags() | Qt::ItemIsEditable);
        rotY->setFlags(rotY->flags() | Qt::ItemIsEditable);
        rotZ->setFlags(rotZ->flags() | Qt::ItemIsEditable);

        x->setText(1,QString::number(Scene->Robots[i]->x) + " m");
        y->setText(1,QString::number(Scene->Robots[i]->y) + " m");
        z->setText(1,QString::number(Scene->Robots[i]->z) + " m");
        rotX->setText(1,QString::number(Scene->Robots[i]->rotX) + " °");
        rotY->setText(1,QString::number(Scene->Robots[i]->rotY) + " °");
        rotZ->setText(1,QString::number(Scene->Robots[i]->rotZ) + " °");

        for(int j=0; j<Scene->Robots[i]->nLinks; j++)
        {
            QTreeWidgetItem *actLink = new QTreeWidgetItem(actRobot);
            actLink->setText(0,Scene->Robots[i]->Links[j]->name);


            if(Scene->Robots[i]->Links[j]->parentId != -1)
            {
                QTreeWidgetItem *q       = new QTreeWidgetItem(actLink);

                if(Scene->Robots[i]->Links[j]->jointType == QDynLink::Prismatic)
                {
                    q->setText(0,"d");
                    q->setText(1,QString::number(Scene->Robots[i]->Links[j]->d) + " m");
                    q->setStatusTip(1,QString::number(Scene->Robots[i]->Links[j]->qMin) + " m :: " + QString::number(Scene->Robots[i]->Links[j]->qMax) + " m");
                }

                if(Scene->Robots[i]->Links[j]->jointType == QDynLink::Revolute)
                {
                    q->setText(0,thetaSymbol);
                    q->setText(1,QString::number(Scene->Robots[i]->Links[j]->theta) + " °");
                    q->setStatusTip(1,QString::number(Scene->Robots[i]->Links[j]->qMin) + " ° :: " + QString::number(Scene->Robots[i]->Links[j]->qMax) + " °");
                }

                q->setFlags(q->flags() | Qt::ItemIsEditable);
            }

            QTreeWidgetItem *pos  = new QTreeWidgetItem(actLink);
            QTreeWidgetItem *rpy  = new QTreeWidgetItem(actLink);

            pos->setText(0,"x :: y :: z");
            pos->setText(1,QDynGeneric::double2meters(Scene->Robots[i]->Links[j]->PLink[0]) + " :: " + QDynGeneric::double2meters(Scene->Robots[i]->Links[j]->PLink[1]) + " :: " + QDynGeneric::double2meters(Scene->Robots[i]->Links[j]->PLink[2]));

            rpy->setText(0,"R :: P :: Y");
            rpy->setText(1,QDynGeneric::double2degree(Scene->Robots[i]->Links[j]->roll) + " :: " + QDynGeneric::double2degree(Scene->Robots[i]->Links[j]->pitch) + " :: " + QDynGeneric::double2degree(Scene->Robots[i]->Links[j]->yaw));

            for(int j=0; j<actLink->childCount(); j++)
            {
                actLink->child(j)->setSizeHint(0,actLink->sizeHint(0));
                actLink->child(j)->setSizeHint(1,actLink->sizeHint(1));
            }
        }

        if(Scene->Robots[i]->nPaths > 0)
        {

            anyPathExists = true;

            QTreeWidgetItem *robotPaths = new QTreeWidgetItem(actRobot);
            robotPaths->setText(0,"Paths");
            for(int j=0; j<Scene->Robots[i]->nPaths; j++)
            {
                QTreeWidgetItem *actRobotPath = new QTreeWidgetItem(robotPaths);
                QTreeWidgetItem *qIni = new QTreeWidgetItem(actRobotPath);
                QTreeWidgetItem *speed = new QTreeWidgetItem(actRobotPath);
                QTreeWidgetItem *link = new QTreeWidgetItem(actRobotPath);

                actRobotPath->setText(0,Scene->Robots[i]->Paths[j]->path->name);

                qIni->setText(0,"Init. Cond.");

                if(j==0)
                {
                    QString qIniTxt = "";
                    for(int k=1; k<Scene->Robots[i]->nLinks; k++)
                    {
                        if(Scene->Robots[i]->Links[k]->jointType == QDynLink::Revolute)
                        qIniTxt += QDynGeneric::double2degree(Scene->Robots[i]->Paths[j]->qIni[k-1]);

                        if(Scene->Robots[i]->Links[k]->jointType == QDynLink::Prismatic)
                        qIniTxt += QDynGeneric::double2meters(Scene->Robots[i]->Paths[j]->qIni[k-1]);

                        if(k != (Scene->Robots[i]->nLinks-1))
                        qIniTxt += " :: ";
                    }

                    qIni->setText(1,qIniTxt);
                }

                else
                {
                    qIni->setText(1,"Defined by previous path end point." );
                }

                speed->setText(0,"App. Speed :: Path Speed");
                speed->setText(1,QDynGeneric::double2linspeed(Scene->Robots[i]->Paths[j]->approachSpeed) + " :: " + QDynGeneric::double2linspeed(Scene->Robots[i]->Paths[j]->speed));

                link->setText(0,"Followed by");
                link->setText(1,Scene->Robots[i]->Links[Scene->Robots[i]->Paths[j]->linkID]->name);
            }
        }
    }

    if(anyPathExists)
    actionStartSimulation->setEnabled(true);
    else
    actionStartSimulation->setDisabled(true);

    flagRobotTree = true;
}

void MainWindow::refreshRobotTree()
{
    flagRobotTree = false;
    for(int i=0; i<Scene->Robots.length(); i++)
    {
        for(int j=0; j<Scene->Robots[i]->nLinks; j++)
        {
            if(j==0)
            {
                robotTree->topLevelItem(i)->child(j+1)->child(0)->setText(1,QDynGeneric::double2meters(Scene->Robots[i]->Links[j]->PLink[0]) + " :: " + QDynGeneric::double2meters(Scene->Robots[i]->Links[j]->PLink[1]) + " :: " + QDynGeneric::double2meters(Scene->Robots[i]->Links[j]->PLink[2]));
                robotTree->topLevelItem(i)->child(j+1)->child(1)->setText(1,QDynGeneric::double2degree(Scene->Robots[i]->Links[j]->roll) + " :: " + QDynGeneric::double2degree(Scene->Robots[i]->Links[j]->pitch) + " :: " + QDynGeneric::double2degree(Scene->Robots[i]->Links[j]->yaw));
            }
            else
            {
                if(Scene->Robots[i]->Links[j]->jointType == QDynLink::Revolute)
                {
                    robotTree->topLevelItem(i)->child(j+1)->child(0)->setText(1,QDynGeneric::double2degree(Scene->Robots[i]->Links[j]->theta));
                }
                if(Scene->Robots[i]->Links[j]->jointType == QDynLink::Prismatic)
                {
                    robotTree->topLevelItem(i)->child(j+1)->child(0)->setText(1,QDynGeneric::double2meters(Scene->Robots[i]->Links[j]->d));
                }
                robotTree->topLevelItem(i)->child(j+1)->child(1)->setText(1,QDynGeneric::double2meters(Scene->Robots[i]->Links[j]->PLink[0]) + " :: " + QDynGeneric::double2meters(Scene->Robots[i]->Links[j]->PLink[1]) + " :: " + QDynGeneric::double2meters(Scene->Robots[i]->Links[j]->PLink[2]));
                robotTree->topLevelItem(i)->child(j+1)->child(2)->setText(1,QDynGeneric::double2degree(Scene->Robots[i]->Links[j]->roll) + " :: " + QDynGeneric::double2degree(Scene->Robots[i]->Links[j]->pitch) + " :: " + QDynGeneric::double2degree(Scene->Robots[i]->Links[j]->yaw));
            }
        }
        robotTree->topLevelItem(i)->child(0)->child(0)->setText(1,QDynGeneric::double2meters(Scene->Robots[i]->x));
        robotTree->topLevelItem(i)->child(0)->child(1)->setText(1,QDynGeneric::double2meters(Scene->Robots[i]->y));
        robotTree->topLevelItem(i)->child(0)->child(2)->setText(1,QDynGeneric::double2meters(Scene->Robots[i]->z));
        robotTree->topLevelItem(i)->child(0)->child(3)->setText(1,QDynGeneric::double2degree(Scene->Robots[i]->rotX));
        robotTree->topLevelItem(i)->child(0)->child(4)->setText(1,QDynGeneric::double2degree(Scene->Robots[i]->rotY));
        robotTree->topLevelItem(i)->child(0)->child(5)->setText(1,QDynGeneric::double2degree(Scene->Robots[i]->rotZ));
    }
    flagRobotTree = true;
}

// End of Robot Slots & Functions

void MainWindow::on_actionCollideAllLinks_triggered()
{
    Scene->setCollisionType(QDynScene::CollideAllLinks);
}

void MainWindow::on_actionCollideEndEffector_triggered()
{
    Scene->setCollisionType(QDynScene::CollideEndEffector);
}

void MainWindow::on_actionCollideNone_triggered()
{
    Scene->setCollisionType(QDynScene::CollideNone);
}

void MainWindow::on_actionAddPath_triggered()
{
//    pathDialog->show();
//    pathDialog->raise();
    pathDialog->openDialog();
}

void MainWindow::addPathFromFile(QString filename)
{
    Scene->addPath(filename);
    updatePathTree();
}

void MainWindow::addPathFromPoints(double xI,double yI, double zI, double xF, double yF, double zF, int n)
{
    Scene->addPath(xI,yI,zI,xF,yF,zF,n);
    updatePathTree();
}

void MainWindow::updatePathTree()
{
    flagPathTree = false;
    pathTree->clear();

    for (int i=0; i<Scene->Paths.length(); i++)
    {
        QTreeWidgetItem *actPath = new QTreeWidgetItem(pathTree);
        actPath->setText(0,Scene->Paths[i]->name);
        QTreeWidgetItem *nPoints  = new QTreeWidgetItem(actPath);
        QTreeWidgetItem *visible  = new QTreeWidgetItem(actPath);
        QTreeWidgetItem *pIni     = new QTreeWidgetItem(actPath);
        QTreeWidgetItem *pFin     = new QTreeWidgetItem(actPath);

        actPath->setSizeHint(0,QSize(pathTree->columnWidth(0),24));
        actPath->setSizeHint(1,QSize(pathTree->columnWidth(1),24));

        for(int j=0; j<actPath->childCount(); j++)
        {
            actPath->child(j)->setSizeHint(0,actPath->sizeHint(0));
            actPath->child(j)->setSizeHint(1,actPath->sizeHint(1));
        }

        actPath->setFlags(actPath->flags() | Qt::ItemIsEditable);
        visible->setCheckState(1,(Scene->Paths[i]->visible)? Qt::Checked : Qt::Unchecked );

        int n = Scene->Paths[i]->nPoints;

        nPoints->setText(0,"# Points");
        nPoints->setText(1,QString::number(n));

        visible->setText(0,"Visible");

        pIni->setText(0,"xIni::yIni::zIni");
        pIni->setText(1,QDynGeneric::double2meters(Scene->Paths[i]->points[0].pos[0]) + " :: " +
                        QDynGeneric::double2meters(Scene->Paths[i]->points[0].pos[1]) + " :: " +
                        QDynGeneric::double2meters(Scene->Paths[i]->points[0].pos[2]));



        pFin->setText(0,"xFin::yFin::zFin");
        pFin->setText(1,QDynGeneric::double2meters(Scene->Paths[i]->points[n-1].pos[0]) + " :: " +
                        QDynGeneric::double2meters(Scene->Paths[i]->points[n-1].pos[1]) + " :: " +
                        QDynGeneric::double2meters(Scene->Paths[i]->points[n-1].pos[2]));
    }
    flagPathTree = true;
}

void MainWindow::on_pathTree_itemChanged(QTreeWidgetItem* item, int column)
{
    if(flagPathTree)
    {
        if(!item->parent())
        {
            int index = pathTree->indexOfTopLevelItem(item);
            bool updateNeeded = false;

            Scene->setPathProperties(0,item->text(0),index);

            for(int i=0; i<Scene->Robots.length(); i++)
            {
                for(int j=0; j<Scene->Robots[i]->nPaths; j++)
                {
                    if(Scene->Robots[i]->Paths[j]->path == Scene->Paths[index])
                    updateNeeded = true;
                }
            }

            if(updateNeeded)
            updateRobotTree();
        }
        else
        {
            Scene->setPathProperties(1,((item->checkState(1) == Qt::Checked) ? true : false) ,pathTree->indexOfTopLevelItem(item->parent()));
        }
    }
}

void MainWindow::on_robotTree_clicked(QModelIndex index)
{
    obstacleTree->clearSelection();
    pathTree->clearSelection();
}

void MainWindow::on_obstacleTree_clicked(QModelIndex index)
{
    robotTree->clearSelection();
    pathTree->clearSelection();
}

void MainWindow::on_pathTree_clicked(QModelIndex index)
{
    robotTree->clearSelection();
    obstacleTree->clearSelection();
}

void MainWindow::on_pathTree_customContextMenuRequested(QPoint pos)
{
    obstacleTree->clearSelection();
    robotTree->clearSelection();

    QMenu menu(this);
    menu.addAction(actionAddPath);

    QTreeWidgetItem *selItem = pathTree->itemAt(pos);

    if(selItem)
    {
        menu.addSeparator();
        menu.addAction(actionDeletePath);
    }
    else
    {
        pathTree->clearSelection();
    }

    menu.exec(pathTree->viewport()->mapToGlobal(pos));
}

void MainWindow::on_actionDeletePath_triggered()
{
    if(pathTree->selectedItems().count()>0)
    {
        if(QMessageBox::question(0,"DynaBOT::Paths::Question","Do you really want to delete this path?.<br> All robot paths depending on this will be deleted too.", QMessageBox::Yes | QMessageBox::No) == QMessageBox::Yes)
        {
            int index;
            if(pathTree->currentItem()->parent())
            {
                index = pathTree->indexOfTopLevelItem(pathTree->currentItem()->parent());
            }
            else
            {
                index = pathTree->indexOfTopLevelItem(pathTree->currentItem());
            }
            Scene->deletePath(index);
            updatePathTree();
            updateRobotTree();
        }
    }
    else
    {
        QMessageBox::warning(0,"DynaBOT::Paths::Warning","There is no paths selected to delete.");
    }
}

void MainWindow::addRobotPath(int robotIndex, int pathNumber, int linkNumber, double approachSpeed, double speed)
{
    Scene->addRobotPath(robotIndex, Scene->Paths[pathNumber], linkNumber, approachSpeed, speed);
    updateRobotTree();
}

void MainWindow::on_actionAddRobotPath_triggered()
{
    if(robotTree->selectedItems().count()>0)
    {
        if(Scene->Paths.length() > 0)
        {
            QTreeWidgetItem *item = robotTree->currentItem();
            while(item->parent())
            {
                item = item->parent();
            }
            int robotIndex = robotTree->indexOfTopLevelItem(item);
            robotPathDialog->showDialog(Scene->Robots[robotIndex], robotIndex ,Scene->Paths);
        }
        else
        {
            QMessageBox::warning(0,"DynaBOT::Paths::Warning","The scene doesn't have any paths defined.");
        }
    }
    else
    {
        QMessageBox::warning(0,"DynaBOT::Robots::Warning","There is no robot selected to add a path to be followed.");
    }
}

void MainWindow::on_actionDeleteRobotPath_triggered()
{
    QTreeWidgetItem *path = robotTree->currentItem();
    QTreeWidgetItem *actRobot = robotTree->currentItem();

    while(actRobot->parent())
    {
        actRobot = actRobot->parent();
    }
    if(robotTree->currentItem()->parent()->text(0) == "Paths")
    {
        // If a path is selected
        path = robotTree->currentItem();

    }
    else if(robotTree->currentItem()->parent()->parent()->text(0) == "Paths")
    {
        // If a path property is selected
        path = robotTree->currentItem()->parent();
    }

    if(QMessageBox::question(0,"DynaBOT::Robots::Question","Do you really want to delete this robot path?", QMessageBox::Yes | QMessageBox::No) == QMessageBox::Yes)
    {
        int robotPathIndex = path->parent()->indexOfChild(path);
        int robotIndex = robotTree->indexOfTopLevelItem(actRobot);

        Scene->deleteRobotPath(robotIndex,robotPathIndex);
        updateRobotTree();
    }
}

void MainWindow::on_actionStartSimulation_triggered()
{
    if(Scene->simStarted)
    Scene->resumeSimulation();
    else
    {
        Scene->startSimulation();
        robotTree->clearSelection();
        obstacleTree->clearSelection();
        pathTree->clearSelection();
    }

}

void MainWindow::on_actionStopSimulation_triggered()
{
    Scene->stopSimulation();
}

void MainWindow::on_actionPauseSimulation_triggered()
{
    Scene->pauseSimulation();
}

void MainWindow::simulationStarted()
{
    actionStopSimulation->setEnabled(true);
    actionStartSimulation->setDisabled(true);
    actionStartSimulation->setText("Resume Simulation");
    actionStartSimulation->setToolTip("Resumes the current running Simulation");

    robotTree->setDisabled(true);
    obstacleTree->setDisabled(true);
    pathTree->setDisabled(true);

    actionNewScene->setDisabled(true);
    actionLoadScene->setDisabled(true);
    actionSaveScene->setDisabled(true);

    actionAddObstacle->setDisabled(true);
    actionOpenRobotCreator->setDisabled(true);
    actionAddRobot->setDisabled(true);
    actionAddPath->setDisabled(true);
    actionAddRobotPath->setDisabled(true);

    actionToggleBlend->setDisabled(true);
    actionToggleGlobalAxis->setDisabled(true);
    actionToggleGrid->setDisabled(true);
    actionToggleLocalAxes->setDisabled(true);
    actionToggleObjectCoordinates->setDisabled(true);
    actionResetCamera->setDisabled(true);
    actionCollideAllLinks->setDisabled(true);
    actionCollideEndEffector->setDisabled(true);
    actionCollideNone->setDisabled(true);

    statusProgress->show();
    robotTree->collapseAll();
}

void MainWindow::simulationStopped()
{
    actionStopSimulation->setDisabled(true);
    actionPauseSimulation->setDisabled(true);
    actionStartSimulation->setEnabled(true);

    robotTree->setEnabled(true);
    obstacleTree->setEnabled(true);
    pathTree->setEnabled(true);

    actionNewScene->setEnabled(true);
    actionLoadScene->setEnabled(true);
    actionSaveScene->setEnabled(true);

    actionAddObstacle->setEnabled(true);
    actionOpenRobotCreator->setEnabled(true);
    actionAddRobot->setEnabled(true);
    actionAddPath->setEnabled(true);
    actionAddRobotPath->setEnabled(true);
    actionStartSimulation->setToolTip("Starts the Simulation for all Robots in the Scene");

    actionToggleBlend->setEnabled(true);
    actionToggleGlobalAxis->setEnabled(true);
    actionToggleGrid->setEnabled(true);
    actionToggleLocalAxes->setEnabled(true);
    actionToggleObjectCoordinates->setEnabled(true);
    actionResetCamera->setEnabled(true);
    actionCollideAllLinks->setEnabled(true);
    actionCollideEndEffector->setEnabled(true);
    actionCollideNone->setEnabled(true);
    statusMessage->setText("");
    statusProgress->hide();
    refreshRobotTree();
}

void MainWindow::simulationPaused()
{
    actionPauseSimulation->setDisabled(true);
    actionStartSimulation->setEnabled(true);
}

void MainWindow::simulationRunning()
{
    actionPauseSimulation->setEnabled(true);
    actionStartSimulation->setDisabled(true);

    if(graphWidget->widget() == label)
    {
        showPlot();
        setPlot();
    }

    actionToggleBlend->setEnabled(true);
    actionToggleGlobalAxis->setEnabled(true);
    actionToggleGrid->setEnabled(true);
    actionToggleLocalAxes->setEnabled(true);
    actionToggleObjectCoordinates->setEnabled(true);
    actionResetCamera->setEnabled(true);
    actionCollideAllLinks->setEnabled(true);
    actionCollideEndEffector->setEnabled(true);
    actionCollideNone->setEnabled(true);
}

void MainWindow::processUpdated(QString process, int percentage)
{
    statusMessage->setText(process + ":");
    statusProgress->setValue(percentage);
}

void MainWindow::on_actionSetInitialSimulationConfiguration_triggered()
{
    QTreeWidgetItem *item = robotTree->currentItem();

    while(item->parent())
    item = item->parent();

    Scene->setInitialPathConfig(robotTree->indexOfTopLevelItem(item));
    refreshRobotTree();
}

void MainWindow::deletePlot()
{
    cleaningPlot = true;

    if(graphWidget->widget() != label)
    {
        if(plotJointRefData)
        {
            plotGrid->detach();
            plotJointRefData->detach();
            plotJointSimData->detach();

            delete plotGrid;
            delete plotJointRefData;
            delete plotJointSimData;
        }

        plotJointRefData    = new QwtPlotCurve("Joint References");
        plotJointSimData    = new QwtPlotCurve("Joint Dynamic Response");
        plotGrid            = new QwtPlotGrid;

        plotGrid->enableXMin(true);
        plotGrid->setMajPen(QPen(Qt::gray, 0, Qt::DotLine));
        plotGrid->setMinPen(QPen(Qt::gray, 0 , Qt::DotLine));

//        plotJointRefData->setCurveAttribute(QwtPlotCurve::Fitted);
//        plotJointRefData->setRenderHint(QwtPlotItem::RenderAntialiased);
        plotJointRefData->setPen(QColor(Qt::darkGreen));
        plotJointRefData->setStyle(QwtPlotCurve::Lines);

//        plotJointSimData->setCurveAttribute(QwtPlotCurve::Fitted);
//        plotJointSimData->setRenderHint(QwtPlotItem::RenderAntialiased);
        plotJointSimData->setPen(QColor(Qt::darkGreen));
        plotJointSimData->setStyle(QwtPlotCurve::Lines);

        plotComboRobot->clear();
        plotComboJoint->clear();
        plotComboTypes->clear();
        plotDynResponse->setChecked(false);

        plotDummyWidget->hide();
        plotDummyWidget->setParent(this);
        graphWidget->setWidget(label);
        graphWidget->setMinimumHeight(60);
        graphWidget->setMinimumWidth(80);
    }

    cleaningPlot = false;
}

void MainWindow::showPlot()
{
    if(graphWidget->widget() == label)
    graphWidget->setWidget(plotDummyWidget);
}

void MainWindow::setPlot()
{
    settingCombo = true;

    for(int k=0; k<Scene->Robots.length(); k++)
    {
        if(Scene->Robots[k]->ikSolved)
        {
            plotComboRobot->addItem(Scene->Robots[k]->name,k);
        }
    }

    int indFirst = plotComboRobot->itemData(0).toInt();

    for(int i=1; i<Scene->Robots[indFirst]->nLinks; i++)
    {
        plotComboJoint->addItem(Scene->Robots[indFirst]->Links[i]->name);
    }

    if(Scene->Robots[indFirst]->Links[1]->jointType == QDynLink::Revolute)
    {
        plotComboTypes->addItem("Joint Value - " + thetaSymbol);
        plotComboTypes->addItem("Joint Speed - " + derivSymbol + thetaSymbol + "/" + derivSymbol + "t");
        plotComboTypes->addItem("Joint Accel - " + derivSymbol + "²" + thetaSymbol + "/" + derivSymbol + "t²");
        plotComboTypes->addItem("Joint Torque - " + tauSymbol);
    }
    if(Scene->Robots[indFirst]->Links[1]->jointType == QDynLink::Prismatic)
    {
        plotComboTypes->addItem("Joint Value - d");
        plotComboTypes->addItem("Joint Speed - " + derivSymbol + "d/" + derivSymbol + "t");
        plotComboTypes->addItem("Joint Accel - " + derivSymbol + "²d/" + derivSymbol + "t²");
        plotComboTypes->addItem("Joint Force - " + tauSymbol);
    }

    settingCombo = false;

    updatePlot();
}

void MainWindow::updatePlot()
{
    int actRobot = plotComboRobot->itemData(plotComboRobot->currentIndex()).toInt();
    int actLink  = plotComboJoint->currentIndex();
    int actGraph = plotComboTypes->currentIndex();

    plotGrid->detach();
    plotJointRefData->detach();
    plotJointSimData->detach();
    plot->setAxisTitle(QwtPlot::xBottom, "t(s)");
    QString plotTitle = "";
    switch(actGraph)
    {
        case 0:
        plotJointRefData->setRawSamples(Scene->Robots[actRobot]->tAcu,Scene->Robots[actRobot]->qRef[actLink],Scene->Robots[actRobot]->nPoints);
        plotJointRefData->attach(plot);
        plotTitle += Scene->Robots[actRobot]->name + " - " + Scene->Robots[actRobot]->Links[actLink+1]->name + " - Joint Position";
        plot->setTitle(plotTitle);
        plot->setAxisTitle(QwtPlot::yLeft,((Scene->Robots[actRobot]->Links[actLink+1]->jointType == QDynLink::Revolute ) ? thetaSymbol + " [°]" : "d [m]" ));
        break;

        case 1:
        plotJointRefData->setRawSamples(Scene->Robots[actRobot]->tAcu,Scene->Robots[actRobot]->qDot[actLink],Scene->Robots[actRobot]->nPoints);
        plotJointRefData->attach(plot);
        plotTitle += Scene->Robots[actRobot]->name + " - " + Scene->Robots[actRobot]->Links[actLink+1]->name + " - Joint Speed";
        plot->setTitle(plotTitle);
        plot->setAxisTitle(QwtPlot::yLeft,((Scene->Robots[actRobot]->Links[actLink+1]->jointType == QDynLink::Revolute ) ? derivSymbol + thetaSymbol + "/" + derivSymbol + "t [°/s]" : derivSymbol + "d/" + derivSymbol + "t [m/s]"));
        break;

        case 2:
        plotJointRefData->setRawSamples(Scene->Robots[actRobot]->tAcu,Scene->Robots[actRobot]->qDotDot[actLink],Scene->Robots[actRobot]->nPoints);
        plotJointRefData->attach(plot);
        plotTitle += Scene->Robots[actRobot]->name + " - " + Scene->Robots[actRobot]->Links[actLink+1]->name + " - Joint Accel.";
        plot->setTitle(plotTitle);
        plot->setAxisTitle(QwtPlot::yLeft,((Scene->Robots[actRobot]->Links[actLink+1]->jointType == QDynLink::Revolute ) ? derivSymbol + "²" + thetaSymbol + "/" + derivSymbol + "t² [°/s²]" : derivSymbol + "²d/" + derivSymbol + "t² [m/s²]"));
        break;

        case 3:
        plotJointRefData->setRawSamples(Scene->Robots[actRobot]->tAcu,Scene->Robots[actRobot]->qTorque[actLink],Scene->Robots[actRobot]->nPoints);
        plotJointRefData->attach(plot);
        plotTitle += Scene->Robots[actRobot]->name + " - " + Scene->Robots[actRobot]->Links[actLink+1]->name + " - " + ((Scene->Robots[actRobot]->Links[actLink+1]->jointType == QDynLink::Revolute)? "Joint Torque" : "Joint Force");
        plot->setTitle(plotTitle);
        plot->setAxisTitle(QwtPlot::yLeft,((Scene->Robots[actRobot]->Links[actLink+1]->jointType == QDynLink::Revolute ) ? tauSymbol + " [N·m]" : "F [N]" ));
        break;
    }
    plotGrid->attach(plot);
    plot->replot();
}

void MainWindow::on_plotComboRobot_currentIndexChanged(int index)
{
    if(settingCombo || cleaningPlot)
    return;

    settingCombo = true;
    plotComboTypes->clear();
    plotComboJoint->clear();

    // Populate Joints Combo

    int selRobot = plotComboRobot->itemData(index).toInt();

    for(int i=1; i<Scene->Robots[selRobot]->nLinks; i++)
    {
        plotComboJoint->addItem(Scene->Robots[selRobot]->Links[i]->name);
    }

    // Populate Graph Types Combo

    if(Scene->Robots[selRobot]->Links[1]->jointType == QDynLink::Revolute)
    {
        plotComboTypes->addItem("Joint Value - " + thetaSymbol);
        plotComboTypes->addItem("Joint Speed - " + derivSymbol + thetaSymbol + "/" + derivSymbol + "t");
        plotComboTypes->addItem("Joint Accel - " + derivSymbol + "²" + thetaSymbol + "/" + derivSymbol + "t²");
        plotComboTypes->addItem("Joint Torque - " + tauSymbol);
    }
    if(Scene->Robots[selRobot]->Links[1]->jointType == QDynLink::Prismatic)
    {
        plotComboTypes->addItem("Joint Value - d");
        plotComboTypes->addItem("Joint Speed - " + derivSymbol + "d/" + derivSymbol + "t");
        plotComboTypes->addItem("Joint Accel - " + derivSymbol + "²d/" + derivSymbol + "t²");
        plotComboTypes->addItem("Joint Force - F");
    }

    settingCombo = false;

    updatePlot();
}

void MainWindow::on_plotComboJoint_currentIndexChanged(int index)
{
    if(settingCombo || cleaningPlot)
    return;

    settingCombo = true;
    int actGraphType = plotComboTypes->currentIndex();
    plotComboTypes->clear();

    int selRobot = plotComboRobot->itemData( plotComboRobot->currentIndex()).toInt();

    // Populate Graph Types Combo
    if(Scene->Robots[selRobot]->Links[index+1]->jointType == QDynLink::Revolute)
    {
        plotComboTypes->addItem("Joint Value - " + thetaSymbol);
        plotComboTypes->addItem("Joint Speed - " + derivSymbol + thetaSymbol + "/" + derivSymbol + "t");
        plotComboTypes->addItem("Joint Accel - " + derivSymbol + "²" + thetaSymbol + "/" + derivSymbol + "t²");
        plotComboTypes->addItem("Joint Torque - " + tauSymbol);
    }
    if(Scene->Robots[selRobot]->Links[index+1]->jointType == QDynLink::Prismatic)
    {
        plotComboTypes->addItem("Joint Value - d");
        plotComboTypes->addItem("Joint Speed - " + derivSymbol + "d/" + derivSymbol + "t");
        plotComboTypes->addItem("Joint Accel - " + derivSymbol + "²d/" + derivSymbol + "t²");
        plotComboTypes->addItem("Joint Force - F");
    }

    if(actGraphType >= 0)
    plotComboTypes->setCurrentIndex(actGraphType);

    settingCombo = false;
    updatePlot();
}

void MainWindow::on_plotComboTypes_currentIndexChanged(int index)
{
    if(settingCombo || cleaningPlot)
    return;

    updatePlot();
}

void MainWindow::on_actionNewScene_triggered()
{
    if(QMessageBox::question(0,"DynaBOT::Scene::Question","Do you really want to reset the Scene?", QMessageBox::Yes | QMessageBox::No) == QMessageBox::Yes)
    {
        Scene->resetScene();
        updateRobotTree();
        updateObstacleTree();
        updatePathTree();
    }
}

void MainWindow::plotContextMenu(QPoint pos)
{
    robotTree->clearSelection();
    obstacleTree->clearSelection();
    pathTree->clearSelection();

    QMenu menu(this);
    menu.addAction(actionExportJointData);
    menu.addAction(actionExportGraph);

    menu.exec(plot->mapToGlobal(pos));
}

void MainWindow::on_actionExportJointData_triggered()
{
    fileDialog->setFileMode(QFileDialog::AnyFile);
    fileDialog->setFilters(filterCSV);
    fileDialog->setOption(QFileDialog::DontConfirmOverwrite,false);
    fileDialog->setDirectory(QDir::currentPath() + "/../savedata");
    fileDialog->setAcceptMode(QFileDialog::AcceptSave);
    fileDialog->setDefaultSuffix("csv");

    if(fileDialog->exec())
    {
        QString fileName = static_cast<QString>(fileDialog->selectedFiles().at(0));

        if(!fileName.isNull())
        {

            int actRobot = plotComboRobot->itemData(plotComboRobot->currentIndex()).toInt();
            int actLink  = plotComboJoint->currentIndex();
            QFile *file = new QFile(fileName);
            file->open(QIODevice::WriteOnly | QIODevice::Text);
            QTextStream out(file);

            if(Scene->Robots[actRobot]->Links[actLink]->jointType == QDynLink::Revolute)
            out << "t(s),Joint Value - q [°],Joint Speed - dq/dt [°/s],Joint Accel - d²q/dt² [°/s²],Joint Torque - N [N·m]\n";

            if(Scene->Robots[actRobot]->Links[actLink]->jointType == QDynLink::Prismatic)
            out << "t(s),Joint Value - q [m],Joint Speed - dq/dt [m/s],Joint Accel - d²q/dt² [m/s²],Joint Force - F [N]\n";

            QString actLine = "";

            for(int i=0; i<Scene->Robots[actRobot]->nPoints; i++)
            {
                actLine = "";
                actLine += QString::number(Scene->Robots[actRobot]->tAcu[i]).replace(",",".") + ",";
                actLine += QString::number(Scene->Robots[actRobot]->qRef[actLink][i]).replace(",",".") + ",";
                actLine += QString::number(Scene->Robots[actRobot]->qDot[actLink][i]).replace(",",".") + ",";
                actLine += QString::number(Scene->Robots[actRobot]->qDotDot[actLink][i]).replace(",",".") + ",";
                actLine += QString::number(Scene->Robots[actRobot]->qTorque[actLink][i]).replace(",",".") + "\n";
                out << actLine;
            }

            file->close();
            delete file;
        }
    }
}

void MainWindow::on_actionExportGraph_triggered()
{

    int actRobot = plotComboRobot->itemData(plotComboRobot->currentIndex()).toInt();
    int actLink  = plotComboJoint->currentIndex();
    int actGraph = plotComboTypes->currentIndex();

    QString graphType = "";

    switch(actGraph)
    {
        case 0:
        graphType += "Joint Value - q [";
        graphType += (Scene->Robots[actRobot]->Links[actLink]->jointType == QDynLink::Revolute) ? "°" : "m";
        graphType +=  "]";
        break;

        case 1:
        graphType += "Joint Speed - dq/dt [";
        graphType += (Scene->Robots[actRobot]->Links[actLink]->jointType == QDynLink::Revolute) ? "°" : "m";
        graphType += "/s]";
        break;

        case 2:
        graphType += "Joint Accel - d²q/dt² [";
        graphType += (Scene->Robots[actRobot]->Links[actLink]->jointType == QDynLink::Revolute) ? "°" : "m";
        graphType += "/s²]";
        break;

        case 3:
        graphType += "Joint ";
        graphType += (Scene->Robots[actRobot]->Links[actLink]->jointType == QDynLink::Revolute) ? "Torque - N [N·m" : "Force - F [N";
        graphType += "]";
        break;
    }

    #ifndef QT_NO_PRINTER
    QString fileName = Scene->Robots[actRobot]->name + " - " + Scene->Robots[actRobot]->Links[actLink+1]->name + " - " + graphType + ".pdf";
    #else
    QString fileName = Scene->Robots[actRobot]->name + " - " + Scene->Robots[actRobot]->Links[actLink+1]->name + " - " + graphType + ".png";
    #endif

    #ifndef QT_NO_FILEDIALOG
    const QList<QByteArray> imageFormats = QImageWriter::supportedImageFormats();

    QStringList filter;
    filter += "PDF Documents (*.pdf)";
    #ifndef QWT_NO_SVG
    filter += "SVG Documents (*.svg)";
    #endif
    filter += "Postscript Documents (*.ps)";

    if ( imageFormats.size() > 0 )
    {
        QString imageFilter("Images (");
        for ( int i = 0; i < imageFormats.size(); i++ )
        {
            if ( i > 0 )
            imageFilter += " ";

            imageFilter += "*.";
            imageFilter += imageFormats[i];
        }
        imageFilter += ")";

        filter += imageFilter;
    }

    #endif

    fileDialog->setFileMode(QFileDialog::AnyFile);
    fileDialog->setFilters(filter);
    fileDialog->setOption(QFileDialog::DontConfirmOverwrite,false);
    fileDialog->setDirectory(QDir::currentPath() + "/../savedata");
    fileDialog->setAcceptMode(QFileDialog::AcceptSave);

    if(fileDialog->exec())
    {
        fileName = static_cast<QString>(fileDialog->selectedFiles().at(0));

        if(!fileName.isEmpty())
        {
            QwtPlotRenderer renderer;

            // flags to make the document look like the widget
            renderer.setDiscardFlag(QwtPlotRenderer::DiscardBackground, false);
            renderer.setLayoutFlag(QwtPlotRenderer::KeepFrames, true);

            // First we have to set font sizes bigger than actual in order to get a nice-looking image file
            QFont smallFont("Segoe UI",8,QFont::StyleNormal);
            QFont bigFont("Segoe UI",12,QFont::StyleNormal);

            QwtText title = plot->title();
            QwtText xTitle = plot->axisTitle(QwtPlot::xBottom);
            QwtText yTitle = plot->axisTitle(QwtPlot::yLeft);

            title.setFont(bigFont);
            xTitle.setFont(bigFont);
            yTitle.setFont(bigFont);
            plot->setAxisFont(QwtPlot::xBottom,bigFont);
            plot->setAxisFont(QwtPlot::yLeft,bigFont);

            plot->setTitle(title);
            plot->setAxisTitle(QwtPlot::xBottom, xTitle);
            plot->setAxisTitle(QwtPlot::yLeft, yTitle);

            // Set the white background visible to render the file
            plot->setAutoFillBackground(true);

            // Here we render the plot with the white background
            renderer.renderDocument(plot, fileName, QSizeF(300, 200), 85);

            // Set the white background invisible again
            plot->setAutoFillBackground(false);

            // Set again the small fonts to view correctly the graph in the graph window
            title.setFont(smallFont);
            xTitle.setFont(smallFont);
            yTitle.setFont(smallFont);
            plot->setAxisFont(QwtPlot::xBottom,smallFont);
            plot->setAxisFont(QwtPlot::yLeft,smallFont);

            plot->setTitle(title);
            plot->setAxisTitle(QwtPlot::xBottom, xTitle);
            plot->setAxisTitle(QwtPlot::yLeft, yTitle);

            Scene->setFocus();

        }
    }
}

void MainWindow::on_actionViewRobotDHTable_triggered()
{
    QTreeWidgetItem *selItem = robotTree->currentItem();

    while(selItem->parent())
    {
        selItem = selItem->parent();
    }

    int actRobot = robotTree->indexOfTopLevelItem(selItem);

    robotTableDialog->openDialog(Scene->Robots[actRobot]);
}

void MainWindow::on_actionOpenRobotCreator_triggered()
{
    robotTableDialog->openDialog(0);
}

void MainWindow::on_robotTree_itemSelectionChanged()
{
    if(robotTree->selectedItems().count() == 0)
    {
        for(int k=0; k<Scene->Robots.length(); k++)
        {
            Scene->Robots[k]->selectedLink = -1;
            Scene->Robots[k]->isSelected = false;
        }
        Scene->updateGL();
    }
    else
    {

        int actRobot,actLink;
        QTreeWidgetItem *selItem = robotTree->selectedItems()[0];

        if(!selItem->parent())
        {
            for(int i=0; i<Scene->Robots.length(); i++)
            {
                Scene->Robots[i]->selectedLink = -1;
                Scene->Robots[i]->isSelected = false;
            }
            Scene->Robots[robotTree->indexOfTopLevelItem(selItem)]->isSelected = true;
        }
        else
        {
            while(selItem->parent()->parent())
            {
                selItem = selItem->parent();
            }

            actRobot = robotTree->indexOfTopLevelItem(selItem->parent());
            actLink = selItem->parent()->indexOfChild(selItem);
            if(actLink == 0 || selItem->text(0) == "Paths")
            actLink = -1;
            else
            actLink -= 1;

            for(int i=0; i<Scene->Robots.length(); i++)
            {
                if(i==actRobot)
                {
                    Scene->Robots[actRobot]->selectedLink = actLink;

                    if(actLink == -1)
                    Scene->Robots[actRobot]->isSelected = true;
                    else
                    Scene->Robots[actRobot]->isSelected = false;

                }
                else
                {
                    Scene->Robots[i]->selectedLink = -1;
                    Scene->Robots[i]->isSelected = false;
                }
            }
        }

        Scene->updateGL();

    }
}
