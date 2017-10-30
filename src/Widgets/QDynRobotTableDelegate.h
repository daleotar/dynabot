#ifndef QDYNROBOTTABLEDELEGATE_H
#define QDYNROBOTTABLEDELEGATE_H

#include <QStyledItemDelegate>
#include <QLineEdit>
#include <QComboBox>
#include <QDoubleSpinBox>
#include <QTableWidget>
#include <QDebug>

class QDynRobotTableDelegate : public QStyledItemDelegate
{
    Q_OBJECT

public:
    QDynRobotTableDelegate(QObject* parent);
    QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const;
    virtual void setEditorData(QWidget *editor, const QModelIndex &index) const;
    virtual void setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const;
    virtual void updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const;

public slots:
    void comboChanged();

signals:
    void jointChanged(int row) const;

};

#endif // QDYNROBOTTABLEDELEGATE_H
