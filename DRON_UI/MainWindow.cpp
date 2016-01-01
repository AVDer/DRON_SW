#include "MainWindow.h"

#include <QQmlContext>


MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent)
{
    resize(1200, 900);
    view = new QQuickView();
    container = QWidget::createWindowContainer(view, this);
    view->setSource(QUrl("qrc:/main.qml"));

    setCentralWidget(container);
}

MainWindow::~MainWindow()
{
}

void MainWindow::resizeEvent(QResizeEvent *ev)
{
    QMainWindow::resizeEvent(ev);
}

