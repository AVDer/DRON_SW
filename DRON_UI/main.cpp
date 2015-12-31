#include <QApplication>
#include "MainWindow.h"
#include "QuickQwtPlot.h"
#include "FileManager.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    qmlRegisterType<QuickQwtPlot>("QuickQwt", 1, 0, "QuickQwtPlot");
    qmlRegisterType<FileManager>("dron.FileManager", 1, 0, "FileManager");
    MainWindow w;
    w.show();

    return app.exec();
}

