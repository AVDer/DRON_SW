#include "QuickCurve.h"

#include "QuickQwtPlot.h"

#include <QDebug>

QuickCurve::QuickCurve(QQuickItem *parent) :
    QQuickItem(parent)
{
    mCurve = new QwtPlotCurve;
    mCurve->setRenderHint(QwtPlotItem::RenderAntialiased, true);
}

QuickCurve::~QuickCurve()
{
    delete mCurve;
}

QVariantList QuickCurve::attach() const
{
    return mPlots;
}

QString QuickCurve::title() const
{
    return mCurve->title().text();
}

QColor QuickCurve::color() const
{
    return mCurve->pen().color();
}

int QuickCurve::lineWidth() const
{
    return mCurve->pen().width();
}

QwtPlotCurve::CurveStyle QuickCurve::NoCurve() const
{
    return QwtPlotCurve::NoCurve;
}

QwtPlotCurve::CurveStyle QuickCurve::style() const
{
    return mCurve->style();
}

QwtPlotCurve::CurveStyle QuickCurve::Lines() const
{
    return QwtPlotCurve::Lines;
}

QwtPlotCurve::CurveStyle QuickCurve::Sticks() const
{
    return QwtPlotCurve::Sticks;
}

QwtPlotCurve::CurveStyle QuickCurve::Steps() const
{
    return QwtPlotCurve::Steps;
}

QwtPlotCurve::CurveStyle QuickCurve::Dots() const
{
    return QwtPlotCurve::Dots;
}

void QuickCurve::setAttach(QVariantList arg)
{
    foreach (QVariant item, arg) {
        if (item.canConvert<QuickQwtPlot *>()) {
            qDebug() << "attach plot";
            QuickQwtPlot *plot = item.value<QuickQwtPlot *>();
            mCurve->attach(plot->getPlot());
            mPlots.append(item);
        }
    }
}

QwtPlotCurve *QuickCurve::getCurve() const
{
    return mCurve;
}

void QuickCurve::setStyle(QwtPlotCurve::CurveStyle arg)
{
    mCurve->setStyle(arg);
}

void QuickCurve::replote()
{
    foreach (QVariant item, mPlots) {
        if (item.canConvert<QuickQwtPlot *>()) {
            QuickQwtPlot *plot = item.value<QuickQwtPlot *>();
            plot->update();
        }
    }
}

void QuickCurve::setTitle(QString arg)
{
    mCurve->setTitle(arg);
}

void QuickCurve::setColor(QColor arg)
{
    mCurve->setPen(arg, mCurve->pen().width());
}

void QuickCurve::setLineWidth(int arg)
{
    mCurve->setPen(mCurve->pen().color(), arg);
}
