TEMPLATE = app

QT += core gui widgets multimedia
QT -= qml quick opengl webkit
CONFIG += c++11 qwt
CONFIG += static staticlib

SOURCES += main.cpp \
    MainWindow.cpp \
    FileManager.cpp \
    MeasureSettings.cpp \
    Processor.cpp \
    Communication.cpp \
    GraphCurve.cpp \
    SimpleButton.cpp \
    LimitsInput.cpp

RESOURCES +=

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Default rules for deployment.
include(deployment.pri)

HEADERS += \
    MainWindow.h \
    FileManager.h \
    MeasureSettings.h \
    Processor.h \
    Communication.h \
    GraphCurve.h \
    SimpleButton.h \
    LimitsInput.h

INCLUDEPATH += $$PWD/Libs/qwt/include

LIBS += -L$$PWD/Libs/qwt/lib/

unix {
LIBS += -lqwt
}
win32 {
LIBS += -lqwt
}

DISTFILES +=

include($$PWD/Libs/qextserialport/qextserialport.pri)

