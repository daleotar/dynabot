#include "QDynLineEditDelegate.h"

QDynLineEditDelegate::QDynLineEditDelegate(QObject *parent) : QStyledItemDelegate(parent)
{
}

QWidget* QDynLineEditDelegate::createEditor(QWidget* parent,const QStyleOptionViewItem &option,const QModelIndex &index) const
{
    if(index.column() == 0)
    {
        QLineEdit* editor = new QLineEdit(parent);
        return editor;
    }
    else
    {
        return 0;
    }
}
void QDynLineEditDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const
{
    if(index.column() == 0)
    {
        QString value = index.model()->data(index,Qt::EditRole).toString();
        QLineEdit* line = static_cast<QLineEdit*>(editor);
        line->setText(value);
    }
}

void QDynLineEditDelegate::setModelData(QWidget* editor,QAbstractItemModel* model,const QModelIndex &index) const
{
    if(index.column() == 0)
    {
        QLineEdit* line = static_cast<QLineEdit*>(editor);
        QString value = line->text();
        model->setData(index,value);
    }
}

void QDynLineEditDelegate::updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    if(index.column() == 0)
    {
        editor->setGeometry(option.rect);
    }
}
