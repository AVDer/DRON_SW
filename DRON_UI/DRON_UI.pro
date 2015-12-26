TEMPLATE = app

QT += qml quick widgets
CONFIG += c++11

SOURCES += main.cpp \
    QuickQwtPlot.cpp \
    QuickCurve.cpp \
    MainWindow.cpp

RESOURCES += qml.qrc

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Default rules for deployment.
include(deployment.pri)

HEADERS += \
    QuickQwtPlot.h \
    QuickCurve.h \
    MainWindow.h

INCLUDEPATH += $$PWD/Libs/qwt/include

LIBS += -L$$PWD/Libs/qwt/lib/ -lqwtd
