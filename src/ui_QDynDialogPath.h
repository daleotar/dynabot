/********************************************************************************
** Form generated from reading UI file 'QDynDialogPath.ui'
**
** Created: Wed 20. Jul 16:14:04 2011
**      by: Qt User Interface Compiler version 4.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_QDYNDIALOGPATH_H
#define UI_QDYNDIALOGPATH_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QDoubleSpinBox>
#include <QtGui/QFrame>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QPushButton>
#include <QtGui/QSpinBox>
#include <QtGui/QTabWidget>
#include <QtGui/QTextEdit>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_QDynDialogPath
{
public:
    QTabWidget *tabWidget;
    QWidget *tabPathFile;
    QPushButton *pathOpenFile;
    QLineEdit *pathFilename;
    QLabel *pathFilelabel;
    QLabel *pathFileLabelInfo;
    QTextEdit *pathFileTextExample;
    QTextEdit *pathFileTextExample_2;
    QWidget *tabPathPoints;
    QDoubleSpinBox *xIni;
    QDoubleSpinBox *xFin;
    QLabel *xFinlabel;
    QLabel *zFinlabel;
    QPushButton *getIniFromLink;
    QDoubleSpinBox *zFin;
    QPushButton *getFinFromLink;
    QDoubleSpinBox *yIni;
    QDoubleSpinBox *zIni;
    QLabel *yInilabel;
    QLabel *yFinlabel;
    QDoubleSpinBox *yFin;
    QLabel *zInilabel;
    QLabel *xInilabel;
    QLabel *pInilabel;
    QLabel *pFinlabel;
    QFrame *line;
    QSpinBox *spinPoints;
    QLabel *label;
    QPushButton *cancel;
    QPushButton *ok;
    QFrame *line_2;

    void setupUi(QDialog *QDynDialogPath)
    {
        if (QDynDialogPath->objectName().isEmpty())
            QDynDialogPath->setObjectName(QString::fromUtf8("QDynDialogPath"));
        QDynDialogPath->setWindowModality(Qt::NonModal);
        QDynDialogPath->resize(264, 275);
        QSizePolicy sizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(QDynDialogPath->sizePolicy().hasHeightForWidth());
        QDynDialogPath->setSizePolicy(sizePolicy);
        QDynDialogPath->setFocusPolicy(Qt::StrongFocus);
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/resources/icons/path.png"), QSize(), QIcon::Normal, QIcon::Off);
        QDynDialogPath->setWindowIcon(icon);
        QDynDialogPath->setSizeGripEnabled(false);
        QDynDialogPath->setModal(false);
        tabWidget = new QTabWidget(QDynDialogPath);
        tabWidget->setObjectName(QString::fromUtf8("tabWidget"));
        tabWidget->setGeometry(QRect(10, 10, 245, 255));
        tabPathFile = new QWidget();
        tabPathFile->setObjectName(QString::fromUtf8("tabPathFile"));
        pathOpenFile = new QPushButton(tabPathFile);
        pathOpenFile->setObjectName(QString::fromUtf8("pathOpenFile"));
        pathOpenFile->setGeometry(QRect(204, 30, 30, 30));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/resources/icons/open.png"), QSize(), QIcon::Normal, QIcon::Off);
        pathOpenFile->setIcon(icon1);
        pathOpenFile->setIconSize(QSize(24, 24));
        pathFilename = new QLineEdit(tabPathFile);
        pathFilename->setObjectName(QString::fromUtf8("pathFilename"));
        pathFilename->setGeometry(QRect(9, 30, 191, 30));
        pathFilelabel = new QLabel(tabPathFile);
        pathFilelabel->setObjectName(QString::fromUtf8("pathFilelabel"));
        pathFilelabel->setGeometry(QRect(10, 10, 61, 16));
        pathFileLabelInfo = new QLabel(tabPathFile);
        pathFileLabelInfo->setObjectName(QString::fromUtf8("pathFileLabelInfo"));
        pathFileLabelInfo->setGeometry(QRect(10, 63, 221, 41));
        pathFileLabelInfo->setTextFormat(Qt::RichText);
        pathFileLabelInfo->setScaledContents(false);
        pathFileLabelInfo->setAlignment(Qt::AlignJustify|Qt::AlignVCenter);
        pathFileLabelInfo->setWordWrap(true);
        pathFileTextExample = new QTextEdit(tabPathFile);
        pathFileTextExample->setObjectName(QString::fromUtf8("pathFileTextExample"));
        pathFileTextExample->setGeometry(QRect(9, 106, 110, 64));
        pathFileTextExample->setReadOnly(true);
        pathFileTextExample_2 = new QTextEdit(tabPathFile);
        pathFileTextExample_2->setObjectName(QString::fromUtf8("pathFileTextExample_2"));
        pathFileTextExample_2->setGeometry(QRect(124, 106, 110, 64));
        pathFileTextExample_2->setReadOnly(true);
        tabWidget->addTab(tabPathFile, QString());
        tabPathPoints = new QWidget();
        tabPathPoints->setObjectName(QString::fromUtf8("tabPathPoints"));
        xIni = new QDoubleSpinBox(tabPathPoints);
        xIni->setObjectName(QString::fromUtf8("xIni"));
        xIni->setGeometry(QRect(30, 32, 80, 22));
        xIni->setDecimals(6);
        xIni->setMinimum(-10);
        xIni->setMaximum(10);
        xFin = new QDoubleSpinBox(tabPathPoints);
        xFin->setObjectName(QString::fromUtf8("xFin"));
        xFin->setGeometry(QRect(151, 32, 80, 22));
        xFin->setDecimals(6);
        xFin->setMinimum(-10);
        xFin->setMaximum(10);
        xFinlabel = new QLabel(tabPathPoints);
        xFinlabel->setObjectName(QString::fromUtf8("xFinlabel"));
        xFinlabel->setGeometry(QRect(132, 34, 10, 16));
        zFinlabel = new QLabel(tabPathPoints);
        zFinlabel->setObjectName(QString::fromUtf8("zFinlabel"));
        zFinlabel->setGeometry(QRect(131, 78, 10, 16));
        getIniFromLink = new QPushButton(tabPathPoints);
        getIniFromLink->setObjectName(QString::fromUtf8("getIniFromLink"));
        getIniFromLink->setGeometry(QRect(8, 104, 106, 35));
        QIcon icon2;
        icon2.addFile(QString::fromUtf8(":/resources/icons/link_pos.png"), QSize(), QIcon::Normal, QIcon::Off);
        getIniFromLink->setIcon(icon2);
        getIniFromLink->setIconSize(QSize(24, 24));
        getIniFromLink->setCheckable(false);
        getIniFromLink->setAutoDefault(true);
        getIniFromLink->setDefault(false);
        getIniFromLink->setFlat(false);
        zFin = new QDoubleSpinBox(tabPathPoints);
        zFin->setObjectName(QString::fromUtf8("zFin"));
        zFin->setGeometry(QRect(150, 76, 80, 22));
        zFin->setDecimals(6);
        zFin->setMinimum(-10);
        zFin->setMaximum(10);
        getFinFromLink = new QPushButton(tabPathPoints);
        getFinFromLink->setObjectName(QString::fromUtf8("getFinFromLink"));
        getFinFromLink->setGeometry(QRect(129, 104, 106, 35));
        getFinFromLink->setIcon(icon2);
        getFinFromLink->setIconSize(QSize(24, 24));
        getFinFromLink->setCheckable(false);
        getFinFromLink->setAutoDefault(true);
        getFinFromLink->setDefault(false);
        getFinFromLink->setFlat(false);
        yIni = new QDoubleSpinBox(tabPathPoints);
        yIni->setObjectName(QString::fromUtf8("yIni"));
        yIni->setGeometry(QRect(30, 54, 80, 22));
        yIni->setDecimals(6);
        yIni->setMinimum(-10);
        yIni->setMaximum(10);
        zIni = new QDoubleSpinBox(tabPathPoints);
        zIni->setObjectName(QString::fromUtf8("zIni"));
        zIni->setGeometry(QRect(30, 76, 80, 22));
        zIni->setDecimals(6);
        zIni->setMinimum(-10);
        zIni->setMaximum(10);
        yInilabel = new QLabel(tabPathPoints);
        yInilabel->setObjectName(QString::fromUtf8("yInilabel"));
        yInilabel->setGeometry(QRect(13, 56, 10, 16));
        yFinlabel = new QLabel(tabPathPoints);
        yFinlabel->setObjectName(QString::fromUtf8("yFinlabel"));
        yFinlabel->setGeometry(QRect(131, 58, 10, 16));
        yFin = new QDoubleSpinBox(tabPathPoints);
        yFin->setObjectName(QString::fromUtf8("yFin"));
        yFin->setGeometry(QRect(150, 54, 80, 22));
        yFin->setDecimals(6);
        yFin->setMinimum(-10);
        yFin->setMaximum(10);
        zInilabel = new QLabel(tabPathPoints);
        zInilabel->setObjectName(QString::fromUtf8("zInilabel"));
        zInilabel->setGeometry(QRect(14, 79, 10, 16));
        xInilabel = new QLabel(tabPathPoints);
        xInilabel->setObjectName(QString::fromUtf8("xInilabel"));
        xInilabel->setGeometry(QRect(14, 35, 10, 16));
        pInilabel = new QLabel(tabPathPoints);
        pInilabel->setObjectName(QString::fromUtf8("pInilabel"));
        pInilabel->setGeometry(QRect(17, 7, 91, 20));
        pInilabel->setAlignment(Qt::AlignCenter);
        pFinlabel = new QLabel(tabPathPoints);
        pFinlabel->setObjectName(QString::fromUtf8("pFinlabel"));
        pFinlabel->setGeometry(QRect(133, 7, 91, 20));
        pFinlabel->setAlignment(Qt::AlignCenter);
        line = new QFrame(tabPathPoints);
        line->setObjectName(QString::fromUtf8("line"));
        line->setGeometry(QRect(111, 14, 20, 121));
        line->setFrameShape(QFrame::VLine);
        line->setFrameShadow(QFrame::Sunken);
        spinPoints = new QSpinBox(tabPathPoints);
        spinPoints->setObjectName(QString::fromUtf8("spinPoints"));
        spinPoints->setGeometry(QRect(181, 150, 51, 22));
        spinPoints->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        spinPoints->setButtonSymbols(QAbstractSpinBox::UpDownArrows);
        spinPoints->setAccelerated(true);
        spinPoints->setMinimum(2);
        spinPoints->setMaximum(10000);
        spinPoints->setValue(2);
        label = new QLabel(tabPathPoints);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(90, 151, 91, 20));
        tabWidget->addTab(tabPathPoints, QString());
        cancel = new QPushButton(QDynDialogPath);
        cancel->setObjectName(QString::fromUtf8("cancel"));
        cancel->setGeometry(QRect(166, 221, 81, 35));
        QIcon icon3;
        icon3.addFile(QString::fromUtf8(":/resources/icons/cancel.png"), QSize(), QIcon::Normal, QIcon::Off);
        cancel->setIcon(icon3);
        cancel->setIconSize(QSize(24, 24));
        cancel->setCheckable(false);
        cancel->setAutoDefault(true);
        cancel->setDefault(false);
        cancel->setFlat(false);
        ok = new QPushButton(QDynDialogPath);
        ok->setObjectName(QString::fromUtf8("ok"));
        ok->setGeometry(QRect(78, 221, 81, 35));
        ok->setStyleSheet(QString::fromUtf8(""));
        QIcon icon4;
        icon4.addFile(QString::fromUtf8(":/resources/icons/ok.png"), QSize(), QIcon::Normal, QIcon::Off);
        ok->setIcon(icon4);
        ok->setIconSize(QSize(24, 24));
        ok->setCheckable(false);
        ok->setAutoDefault(true);
        ok->setDefault(false);
        ok->setFlat(false);
        line_2 = new QFrame(QDynDialogPath);
        line_2->setObjectName(QString::fromUtf8("line_2"));
        line_2->setGeometry(QRect(20, 198, 225, 31));
        line_2->setFrameShape(QFrame::HLine);
        line_2->setFrameShadow(QFrame::Sunken);
        QWidget::setTabOrder(tabWidget, pathFilename);
        QWidget::setTabOrder(pathFilename, pathOpenFile);
        QWidget::setTabOrder(pathOpenFile, pathFileTextExample);
        QWidget::setTabOrder(pathFileTextExample, pathFileTextExample_2);
        QWidget::setTabOrder(pathFileTextExample_2, xIni);
        QWidget::setTabOrder(xIni, yIni);
        QWidget::setTabOrder(yIni, zIni);
        QWidget::setTabOrder(zIni, getIniFromLink);
        QWidget::setTabOrder(getIniFromLink, xFin);
        QWidget::setTabOrder(xFin, yFin);
        QWidget::setTabOrder(yFin, zFin);
        QWidget::setTabOrder(zFin, getFinFromLink);
        QWidget::setTabOrder(getFinFromLink, spinPoints);
        QWidget::setTabOrder(spinPoints, ok);
        QWidget::setTabOrder(ok, cancel);

        retranslateUi(QDynDialogPath);

        tabWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(QDynDialogPath);
    } // setupUi

    void retranslateUi(QDialog *QDynDialogPath)
    {
        QDynDialogPath->setWindowTitle(QApplication::translate("QDynDialogPath", "Add new Path...", 0, QApplication::UnicodeUTF8));
        pathOpenFile->setText(QString());
        pathFilelabel->setText(QApplication::translate("QDynDialogPath", "Filename:", 0, QApplication::UnicodeUTF8));
        pathFileLabelInfo->setText(QApplication::translate("QDynDialogPath", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'MS Shell Dlg 2'; font-size:8.25pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:8pt;\">The file must be a .txt file with coordinates separated by a single space or tab (\\t):</span></p></body></html>", 0, QApplication::UnicodeUTF8));
        pathFileTextExample->setHtml(QApplication::translate("QDynDialogPath", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'MS Shell Dlg 2'; font-size:8.25pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:8pt;\">x</span><span style=\" font-size:8pt; vertical-align:sub;\">0</span><span style=\" font-size:8pt;\"> y</span><span style=\" font-size:8pt; vertical-align:sub;\">0</span><span style=\" font-size:8pt;\"> z</span><span style=\" font-size:8pt; vertical-align:sub;\">0</span></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:8pt;\">x</span><span style=\" font-size:8pt; vertical-align:sub;\">1</span><span style=\" font-size:8pt"
                        ";\"> y</span><span style=\" font-size:8pt; vertical-align:sub;\">1</span><span style=\" font-size:8pt;\"> z</span><span style=\" font-size:8pt; vertical-align:sub;\">1</span></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:8pt;\">...</span></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:8pt;\">x</span><span style=\" font-size:8pt; vertical-align:sub;\">n</span><span style=\" font-size:8pt;\"> y</span><span style=\" font-size:8pt; vertical-align:sub;\">n</span><span style=\" font-size:8pt;\"> z</span><span style=\" font-size:8pt; vertical-align:sub;\">n</span></p></body></html>", 0, QApplication::UnicodeUTF8));
        pathFileTextExample_2->setHtml(QApplication::translate("QDynDialogPath", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'MS Shell Dlg 2'; font-size:8.25pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:8pt;\">0 0 0</span></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:8pt;\">1 1 1</span></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:8pt;\">1.2 1.2 1.2</span></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:8pt;\">"
                        "2.45 2.45 2.45</span></p></body></html>", 0, QApplication::UnicodeUTF8));
        tabWidget->setTabText(tabWidget->indexOf(tabPathFile), QApplication::translate("QDynDialogPath", "From .txt file", 0, QApplication::UnicodeUTF8));
        xIni->setSuffix(QApplication::translate("QDynDialogPath", " m", 0, QApplication::UnicodeUTF8));
        xFin->setSuffix(QApplication::translate("QDynDialogPath", " m", 0, QApplication::UnicodeUTF8));
        xFinlabel->setText(QApplication::translate("QDynDialogPath", "x:", 0, QApplication::UnicodeUTF8));
        zFinlabel->setText(QApplication::translate("QDynDialogPath", "z:", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        getIniFromLink->setToolTip(QApplication::translate("QDynDialogPath", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'MS Shell Dlg 2'; font-size:8.25pt; font-weight:400; font-style:normal;\">\n"
"<p align=\"justify\" style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">Gets the actual position of the frame of reference attached to the selected link. If a robot or a robot property is selected, the robot's end effector's frame of reference's position will be taken.</p></body></html>", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        getIniFromLink->setText(QApplication::translate("QDynDialogPath", "Get from Link", 0, QApplication::UnicodeUTF8));
        zFin->setSuffix(QApplication::translate("QDynDialogPath", " m", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        getFinFromLink->setToolTip(QApplication::translate("QDynDialogPath", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'MS Shell Dlg 2'; font-size:8.25pt; font-weight:400; font-style:normal;\">\n"
"<p align=\"justify\" style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">Gets the actual position of the frame of reference attached to the selected link. If a robot or a robot property is selected, the robot's end effector's frame of reference's position will be taken.</p></body></html>", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        getFinFromLink->setText(QApplication::translate("QDynDialogPath", "Get from Link", 0, QApplication::UnicodeUTF8));
        yIni->setSuffix(QApplication::translate("QDynDialogPath", " m", 0, QApplication::UnicodeUTF8));
        zIni->setSuffix(QApplication::translate("QDynDialogPath", " m", 0, QApplication::UnicodeUTF8));
        yInilabel->setText(QApplication::translate("QDynDialogPath", "y:", 0, QApplication::UnicodeUTF8));
        yFinlabel->setText(QApplication::translate("QDynDialogPath", "y:", 0, QApplication::UnicodeUTF8));
        yFin->setSuffix(QApplication::translate("QDynDialogPath", " m", 0, QApplication::UnicodeUTF8));
        zInilabel->setText(QApplication::translate("QDynDialogPath", "z:", 0, QApplication::UnicodeUTF8));
        xInilabel->setText(QApplication::translate("QDynDialogPath", "x:", 0, QApplication::UnicodeUTF8));
        pInilabel->setText(QApplication::translate("QDynDialogPath", "Starting Point", 0, QApplication::UnicodeUTF8));
        pFinlabel->setText(QApplication::translate("QDynDialogPath", "End Point", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("QDynDialogPath", "Number of Points:", 0, QApplication::UnicodeUTF8));
        tabWidget->setTabText(tabWidget->indexOf(tabPathPoints), QApplication::translate("QDynDialogPath", "From two points", 0, QApplication::UnicodeUTF8));
        cancel->setText(QApplication::translate("QDynDialogPath", "  Cancel", 0, QApplication::UnicodeUTF8));
        ok->setText(QApplication::translate("QDynDialogPath", "   OK    ", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class QDynDialogPath: public Ui_QDynDialogPath {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_QDYNDIALOGPATH_H
