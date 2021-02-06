#-------------------------------------------------
#
# Project created by QtCreator 2018-12-11T15:16:23
#
#-------------------------------------------------

QT  += core gui
#QT  += opengl       #使用opengl

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets  printsupport

TARGET = LXCustomPlot
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

#DEFINES += QCUSTOMPLOT_USE_OPENGL   #使用opengl

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += c++11

#LIBS += -L -llibfreeglut -lopengl32     #依赖opengl库文件


SOURCES += \
        main.cpp \
        LDrawSpectrum.cpp \
    qcustomplot.cpp \
    LXCustomPlot.cpp \
    LXTracer.cpp

HEADERS += \
        LDrawSpectrum.h \
    qcustomplot.h \
    LXCustomPlot.h \
    LXTracer.h


# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
