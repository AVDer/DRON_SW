#ifndef QUICKCURVE_H
#define QUICKCURVE_H


#include "qwt_plot_curve.h"

#include <QQuickItem>
#include <QMetaType>

class QuickCurve : public QQuickItem
{
    Q_OBJECT
    Q_PROPERTY(QVariantList attach READ attach WRITE setAttach)
    Q_PROPERTY(QString title READ title WRITE setTitle)
    Q_PROPERTY(QColor color READ color WRITE setColor)
    Q_PROPERTY(int lineWidth READ lineWidth WRITE setLineWidth)
    Q_PROPERTY(QwtPlotCurve::CurveStyle style READ style WRITE setStyle)
    Q_PROPERTY(QwtPlotCurve::CurveStyle NoCurve READ NoCurve)
    Q_PROPERTY(QwtPlotCurve::CurveStyle Lines READ Lines)
    Q_PROPERTY(QwtPlotCurve::CurveStyle Sticks READ Sticks)
    Q_PROPERTY(QwtPlotCurve::CurveStyle Steps READ Steps)
    Q_PROPERTY(QwtPlotCurve::CurveStyle Dots READ Dots)

public:
    explicit QuickCurve(QQuickItem *parent = 0);
    ~QuickCurve();

    QVariantList attach() const;
    QString title() const;
    QColor color() const;
    int lineWidth() const;

    QwtPlotCurve::CurveStyle NoCurve() const;
    QwtPlotCurve::CurveStyle style() const;
    QwtPlotCurve::CurveStyle Lines() const;
    QwtPlotCurve::CurveStyle Sticks() const;
    QwtPlotCurve::CurveStyle Steps() const;
    QwtPlotCurve::CurveStyle Dots() const;

signals:

public slots:
    void setAttach(QVariantList arg);
    void setTitle(QString arg);
    void setColor(QColor arg);
    void setLineWidth(int arg);
    void setStyle(QwtPlotCurve::CurveStyle arg);

protected:
    void replote();
    QwtPlotCurve *getCurve() const;

private:
    QwtPlotCurve *mCurve;
    QVariantList mPlots;
};

Q_DECLARE_METATYPE(QwtPlotCurve::CurveStyle)

#endif // QUICKCURVE_H
