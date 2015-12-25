#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlEngine>

#include "QuickQwtPlot.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);
    QQmlApplicationEngine engine;
    qmlRegisterType<QuickQwtPlot>("QuickQwt", 1, 0, "QuickQwtPlot");
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));

    return app.exec();
}

