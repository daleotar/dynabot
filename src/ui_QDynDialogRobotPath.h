/********************************************************************************
** Form generated from reading UI file 'QDynDialogRobotPath.ui'
**
** Created: Wed 20. Jul 16:14:04 2011
**      by: Qt User Interface Compiler version 4.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_QDYNDIALOGROBOTPATH_H
#define UI_QDYNDIALOGROBOTPATH_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QComboBox>
#include <QtGui/QDialog>
#include <QtGui/QDoubleSpinBox>
#include <QtGui/QFrame>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_QDynDialogRobotPath
{
public:
    QComboBox *comboPath;
    QDoubleSpinBox *spinSpeed;
    QPushButton *cancel;
    QPushButton *ok;
    QFrame *line_2;
    QComboBox *comboLink;
    QLabel *label;
    QLabel *label_2;
    QLabel *label_3;
    QLabel *label_4;
    QDoubleSpinBox *spinApproach;

    void setupUi(QDialog *QDynDialogRobotPath)
    {
        if (QDynDialogRobotPath->objectName().isEmpty())
            QDynDialogRobotPath->setObjectName(QString::fromUtf8("QDynDialogRobotPath"));
        QDynDialogRobotPath->setWindowModality(Qt::ApplicationModal);
        QDynDialogRobotPath->resize(229, 193);
        comboPath = new QComboBox(QDynDialogRobotPath);
        comboPath->setObjectName(QString::fromUtf8("comboPath"));
        comboPath->setGeometry(QRect(129, 9, 91, 22));
        spinSpeed = new QDoubleSpinBox(QDynDialogRobotPath);
        spinSpeed->setObjectName(QString::fromUtf8("spinSpeed"));
        spinSpeed->setGeometry(QRect(129, 100, 91, 22));
        spinSpeed->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        spinSpeed->setAccelerated(true);
        spinSpeed->setDecimals(4);
        spinSpeed->setMinimum(0.0001);
        spinSpeed->setValue(0.01);
        cancel = new QPushButton(QDynDialogRobotPath);
        cancel->setObjectName(QString::fromUtf8("cancel"));
        cancel->setGeometry(QRect(137, 146, 81, 35));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/resources/icons/cancel.png"), QSize(), QIcon::Normal, QIcon::Off);
        cancel->setIcon(icon);
        cancel->setIconSize(QSize(24, 24));
        cancel->setCheckable(false);
        cancel->setAutoDefault(true);
        cancel->setDefault(false);
        cancel->setFlat(false);
        ok = new QPushButton(QDynDialogRobotPath);
        ok->setObjectName(QString::fromUtf8("ok"));
        ok->setGeometry(QRect(49, 146, 81, 35));
        ok->setStyleSheet(QString::fromUtf8(""));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/resources/icons/ok.png"), QSize(), QIcon::Normal, QIcon::Off);
        ok->setIcon(icon1);
        ok->setIconSize(QSize(24, 24));
        ok->setCheckable(false);
        ok->setAutoDefault(true);
        ok->setDefault(false);
        ok->setFlat(false);
        line_2 = new QFrame(QDynDialogRobotPath);
        line_2->setObjectName(QString::fromUtf8("line_2"));
        line_2->setGeometry(QRect(8, 122, 211, 31));
        line_2->setFrameShape(QFrame::HLine);
        line_2->setFrameShadow(QFrame::Sunken);
        comboLink = new QComboBox(QDynDialogRobotPath);
        comboLink->setObjectName(QString::fromUtf8("comboLink"));
        comboLink->setGeometry(QRect(129, 40, 91, 22));
        label = new QLabel(QDynDialogRobotPath);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(29, 9, 91, 22));
        label->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        label_2 = new QLabel(QDynDialogRobotPath);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(19, 40, 101, 22));
        label_2->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        label_3 = new QLabel(QDynDialogRobotPath);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setGeometry(QRect(9, 70, 111, 22));
        label_3->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        label_4 = new QLabel(QDynDialogRobotPath);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setGeometry(QRect(9, 100, 111, 22));
        label_4->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        spinApproach = new QDoubleSpinBox(QDynDialogRobotPath);
        spinApproach->setObjectName(QString::fromUtf8("spinApproach"));
        spinApproach->setGeometry(QRect(129, 70, 91, 22));
        spinApproach->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        spinApproach->setAccelerated(true);
        spinApproach->setDecimals(4);
        spinApproach->setMinimum(0.0001);
        spinApproach->setValue(0.1);

        retranslateUi(QDynDialogRobotPath);

        QMetaObject::connectSlotsByName(QDynDialogRobotPath);
    } // setupUi

    void retranslateUi(QDialog *QDynDialogRobotPath)
    {
        QDynDialogRobotPath->setWindowTitle(QApplication::translate("QDynDialogRobotPath", "Dialog", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        comboPath->setToolTip(QApplication::translate("QDynDialogRobotPath", "Choose the Scene's path that is going to be followed.", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_TOOLTIP
        spinSpeed->setToolTip(QApplication::translate("QDynDialogRobotPath", "This value specifies the linear speed of the frame of reference attached to the selected link.", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        spinSpeed->setSuffix(QApplication::translate("QDynDialogRobotPath", " m/s", 0, QApplication::UnicodeUTF8));
        cancel->setText(QApplication::translate("QDynDialogRobotPath", "  Cancel", 0, QApplication::UnicodeUTF8));
        ok->setText(QApplication::translate("QDynDialogRobotPath", "   OK    ", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        comboLink->setToolTip(QApplication::translate("QDynDialogRobotPath", "With this list you can specify the Link of the selected Robot which is going to follow the Path specified.", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        label->setText(QApplication::translate("QDynDialogRobotPath", "Path to Follow:", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("QDynDialogRobotPath", "Link following Path:", 0, QApplication::UnicodeUTF8));
        label_3->setText(QApplication::translate("QDynDialogRobotPath", "Approach Speed", 0, QApplication::UnicodeUTF8));
        label_4->setText(QApplication::translate("QDynDialogRobotPath", "Speed:", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        spinApproach->setToolTip(QApplication::translate("QDynDialogRobotPath", "This value specifies the linear speed of the frame of reference attached to the selected link.", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        spinApproach->setSuffix(QApplication::translate("QDynDialogRobotPath", " m/s", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class QDynDialogRobotPath: public Ui_QDynDialogRobotPath {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_QDYNDIALOGROBOTPATH_H
