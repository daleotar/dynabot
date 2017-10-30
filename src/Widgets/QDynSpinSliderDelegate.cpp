#include "QDynSpinSliderDelegate.h"

QDynSpinSliderDelegate::QDynSpinSliderDelegate(QObject *parent, QDynDelegateType degType) : QStyledItemDelegate(parent)
{
    delegateType = degType;
}

QWidget* QDynSpinSliderDelegate::createEditor(QWidget* parent,const QStyleOptionViewItem &option,const QModelIndex &index) const
{
    if(delegateType == Obstacle)
    {
        QTreeWidgetItem *treeItem = static_cast<QTreeWidgetItem *>(index.internalPointer());

        if(index.column() == 0 && !treeItem->parent())
        {
            QLineEdit* editor = new QLineEdit(parent);
            return editor;
        }
        else if(index.column()==1 && treeItem->parent())
        {
            QDynSpinSlider *editor = new QDynSpinSlider(parent);
            connect(editor,SIGNAL(valueChanged(double)),this,SLOT(editing(double)));
            if(index.row()>=0 && index.row()<=2)
            {
                editor->setRange(-5,5);
                editor->setDecimals(3);
                editor->setSuffix(" m");
                editor->setSingleStep(0.05);
                editor->setPageStep(0.15);
            }
            else
            {
                editor->setRange(-180,180);
                editor->setDecimals(3);
                editor->setSuffix(" °");
                editor->setSingleStep(0.1);
                editor->setPageStep(1);
            }
            return editor;
        }
        else
        {
            return 0;
        }
    }
    else if(delegateType == Robot)
    {
        QTreeWidgetItem *treeItem = static_cast<QTreeWidgetItem *>(index.internalPointer());
        QTreeWidgetItem *treeItemParent = static_cast<QTreeWidgetItem *>(index.parent().internalPointer());

        if(index.column() == 0 && !treeItemParent)
        {
            QLineEdit* editor = new QLineEdit(parent);
            return editor;
        }
        else if(index.column() == 1 && treeItemParent)
        {
            QDynSpinSlider *editor = new QDynSpinSlider(parent);
            connect(editor,SIGNAL(valueChanged(double)),this,SLOT(editing(double)));
            if(treeItemParent->text(0) == "Loc./Rot.")
            {
                // First we're defining the delegate to the Loc/Rot of the Robot
                if(index.row()>=0 && index.row()<=2)
                {
                    editor->setRange(-5,5);
                    editor->setDecimals(3);
                    editor->setSuffix(" m");
                    editor->setSingleStep(0.05);
                    editor->setPageStep(0.15);
                }
                else
                {
                    editor->setRange(-180,180);
                    editor->setDecimals(3);
                    editor->setSuffix(" °");
                    editor->setSingleStep(0.1);
                    editor->setPageStep(1);
                }
            }
            else if(treeItemParent->text(0) != "Paths")
            {
                QTreeWidgetItem *treeqMinqMax = static_cast<QTreeWidgetItem *>(treeItemParent->child(0));
                // First we have to get the min and max value of a joint.
                QList<QString> qMinqMax = treeqMinqMax->statusTip(1).split(" ");
                double qMin = qMinqMax[0].toDouble();
                double qMax = qMinqMax[3].toDouble();

                if(treeItem->text(0) == QString("d"))
                {
                    editor->setDecimals(3);
                    editor->setSingleStep(0.001);
                    editor->setRange(qMin,qMax);
                    editor->setSuffix(" m");
                    editor->setPageStep(0.01);
                }
                else
                {
                    editor->setDecimals(3);
                    editor->setSingleStep(0.1);
                    editor->setRange(qMin,qMax);
                    editor->setSuffix(" °");
                    editor->setPageStep(1);
                }
            }
            return editor;
        }
        else
        {
            return 0;
        }
    }
    else
    {
        return 0;
    }
}
void QDynSpinSliderDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const
{
    if(index.column() == 0)
    {
        QString value = index.model()->data(index,Qt::EditRole).toString();
        QLineEdit* line = static_cast<QLineEdit*>(editor);
        line->setText(value);
    }
    else
    {
        QDynSpinSlider *spinslide = static_cast<QDynSpinSlider*>(editor);
        QString strValue = index.model()->data(index,Qt::EditRole).toString();
        strValue.chop(2);
        double value = strValue.toDouble();
        spinslide->setValue(value);
        spinslide->spinBox->setFocus();
    }
}

void QDynSpinSliderDelegate::setModelData(QWidget* editor,QAbstractItemModel* model,const QModelIndex &index) const
{
    if(index.column() == 0)
    {
        QLineEdit* line = static_cast<QLineEdit*>(editor);
        QString value = line->text();
        model->setData(index,value);
    }
    else
    {
        QDynSpinSlider* spinslide = static_cast<QDynSpinSlider*>(editor);
        QString value = QString::number(spinslide->value) + spinslide->spinBox->suffix();

        model->setData(index,value);
    }
}

void QDynSpinSliderDelegate::updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    if(index.column() == 0)
    {
        editor->setGeometry(option.rect);
    }
    else
    {
        QDynSpinSlider *spinslide = static_cast<QDynSpinSlider*>(editor);
        spinslide->adjustAllSizes(option.rect);
        spinslide->setFocus();
    }
}

void QDynSpinSliderDelegate::editing(double value)
{
    QDynSpinSlider *spinslide = static_cast<QDynSpinSlider*>(sender());
    emit commitData(spinslide);
}
