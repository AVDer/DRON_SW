#include <QApplication>
#include "MainWindow.h"
#include "QuickQwtPlot.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    qmlRegisterType<QuickQwtPlot>("QuickQwt", 1, 0, "QuickQwtPlot");
    MainWindow w;
    w.show();

    return app.exec();
}

