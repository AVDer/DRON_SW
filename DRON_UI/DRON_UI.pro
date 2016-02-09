QT += core gui widgets
QT -= qml quick opengl webkit
QMAKE_CXXFLAGS += -std=c++11

TEMPLATE = app

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
LIBS += -lqwt5
}
win32 {
LIBS += -lqwt5
}

DISTFILES +=
