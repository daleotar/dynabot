#-------------------------------------------------
#
# Project created by QtCreator 2011-06-13T17:00:02
#
#-------------------------------------------------

QT  += core gui
QT  += opengl
QT  += qwt
QT  += xml

TARGET = ../../bin/DynaBOT

TEMPLATE = app

SOURCES += main.cpp\
        mainwindow.cpp \
    Classes\QDynScene.cpp \
    Classes\QDynMesh.cpp \
    RAPID/RAPID.C \
    RAPID/overlap.C \
    RAPID/collide.C \
    RAPID/build.C \
    Classes/QDynRobot.cpp \
    Classes/QDynObstacle.cpp \
    Classes/QDynLink.cpp \
    Classes/QDynMath.cpp \
    Classes/QDynPath.cpp \
    Classes/QDynGeneric.cpp \
    Classes/QDynRobotPath.cpp \
    Classes/QDynMatrix.cpp \
    Widgets/QDynWindowStyles.cpp \
    Widgets/QDynSpinSlider.cpp \
    Widgets/QDynSpinSliderDelegate.cpp \
    Widgets/QDynDialogPath.cpp \
    Widgets/QDynLineEditDelegate.cpp \
    Widgets/QDynDialogRobotPath.cpp \
    Widgets/QDynDialogRobotTable.cpp \
    Threads/QDynRobotThread.cpp \
    Widgets/QDynRobotTableDelegate.cpp

HEADERS  += mainwindow.h \
    Classes\QDynScene.h \
    Classes\QDynMesh.h \
    RAPID/RAPID_version.H \
    RAPID/RAPID_private.H \
    RAPID/RAPID.H \
    RAPID/overlap.H \
    RAPID/obb.H \
    RAPID/moments.H \
    RAPID/matvec.H \
    Classes/QDynRobot.h \
    Classes/QDynObstacle.h \
    Classes/QDynLink.h \
    Classes/QDynMath.h \
    Widgets/QDynWindowStyles.h \
    Widgets/QDynSpinSlider.h \
    Widgets/QDynSpinSliderDelegate.h \
    Classes/QDynPath.h \
    Widgets/QDynDialogPath.h \
    Classes/QDynGeneric.h \
    Widgets/QDynLineEditDelegate.h \
    Classes/QDynRobotPath.h \
    Widgets/QDynDialogRobotPath.h \
    Threads/QDynRobotThread.h \
    Classes/QDynMatrix.h \
    Widgets/QDynDialogRobotTable.h \
    Widgets/QDynRobotTableDelegate.h

FORMS    += mainwindow.ui \
    Widgets/QDynDialogPath.ui \
    Widgets/QDynDialogRobotPath.ui \
    Widgets/QDynDialogRobotTable.ui

INCLUDEPATH += C:/Qt/qwt-6.0.0/include
DEPENDPATH += C:/Qt/qwt-6.0.0/lib
LIBS += -LC:/Qt/qwt-6.0.0/lib

win32{
    CONFIG(debug, debug|release){
    LIBS += -lqwtd
    }
    else{
    LIBS += -lqwt
    }
}

RESOURCES += \
    Resources.qrc
