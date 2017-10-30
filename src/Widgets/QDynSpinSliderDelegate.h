#ifndef QDynSpinSliderDelegate_H
#define QDynSpinSliderDelegate_H

#include <QStyledItemDelegate>
#include <QLineEdit>
#include <Widgets/QDynSpinSlider.h>
#include <QTreeWidgetItem>
#include <QDebug>

class QDynSpinSliderDelegate : public QStyledItemDelegate
{
    Q_OBJECT

public:
    enum QDynDelegateType{Obstacle, Robot};

    QDynDelegateType delegateType;

    QDynSpinSliderDelegate(QObject* parent, QDynDelegateType degType);
    QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const;
    void setEditorData(QWidget *editor, const QModelIndex &index) const;
    void setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const;
    void updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const;
private slots:
    void editing(double value);
};

#endif // QDynSpinSliderDelegate_H
