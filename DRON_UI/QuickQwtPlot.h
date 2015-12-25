#ifndef QUICKQWTPLOT_H
#define QUICKQWTPLOT_H

#include <QQuickPaintedItem>

class QwtPlot;

class QuickQwtPlot : public QQuickPaintedItem
{
    Q_OBJECT
    Q_PROPERTY(QString titleYLeft READ titleYLeft WRITE setAxisYLeft)
    Q_PROPERTY(QString titleYRight READ titleYRight WRITE setAxisYRight)
    Q_PROPERTY(QString titleXBottom READ titleXBottom WRITE setAxisXBottom)
    Q_PROPERTY(QString titleXTop READ titleXTop WRITE setAxisXTop)
    Q_PROPERTY(QString title READ title WRITE setTitle)

public:
    QuickQwtPlot(QQuickItem *parent = 0);
    ~QuickQwtPlot();

    void paint(QPainter *painter);

    QwtPlot *getPlot();

    QString titleXBottom() const;
    QString titleXTop() const;
    QString titleYRight() const;
    QString titleYLeft() const;
    QString title() const;

public slots:
    void heightChanged();
    void widthChanged();
    void setAxisXBottom(QString arg);
    void setAxisXTop(QString arg);
    void setAxisYRight(QString arg);
    void setAxisYLeft(QString arg);
    void setTitle(QString arg);

private:
    QwtPlot *mPlot;
};

#endif // QUICKQWTPLOT_H
