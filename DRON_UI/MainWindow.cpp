#include "MainWindow.h"

#include <QQmlContext>


MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent)
{
    resize(1600, 600);
    view = new QQuickView();
    container = QWidget::createWindowContainer(view, this);
    view->setSource(QUrl("qrc:/main.qml"));

    this->setCentralWidget(container);
}

MainWindow::~MainWindow()
{
}

void MainWindow::resizeEvent(QResizeEvent *ev)
{
    QMainWindow::resizeEvent(ev);
}

