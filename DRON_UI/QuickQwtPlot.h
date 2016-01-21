#ifndef QUICKQWTPLOT_H
#define QUICKQWTPLOT_H

#include <QQuickPaintedItem>

#include "Libs/qwt/include/qwt_plot_magnifier.h"
#include "Libs/qwt/include/qwt_plot_panner.h"
#include "Libs/qwt/include/qwt_plot_grid.h"
#include "Libs/qwt/include/qwt_symbol.h"

#include "GraphCurve.h"

class QwtPlot;

class QuickQwtPlot : public QQuickPaintedItem
{
    Q_OBJECT
    Q_PROPERTY(QString titleYLeft READ titleYLeft WRITE setAxisYLeft)
    Q_PROPERTY(QString titleYRight READ titleYRight WRITE setAxisYRight)
    Q_PROPERTY(QString titleXBottom READ titleXBottom WRITE setAxisXBottom)
    Q_PROPERTY(QString titleXTop READ titleXTop WRITE setAxisXTop)
    Q_PROPERTY(QString title READ title WRITE setTitle)
    Q_PROPERTY(double xMin READ xMin WRITE setXMin NOTIFY xMinChanged)
    Q_PROPERTY(double xMax READ xMax WRITE setXMax NOTIFY xMaxChanged)
    Q_PROPERTY(double yMin READ yMin WRITE setYMin NOTIFY yMinChanged)
    Q_PROPERTY(double yMax READ yMax WRITE setYMax NOTIFY yMaxChanged)

public:
    QuickQwtPlot(QQuickItem *parent = 0);
    ~QuickQwtPlot();

    void paint(QPainter *painter);

    Q_INVOKABLE void setAutoScale();

    QwtPlot *getPlot();

    QString titleXBottom() const;
    QString titleXTop() const;
    QString titleYRight() const;
    QString titleYLeft() const;
    QString title() const;
    double xMin() const;
    void setXMin(double x_min);
    double xMax() const;
    void setXMax(double x_max);
    double yMin() const;
    void setYMin(double y_min);
    double yMax() const;
    void setYMax(double y_max);

public slots:
    void heightChanged();
    void widthChanged();
    void setAxisXBottom(QString arg);
    void setAxisXTop(QString arg);
    void setAxisYRight(QString arg);
    void setAxisYLeft(QString arg);
    void setTitle(QString arg);

signals:
    void xMinChanged();
    void xMaxChanged();
    void yMinChanged();
    void yMaxChanged();

private:
    QwtPlot *mPlot;
    QwtPlotMagnifier* magnifier_;
    QwtPlotPanner* panner_;
    QwtPlotGrid* grid_;
    double x_min_ = 0;
    double x_max_ = 1000;
    double y_min_ = 0;
    double y_max_ = 1000;
};

#endif // QUICKQWTPLOT_H
