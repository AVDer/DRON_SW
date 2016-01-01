TEMPLATE = app

QT += qml quick widgets
CONFIG += c++11 qwt

SOURCES += main.cpp \
    QuickQwtPlot.cpp \
    QuickCurve.cpp \
    MainWindow.cpp \
    FileManager.cpp \
    MeasureSettings.cpp \
    Processor.cpp

RESOURCES += qml.qrc

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Default rules for deployment.
include(deployment.pri)

HEADERS += \
    QuickQwtPlot.h \
    QuickCurve.h \
    MainWindow.h \
    FileManager.h \
    MeasureSettings.h \
    Processor.h

INCLUDEPATH += $$PWD/Libs/qwt/include

LIBS += -L$$PWD/Libs/qwt/lib/

unix {
LIBS += -lqwt
}
win32 {
LIBS += -lqwtd
}

DISTFILES +=
