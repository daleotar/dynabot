#include "QDynRobotTableDelegate.h"

QDynRobotTableDelegate::QDynRobotTableDelegate(QObject *parent) : QStyledItemDelegate(parent)
{
}

QWidget* QDynRobotTableDelegate::createEditor(QWidget* parent,const QStyleOptionViewItem &option,const QModelIndex &index) const
{
    if(index.column() == 0)
    {
        QLineEdit *editor = new QLineEdit(parent);
        return editor;
    }
    else if(index.column() == 1 || index.column() == 2)
    {
        if(index.row() == 0)
        {
            return 0;
        }
        else
        {
            QComboBox *editor = new QComboBox(parent);

            if(index.column() == 2)
            {
                editor->addItem("Revolute");
                editor->addItem("Prismatic");
            }

            connect(editor,SIGNAL(activated(int)),this,SLOT(comboChanged()));

            return editor;
        }
    }
    else if(index.column() >= 3 && index.column() <= 10)
    {

        if(index.row() == 0)
        {
            if(index.column() == 4 || index.column() == 6 || index.column() == 7 || index.column() == 10)
            {
                QDoubleSpinBox *editor = new QDoubleSpinBox(parent);
                editor->setAccelerated(true);
                return editor;
            }
            else
            {
                return 0;
            }
        }
        else
        {
            QDoubleSpinBox *editor = new QDoubleSpinBox(parent);
            editor->setAccelerated(true);
            return editor;
        }
    }
    else
    {
        return 0;
    }
}
void QDynRobotTableDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const
{
    QTableWidget *table = static_cast<QTableWidget*>(this->parent());
    int jointType = (table->item(index.row(),2)->text() == "Revolute")? 0 : 1;

    if(index.column() == 0)
    {
        QString value = index.model()->data(index,Qt::EditRole).toString();
        QLineEdit *line = static_cast<QLineEdit*>(editor);
        line->setText(value);
    }
    if(index.column() == 1)
    {
        QComboBox *combo = static_cast<QComboBox*>(editor);
        combo->clear();

        for(int i=0; i<index.row(); i++)
        {
            combo->addItem(table->item(i,0)->text());
        }

        combo->setCurrentIndex(table->item(index.row(),1)->data(Qt::StatusTipRole).toInt());
        combo->showPopup();
    }
    if(index.column() == 2)
    {
        QComboBox *combo = static_cast<QComboBox*>(editor);
        combo->setCurrentIndex(jointType);
        combo->showPopup();
    }
    if(index.column() == 3 || index.column() == 5)
    {
        QDoubleSpinBox *spin = static_cast<QDoubleSpinBox*>(editor);
        QString value = index.model()->data(index,Qt::EditRole).toString();
        value.chop(2);
        spin->setSuffix(" m");
        spin->setDecimals((jointType == 0)? 5 : 6);
        spin->setRange(-5,5);
        spin->setSingleStep(0.1);
        spin->setValue(value.toDouble());
    }
    if(index.column() == 10)
    {
        QDoubleSpinBox *spin = static_cast<QDoubleSpinBox*>(editor);
        QString value = index.model()->data(index,Qt::EditRole).toString();
        value.chop(3);
        spin->setSuffix(" kg");
        spin->setDecimals(3);
        spin->setRange(0,200);
        spin->setSingleStep(0.1);
        spin->setValue(value.toDouble());
    }
    if(index.column() == 4 || index.column() == 6 || index.column() == 7)
    {
        QDoubleSpinBox *spin = static_cast<QDoubleSpinBox*>(editor);
        QString value = index.model()->data(index,Qt::EditRole).toString();
        value.chop(2);
        spin->setSuffix(" °");
        spin->setDecimals((index.column() == 7)? 1 : ((jointType == 0)? 5 : 1 ));
        spin->setRange(-180,180);
        spin->setSingleStep(1);
        spin->setValue(value.toDouble());
    }
    if(index.column() == 8 || index.column() == 9)
    {
        QDoubleSpinBox *spin = static_cast<QDoubleSpinBox*>(editor);
        QString value = index.model()->data(index,Qt::EditRole).toString();
        value.chop(2);

        if(jointType == 0)
        {
            spin->setSuffix(" °");
            spin->setDecimals(1);
            spin->setRange(-180,180);
            spin->setSingleStep(1);
            spin->setValue(value.toDouble());
        }
        if(jointType == 1)
        {
            spin->setSuffix(" m");
            spin->setDecimals(3);
            spin->setRange(-5,5);
            spin->setSingleStep(0.1);
            spin->setValue(value.toDouble());
        }
    }
}

void QDynRobotTableDelegate::setModelData(QWidget* editor,QAbstractItemModel* model,const QModelIndex &index) const
{
    QTableWidget *table = static_cast<QTableWidget*>(this->parent());
//    int jointType = (table->item(index.row(),2)->text() == "Revolute")? 0 : 1;

    if(index.column() == 0)
    {
        QLineEdit *line = static_cast<QLineEdit*>(editor);
        model->setData(index,line->text());
    }
    if(index.column() == 1)
    {
        QComboBox *combo = static_cast<QComboBox*>(editor);
        table->item(index.row(),index.column())->setData(Qt::StatusTipRole,combo->currentIndex());
        model->setData(index,combo->itemText(combo->currentIndex()));

    }
    if(index.column() == 2)
    {
        QComboBox *combo = static_cast<QComboBox*>(editor);
        QString prevData = model->data(index,Qt::EditRole).toString();
        model->setData(index,combo->itemText(combo->currentIndex()));
        if(prevData != combo->itemText(combo->currentIndex()))
        emit jointChanged(index.row());

    }
    if(index.column() >= 3 && index.column() <= 10)
    {
        QDoubleSpinBox *spin = static_cast<QDoubleSpinBox*>(editor);
        model->setData(index,QString::number(spin->value()) + spin->suffix());
    }
}

void QDynRobotTableDelegate::updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    editor->setGeometry(option.rect);
}

void QDynRobotTableDelegate::comboChanged()
{
    QDoubleSpinBox *spin = static_cast<QDoubleSpinBox*>(sender());
    emit commitData(spin);
    emit closeEditor(spin);
}
