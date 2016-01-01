#include <QApplication>
#include "MainWindow.h"
#include "QuickQwtPlot.h"
#include "FileManager.h"
#include "MeasureSettings.h"
#include "Processor.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    qmlRegisterType<QuickQwtPlot>("QuickQwt", 1, 0, "QuickQwtPlot");
    qmlRegisterType<FileManager>("dron.FileManager", 1, 0, "FileManager");
    qmlRegisterType<MeasureSettings>("dron.MeasureSettings", 1, 0, "MeasureSettings");
    qmlRegisterType<Processor>("dron.Processor", 1, 0, "Processor");
    MainWindow w;
    w.show();

    return app.exec();
}

