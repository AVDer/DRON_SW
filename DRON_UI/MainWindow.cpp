#include "MainWindow.h"

#include <QQuickView>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent)
{
    QQuickView *view = new QQuickView();
    QWidget *container = QWidget::createWindowContainer(view, this);
    container->setFocusPolicy(Qt::TabFocus);
    view->setSource(QUrl("qrc:/main.qml"));
    this->setCentralWidget(container);
}

MainWindow::~MainWindow()
{

}

