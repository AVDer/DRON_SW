QT += core gui widgets
QT -= qml quick opengl webkit

TEMPLATE = app

SOURCES += main.cpp \
    MainWindow.cpp \
    FileManager.cpp \
    MeasureSettings.cpp \
    Processor.cpp \
    Communication.cpp \
    GraphCurve.cpp \
    SimpleButton.cpp \
    LimitsInput.cpp \
    UartManager.cpp

RESOURCES +=

HEADERS += \
    MainWindow.h \
    FileManager.h \
    MeasureSettings.h \
    Processor.h \
    Communication.h \
    GraphCurve.h \
    SimpleButton.h \
    LimitsInput.h \
    Version.h \
    UartManager.h

INCLUDEPATH += $$PWD/Libs/qwt6/include

LIBS += -L$$PWD/Libs/qwt6/lib/

unix {
LIBS += -lqwt
}
win32 {
LIBS += -lqwt
}

DISTFILES +=

include($$PWD/Libs/qextserialport/qextserialport.pri)
