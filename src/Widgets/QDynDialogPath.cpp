#include "QDynDialogPath.h"

QDynDialogPath::QDynDialogPath(QWidget *parent) : QDialog(parent)
{
    setupUi(this);
    this->setFixedSize(this->width(),this->height());

    filterTXT << "TXT Files (*.txt)";
    filterTXT << "All files (*.*)";

    xSel = 0;
    ySel = 0;
    zSel = 0;
}

QDynDialogPath::~QDynDialogPath()
{

}

void QDynDialogPath::setFileDialog(QFileDialog *dialog)
{
    this->fileDialog = dialog;
}

void QDynDialogPath::openDialog()
{
    if(this->isHidden())
    this->show();
}

void QDynDialogPath::on_pathOpenFile_clicked()
{
    fileDialog->setFileMode(QFileDialog::ExistingFile);
    fileDialog->setFilters(filterTXT);
    fileDialog->setOption(QFileDialog::DontUseNativeDialog,true);
    fileDialog->setAcceptMode(QFileDialog::AcceptOpen);
    fileDialog->setDirectory(QDir::currentPath() + "/../paths");

    if(fileDialog->exec())
    {
        this->pathFilename->setText(fileDialog->selectedFiles().at(0));
    }
}

void QDynDialogPath::on_ok_clicked()
{
    if(tabWidget->currentIndex() == 0)
    {
        QFileInfo *fileInfo = new QFileInfo(pathFilename->text());
        if(fileInfo->exists())
        {
            emit addPathFromFile(pathFilename->text());
            close();
        }
        else
        {
            QMessageBox::warning(0,"DynaBOT::Paths::Warning","The file specified doesn't exist");
        }
        delete fileInfo;
    }
    else
    {
        if(xIni->value() == xFin->value() && yIni->value() == yFin->value() && zIni->value() == zFin->value())
        {
            QMessageBox::warning(0,"DynaBOT::Paths::Warning","Starting and End Points must be different");
        }
        else
        {
            emit addPathFromPoints(xIni->value(),yIni->value(),zIni->value(),xFin->value(),yFin->value(),zFin->value(),spinPoints->value());
            close();
        }
    }
}

void QDynDialogPath::on_cancel_clicked()
{
    this->close();
}

void QDynDialogPath::on_getIniFromLink_clicked()
{
    updateSelectedXYZ();
    xIni->setValue(xSel);
    yIni->setValue(ySel);
    zIni->setValue(zSel);
}

void QDynDialogPath::on_getFinFromLink_clicked()
{
    updateSelectedXYZ();
    xFin->setValue(xSel);
    yFin->setValue(ySel);
    zFin->setValue(zSel);
}

void QDynDialogPath::updateSelectedXYZ()
{
    if(robotTree->selectedItems().count() > 0)
    {
        QTreeWidgetItem *item = robotTree->selectedItems()[0];
        if(!item->parent())
        {
            // If a robot is being selected then take its last link's position as the selected point
            if(item->child(item->childCount()-1)->text(0) == "Paths")
            item = item->child(item->childCount()-2);
            else
            item = item->child(item->childCount()-1);

        }
        else
        {   // If a link or a link property is being selected then take the position of the actual link.
            // The index of the selected item has to be found first.
            // They're at this order:
            // 0-Loc/Rot
            // 1-Link0
            // 2-Link1
            // ....
            int itemIndex = 0;

            if(!item->parent()->parent())
            {
                // If the item selected has no parent, it is a link or Loc/Rot item.
                itemIndex = item->parent()->indexOfChild(item);
            }
            else
            {
                // If a property is selected
                itemIndex = item->parent()->parent()->indexOfChild(item->parent());
                // The pointer is changed to the actual selected item
                item = item->parent();
            }

            if(item->parent()->child(item->parent()->childCount()-1)->text(0) == "Paths")
            {
                if(itemIndex == 0 || itemIndex == item->parent()->childCount()-1)
                // If Loc/Rot or "Paths" is selected while we have Paths, then the item will be the last link.
                item = item->parent()->child(item->parent()->childCount()-2);
            }
            else if(itemIndex == 0)
            {
                // If Loc/Rot is selected then the item will be the last link.
                item = item->parent()->child(item->parent()->childCount()-1);
            }


        }
        QList<QString> xyz = item->child(1)->text(1).split("::");
        xSel = QDynGeneric::meters2double(xyz[0]);
        ySel = QDynGeneric::meters2double(xyz[1]);
        zSel = QDynGeneric::meters2double(xyz[2]);
    }
}
