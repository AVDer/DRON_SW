#include "QuickQwtPlot.h"

#include "Libs/qwt/include/qwt_legend.h"
#include "Libs/qwt/include/qwt_plot_canvas.h"
#include "Libs/qwt/include/qwt_plot.h"
#include "Libs/qwt/include/qwt.h"

#include <QDebug>

QuickQwtPlot::QuickQwtPlot(QQuickItem *parent)  : QQuickPaintedItem(parent)
{
    mPlot = new QwtPlot;

    mPlot->setAttribute(Qt::WA_NoSystemBackground);

    connect(this, SIGNAL(heightChanged()), this, SLOT(heightChanged()));
    connect(this, SIGNAL(widthChanged()), this, SLOT(widthChanged()));

    mPlot->insertLegend(new QwtLegend(), QwtPlot::BottomLegend);

    // canvas
    QwtPlotCanvas *canvas = new QwtPlotCanvas();
    canvas->setLineWidth(0);
    canvas->setFrameStyle(QFrame::Box | QFrame::Plain);
    canvas->setBorderRadius(4);
    QPalette canvasPalette(Qt::white);
    canvas->setPalette(canvasPalette);
    mPlot->setCanvas(canvas);

    mPlot->setAutoReplot(true);
}

QuickQwtPlot::~QuickQwtPlot()
{
    delete mPlot;
}

void QuickQwtPlot::paint(QPainter *painter)
{
    painter->setRenderHints(QPainter::Antialiasing, true);
    mPlot->render(painter);
}

QwtPlot *QuickQwtPlot::getPlot()
{
    return mPlot;
}

QString QuickQwtPlot::titleXBottom() const
{
    return mPlot->axisTitle(QwtPlot::xBottom).text();
}

QString QuickQwtPlot::titleXTop() const
{
    return mPlot->axisTitle(QwtPlot::xTop).text();
}

QString QuickQwtPlot::titleYRight() const
{
    return mPlot->axisTitle(QwtPlot::yRight).text();
}

QString QuickQwtPlot::titleYLeft() const
{
    return mPlot->axisTitle(QwtPlot::yLeft).text();
}

void QuickQwtPlot::heightChanged()
{
    mPlot->setFixedHeight(contentsBoundingRect().height());
}

void QuickQwtPlot::widthChanged()
{
    mPlot->setFixedWidth(contentsBoundingRect().width());
}

void QuickQwtPlot::setAxisXBottom(QString arg)
{
    mPlot->setAxisTitle(QwtPlot::xBottom, arg);
}

void QuickQwtPlot::setAxisXTop(QString arg)
{
    mPlot->setAxisTitle(QwtPlot::xTop, arg);
}

void QuickQwtPlot::setAxisYRight(QString arg)
{
    mPlot->setAxisTitle(QwtPlot::yRight, arg);
}

void QuickQwtPlot::setAxisYLeft(QString arg)
{
    mPlot->setAxisTitle(QwtPlot::yLeft, arg);
}

QString QuickQwtPlot::title() const
{
    return mPlot->title().text();
}

void QuickQwtPlot::setTitle(QString arg)
{
    mPlot->setTitle(arg);
}
