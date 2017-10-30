/********************************************************************************
** Form generated from reading UI file 'QDynDialogRobotTable.ui'
**
** Created: Wed 20. Jul 16:14:04 2011
**      by: Qt User Interface Compiler version 4.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_QDYNDIALOGROBOTTABLE_H
#define UI_QDYNDIALOGROBOTTABLE_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QFrame>
#include <QtGui/QGridLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QPushButton>
#include <QtGui/QTableWidget>

QT_BEGIN_NAMESPACE

class Ui_QDynDialogRobotTable
{
public:
    QAction *actionAddLink;
    QAction *actionDeleteLink;
    QAction *actionClearTable;
    QGridLayout *gridLayout;
    QTableWidget *robotTable;
    QFrame *line_2;
    QLabel *label;
    QLabel *label_2;
    QPushButton *closeDialog;
    QLineEdit *robotName;
    QPushButton *save;

    void setupUi(QDialog *QDynDialogRobotTable)
    {
        if (QDynDialogRobotTable->objectName().isEmpty())
            QDynDialogRobotTable->setObjectName(QString::fromUtf8("QDynDialogRobotTable"));
        QDynDialogRobotTable->setWindowModality(Qt::NonModal);
        QDynDialogRobotTable->resize(803, 291);
        QDynDialogRobotTable->setSizeGripEnabled(true);
        QDynDialogRobotTable->setModal(true);
        actionAddLink = new QAction(QDynDialogRobotTable);
        actionAddLink->setObjectName(QString::fromUtf8("actionAddLink"));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/resources/icons/link_add.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionAddLink->setIcon(icon);
        actionDeleteLink = new QAction(QDynDialogRobotTable);
        actionDeleteLink->setObjectName(QString::fromUtf8("actionDeleteLink"));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/resources/icons/delete.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionDeleteLink->setIcon(icon1);
        actionClearTable = new QAction(QDynDialogRobotTable);
        actionClearTable->setObjectName(QString::fromUtf8("actionClearTable"));
        QIcon icon2;
        icon2.addFile(QString::fromUtf8(":/resources/icons/table_clear.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionClearTable->setIcon(icon2);
        gridLayout = new QGridLayout(QDynDialogRobotTable);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        gridLayout->setSizeConstraint(QLayout::SetDefaultConstraint);
        robotTable = new QTableWidget(QDynDialogRobotTable);
        if (robotTable->columnCount() < 11)
            robotTable->setColumnCount(11);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        robotTable->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        robotTable->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        robotTable->setHorizontalHeaderItem(2, __qtablewidgetitem2);
        QTableWidgetItem *__qtablewidgetitem3 = new QTableWidgetItem();
        robotTable->setHorizontalHeaderItem(3, __qtablewidgetitem3);
        QTableWidgetItem *__qtablewidgetitem4 = new QTableWidgetItem();
        robotTable->setHorizontalHeaderItem(4, __qtablewidgetitem4);
        QTableWidgetItem *__qtablewidgetitem5 = new QTableWidgetItem();
        robotTable->setHorizontalHeaderItem(5, __qtablewidgetitem5);
        QTableWidgetItem *__qtablewidgetitem6 = new QTableWidgetItem();
        robotTable->setHorizontalHeaderItem(6, __qtablewidgetitem6);
        QTableWidgetItem *__qtablewidgetitem7 = new QTableWidgetItem();
        robotTable->setHorizontalHeaderItem(7, __qtablewidgetitem7);
        QTableWidgetItem *__qtablewidgetitem8 = new QTableWidgetItem();
        robotTable->setHorizontalHeaderItem(8, __qtablewidgetitem8);
        QTableWidgetItem *__qtablewidgetitem9 = new QTableWidgetItem();
        robotTable->setHorizontalHeaderItem(9, __qtablewidgetitem9);
        QTableWidgetItem *__qtablewidgetitem10 = new QTableWidgetItem();
        robotTable->setHorizontalHeaderItem(10, __qtablewidgetitem10);
        robotTable->setObjectName(QString::fromUtf8("robotTable"));
        robotTable->setContextMenuPolicy(Qt::CustomContextMenu);
        robotTable->setEditTriggers(QAbstractItemView::AnyKeyPressed|QAbstractItemView::EditKeyPressed|QAbstractItemView::SelectedClicked);
        robotTable->setAlternatingRowColors(true);
        robotTable->horizontalHeader()->setDefaultSectionSize(90);
        robotTable->horizontalHeader()->setMinimumSectionSize(90);

        gridLayout->addWidget(robotTable, 1, 1, 1, 4);

        line_2 = new QFrame(QDynDialogRobotTable);
        line_2->setObjectName(QString::fromUtf8("line_2"));
        line_2->setFrameShape(QFrame::HLine);
        line_2->setFrameShadow(QFrame::Sunken);

        gridLayout->addWidget(line_2, 2, 0, 2, 5);

        label = new QLabel(QDynDialogRobotTable);
        label->setObjectName(QString::fromUtf8("label"));
        label->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout->addWidget(label, 0, 0, 1, 1);

        label_2 = new QLabel(QDynDialogRobotTable);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setMinimumSize(QSize(90, 120));
        label_2->setMaximumSize(QSize(90, 300));
        label_2->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout->addWidget(label_2, 1, 0, 1, 1);

        closeDialog = new QPushButton(QDynDialogRobotTable);
        closeDialog->setObjectName(QString::fromUtf8("closeDialog"));
        closeDialog->setMinimumSize(QSize(75, 0));
        closeDialog->setMaximumSize(QSize(75, 16777215));
        QIcon icon3;
        icon3.addFile(QString::fromUtf8(":/resources/icons/cancel.png"), QSize(), QIcon::Normal, QIcon::Off);
        closeDialog->setIcon(icon3);
        closeDialog->setIconSize(QSize(24, 24));
        closeDialog->setCheckable(false);
        closeDialog->setAutoDefault(true);
        closeDialog->setDefault(false);
        closeDialog->setFlat(false);

        gridLayout->addWidget(closeDialog, 4, 4, 1, 1);

        robotName = new QLineEdit(QDynDialogRobotTable);
        robotName->setObjectName(QString::fromUtf8("robotName"));

        gridLayout->addWidget(robotName, 0, 1, 1, 4);

        save = new QPushButton(QDynDialogRobotTable);
        save->setObjectName(QString::fromUtf8("save"));
        save->setMinimumSize(QSize(90, 0));
        save->setMaximumSize(QSize(90, 16777215));
        save->setStyleSheet(QString::fromUtf8(""));
        QIcon icon4;
        icon4.addFile(QString::fromUtf8(":/resources/icons/save_as.png"), QSize(), QIcon::Normal, QIcon::Off);
        save->setIcon(icon4);
        save->setIconSize(QSize(24, 24));
        save->setCheckable(false);
        save->setAutoDefault(true);
        save->setDefault(false);
        save->setFlat(false);

        gridLayout->addWidget(save, 4, 3, 1, 1);


        retranslateUi(QDynDialogRobotTable);

        QMetaObject::connectSlotsByName(QDynDialogRobotTable);
    } // setupUi

    void retranslateUi(QDialog *QDynDialogRobotTable)
    {
        QDynDialogRobotTable->setWindowTitle(QApplication::translate("QDynDialogRobotTable", "Dialog", 0, QApplication::UnicodeUTF8));
        actionAddLink->setText(QApplication::translate("QDynDialogRobotTable", "Add Link at bottom...", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        actionAddLink->setToolTip(QApplication::translate("QDynDialogRobotTable", "Add Link to the current D-H Table", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        actionDeleteLink->setText(QApplication::translate("QDynDialogRobotTable", "Delete this Link", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        actionDeleteLink->setToolTip(QApplication::translate("QDynDialogRobotTable", "Delete selected Link", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        actionClearTable->setText(QApplication::translate("QDynDialogRobotTable", "Clear Table", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        actionClearTable->setToolTip(QApplication::translate("QDynDialogRobotTable", "Clear the current D-H Table", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        QTableWidgetItem *___qtablewidgetitem = robotTable->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QApplication::translate("QDynDialogRobotTable", "Name", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem1 = robotTable->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QApplication::translate("QDynDialogRobotTable", "Parent", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem2 = robotTable->horizontalHeaderItem(2);
        ___qtablewidgetitem2->setText(QApplication::translate("QDynDialogRobotTable", "Joint", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem3 = robotTable->horizontalHeaderItem(3);
        ___qtablewidgetitem3->setText(QApplication::translate("QDynDialogRobotTable", "a [m]", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem4 = robotTable->horizontalHeaderItem(4);
        ___qtablewidgetitem4->setText(QApplication::translate("QDynDialogRobotTable", "\316\261 [\302\260]", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem5 = robotTable->horizontalHeaderItem(5);
        ___qtablewidgetitem5->setText(QApplication::translate("QDynDialogRobotTable", "d [m]", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem6 = robotTable->horizontalHeaderItem(6);
        ___qtablewidgetitem6->setText(QApplication::translate("QDynDialogRobotTable", "\316\270 [\302\260]", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem7 = robotTable->horizontalHeaderItem(7);
        ___qtablewidgetitem7->setText(QApplication::translate("QDynDialogRobotTable", "\316\270+ [\302\260]", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem8 = robotTable->horizontalHeaderItem(8);
        ___qtablewidgetitem8->setText(QApplication::translate("QDynDialogRobotTable", "qMin", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem9 = robotTable->horizontalHeaderItem(9);
        ___qtablewidgetitem9->setText(QApplication::translate("QDynDialogRobotTable", "qMax", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem10 = robotTable->horizontalHeaderItem(10);
        ___qtablewidgetitem10->setText(QApplication::translate("QDynDialogRobotTable", "Mass [Kg]", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("QDynDialogRobotTable", "Robot's Name:", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("QDynDialogRobotTable", "Robot's DH Table:", 0, QApplication::UnicodeUTF8));
        closeDialog->setText(QApplication::translate("QDynDialogRobotTable", "Close", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        save->setToolTip(QApplication::translate("QDynDialogRobotTable", "Save the current Denavit-Hartenber parameters table into a XML file.", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        save->setText(QApplication::translate("QDynDialogRobotTable", "Save as...", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class QDynDialogRobotTable: public Ui_QDynDialogRobotTable {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_QDYNDIALOGROBOTTABLE_H
