#include "QDynDialogRobotTable.h"

QDynDialogRobotTable::QDynDialogRobotTable(QWidget *parent) : QDialog(parent)
{
    setupUi(this);
    QDynRobotTableDelegate *robotTableDelegate = new QDynRobotTableDelegate(robotTable);
    this->robotTable->setItemDelegate(robotTableDelegate);
    connect(robotTableDelegate,SIGNAL(jointChanged(int)),this,SLOT(jointChanged(int)));
    filterXML << "XML Files (*.xml)";
    filterXML << "All files (*.*)";
}

QDynDialogRobotTable::~QDynDialogRobotTable()
{

}

void QDynDialogRobotTable::openDialog(QDynRobot *robot)
{

    QTableWidgetItem *baseItem = new QTableWidgetItem();
    QTableWidgetItem *tableItem;
    baseItem->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled | Qt::ItemIsEditable);
    robotTable->clearContents();

    settingTable = true;

    if(robot == 0)
    {
        if(this->isHidden())
        robotName->setText("New Robot");
        robotTable->setRowCount(1);
        this->setWindowTitle("SIMUNROBOT v2.0 :: Robot Creator");

        for(int j=0; j<11; j++)
        {
            tableItem = baseItem->clone();
            robotTable->setItem(0,j,tableItem);
        }

        robotTable->item(0,0)->setText("Link0");
        robotTable->item(0,1)->setText("None");
        robotTable->item(0,1)->setData(Qt::StatusTipRole,-1);
        robotTable->item(0,2)->setText("Revolute");
        robotTable->item(0,3)->setText(QDynGeneric::double2meters(0));
        robotTable->item(0,4)->setText(QDynGeneric::double2degree(0));
        robotTable->item(0,5)->setText(QDynGeneric::double2meters(0));
        robotTable->item(0,6)->setText(QDynGeneric::double2degree(0));
        robotTable->item(0,7)->setText(QDynGeneric::double2degree(0));
        robotTable->item(0,8)->setText(QDynGeneric::double2degree(0));
        robotTable->item(0,9)->setText(QDynGeneric::double2degree(0));
        robotTable->item(0,10)->setText(QDynGeneric::double2kilogram(1));
    }
    else
    {
        robotName->setText(robot->name);
        robotTable->setRowCount(robot->nLinks);
        this->setWindowTitle("DH Table for: " + robot->name);

        for(int i=0; i<robot->nLinks; i++)
        {
            for(int j=0; j<11; j++)
            {
                tableItem = baseItem->clone();
                robotTable->setItem(i,j,tableItem);
            }

            robotTable->item(i,0)->setText(robot->Links[i]->name);
            robotTable->item(i,1)->setText( (i==0)? "None" : robot->Links[robot->Links[i]->parentId]->name);
            robotTable->item(i,1)->setData(Qt::StatusTipRole,robot->Links[i]->parentId);
            robotTable->item(i,2)->setText((robot->Links[i]->jointType == QDynLink::Revolute)? "Revolute" : "Prismatic");
            robotTable->item(i,3)->setText(QDynGeneric::double2meters(robot->Links[i]->a));
            robotTable->item(i,4)->setText(QDynGeneric::double2degree(robot->Links[i]->alpha));
            robotTable->item(i,5)->setText(QDynGeneric::double2meters(robot->Links[i]->d));
            robotTable->item(i,6)->setText(QDynGeneric::double2degree(robot->Links[i]->theta));
            robotTable->item(i,7)->setText(QDynGeneric::double2degree(robot->Links[i]->plusTheta));

            if(robot->Links[i]->jointType == QDynLink::Revolute)
            {
                robotTable->item(i,8)->setText(QDynGeneric::double2degree(robot->Links[i]->qMin));
                robotTable->item(i,9)->setText(QDynGeneric::double2degree(robot->Links[i]->qMax));
            }

            if(robot->Links[i]->jointType == QDynLink::Prismatic)
            {
                robotTable->item(i,8)->setText(QDynGeneric::double2meters(robot->Links[i]->qMin));
                robotTable->item(i,9)->setText(QDynGeneric::double2meters(robot->Links[i]->qMax));
            }

            robotTable->item(i,10)->setText(QDynGeneric::double2kilogram(robot->Links[i]->mass));
        }
    }
    settingTable = false;

    if(this->isHidden())
    this->show();
}

void QDynDialogRobotTable::setFileDialog(QFileDialog *dialog)
{
    this->fileDialog = dialog;
}

void QDynDialogRobotTable::jointChanged(int row)
{
    // When we change a joint type into the DH table we have to change the qMin and qMax units and obviously reset them to zero
    if(robotTable->item(row,2)->text() == "Revolute")
    {
        robotTable->item(row,8)->setText("0 °");
        robotTable->item(row,9)->setText("0 °");
    }
    if(robotTable->item(row,2)->text() == "Prismatic")
    {
        robotTable->item(row,8)->setText("0 m");
        robotTable->item(row,9)->setText("0 m");
    }

}

void QDynDialogRobotTable::on_save_clicked()
{
    // Save the actual DH Table into a XML file
    fileDialog->setFileMode(QFileDialog::AnyFile);
    fileDialog->setFilters(filterXML);
    fileDialog->setOption(QFileDialog::DontConfirmOverwrite,false);
    fileDialog->setDirectory(QDir::currentPath() + "/../robots");
    fileDialog->setAcceptMode(QFileDialog::AcceptSave);
    fileDialog->setDefaultSuffix("xml");

    if(fileDialog->exec())
    {
        QString fileName = static_cast<QString>(fileDialog->selectedFiles().at(0));

        if(!fileName.isNull())
        {
            QFile *file = new QFile(fileName);
            file->open(QIODevice::WriteOnly | QIODevice::Text);
            QTextStream out(file);

            out << "<Robot>\n";
            out << "\t<Name>" << robotName->text() << "</Name>\n";
            out << "\t<Links>\n";

            QString jointType, plusTheta;
            int id, parentID;
            double a,alpha,d,theta,qMin,qMax,mass;

            for(int i=0; i<robotTable->rowCount(); i++)
            {
                plusTheta = "";

                id          = i;
                parentID    = (i==0)? -1 : robotTable->item(i,1)->data(Qt::StatusTipRole).toInt();
                jointType   = (robotTable->item(i,2)->text().startsWith("R"))? "Rot" : "Pri";
                a           = QDynGeneric::meters2double(robotTable->item(i,3)->text());
                alpha       = QDynGeneric::degree2double(robotTable->item(i,4)->text());
                d           = QDynGeneric::meters2double(robotTable->item(i,5)->text());
                theta       = QDynGeneric::degree2double(robotTable->item(i,6)->text());

                if(QDynGeneric::degree2double(robotTable->item(i,7)->text()) != 0)
                {
                    plusTheta += " plus=\"";
                    plusTheta += QString::number(QDynGeneric::degree2double(robotTable->item(i,7)->text()));
                    plusTheta += "\"";
                }

                qMin        = QDynGeneric::degree2double(robotTable->item(i,8)->text());
                qMax        = QDynGeneric::degree2double(robotTable->item(i,9)->text());
                mass        = QDynGeneric::kilogram2double(robotTable->item(i,10)->text());

                out << "\t\t<Link>\n";
                out << "\t\t\t<Name>" << robotTable->item(i,0)->text() << "</Name>\n";

                if(id != 0)
                out << "\t\t\t<Id>" << i << "</Id>\n";

                if(parentID != -1)
                out << "\t\t\t<ParentId>" << parentID << "</ParentId>\n";

                if(id != 0)
                out << "\t\t\t<Joint>" << jointType << "</Joint>\n";

                if(id != 0)
                out << "\t\t\t<a>" << a << "</a>\n";

                // Alpha can be defined for any Link
                out << "\t\t\t<alpha>" << alpha << "</alpha>\n";

                if(id != 0)
                out << "\t\t\t<d>" << d << "</d>\n";

                // Theta can be defined for any Link
                out << "\t\t\t<theta" << plusTheta << ">" << theta << "</theta>\n";

                if(id != 0)
                out << "\t\t\t<qMin>" << qMin << "</qMin>\n";

                if(id != 0)
                out << "\t\t\t<qMax>" << qMax << "</qMax>\n";

                if(mass != 1)
                out << "\t\t\t<m>" << mass << "</m>\n";

                out << "\t\t</Link>\n";
            }

            out << "\t</Links>\n";
            out << "</Robot>\n";
            file->close();
            delete file;
        }
    }
    this->setFocus();
}

void QDynDialogRobotTable::on_robotTable_customContextMenuRequested(QPoint pos)
{
    QMenu menu(this);
    menu.addAction(actionAddLink);

    if(robotTable->itemAt(pos))
    if(robotTable->itemAt(pos)->row()!=0)
    menu.addAction(actionDeleteLink);

    menu.addAction(actionClearTable);
    menu.exec(robotTable->viewport()->mapToGlobal(pos));
}

void QDynDialogRobotTable::on_actionAddLink_triggered()
{
    settingTable = true;

    QTableWidgetItem *baseItem = new QTableWidgetItem();
    QTableWidgetItem *tableItem;
    baseItem->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled | Qt::ItemIsEditable);

    int indLastRow = robotTable->rowCount();
    robotTable->insertRow(indLastRow);

    for(int j=0; j<11; j++)
    {
        tableItem = baseItem->clone();
        robotTable->setItem(indLastRow,j,tableItem);
    }

    robotTable->item(indLastRow,0)->setText("Link" + QString::number(indLastRow));
    robotTable->item(indLastRow,1)->setText(robotTable->item(indLastRow-1,0)->text());
    robotTable->item(indLastRow,1)->setData(Qt::StatusTipRole,indLastRow-1);
    robotTable->item(indLastRow,2)->setText("Revolute");
    robotTable->item(indLastRow,3)->setText(QDynGeneric::double2meters(0));
    robotTable->item(indLastRow,4)->setText(QDynGeneric::double2degree(0));
    robotTable->item(indLastRow,5)->setText(QDynGeneric::double2meters(0));
    robotTable->item(indLastRow,6)->setText(QDynGeneric::double2degree(0));
    robotTable->item(indLastRow,7)->setText(QDynGeneric::double2degree(0));
    robotTable->item(indLastRow,8)->setText(QDynGeneric::double2degree(0));
    robotTable->item(indLastRow,9)->setText(QDynGeneric::double2degree(0));
    robotTable->item(indLastRow,10)->setText(QDynGeneric::double2kilogram(1));

    settingTable = false;
}

void QDynDialogRobotTable::on_actionDeleteLink_triggered()
{
    settingTable = true;

    int deletedLinkId = robotTable->currentRow();
    int deletedLinkParentId = robotTable->item(robotTable->currentRow(),1)->data(Qt::StatusTipRole).toInt();

    robotTable->removeRow(robotTable->currentRow());

    for(int i=1; i<robotTable->rowCount()-1; i++)
    {
        // If we delete a link, the new parent for its child links will be its own parent
        if(deletedLinkId == robotTable->item(i,1)->data(Qt::StatusTipRole).toInt())
        robotTable->item(i,1)->setText(robotTable->item(deletedLinkParentId,0)->text());
    }

    for(int i=1; i<robotTable->rowCount()-1; i++)
    {
        for(int j=0; j<i; j++)
        {
            if(robotTable->item(i,1)->text() == robotTable->item(j,0)->text())
            robotTable->item(i,1)->setData(Qt::StatusTipRole,j);
        }
    }

    settingTable = false;
}

void QDynDialogRobotTable::on_actionClearTable_triggered()
{
    openDialog(0);
}

void QDynDialogRobotTable::on_closeDialog_clicked()
{
    this->close();
}

void QDynDialogRobotTable::on_robotTable_itemChanged(QTableWidgetItem* item)
{
    if(!settingTable)
    {
        if(item->column() == 0)
        {
            // Refresh names in the table if the item changed is parent of someone else
            for(int i=1; i<robotTable->rowCount(); i++)
            {
                if(robotTable->item(i,1)->data(Qt::StatusTipRole).toInt() == item->row())
                robotTable->item(i,1)->setText(item->text());
            }
        }
    }
}
