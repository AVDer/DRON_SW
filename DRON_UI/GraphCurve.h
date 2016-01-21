#ifndef GRAPHCURVE_H
#define GRAPHCURVE_H

#include <algorithm>
#include <utility>
#include <vector>

#include "Libs/qwt/include/qwt_plot.h"
#include "Libs/qwt/include/qwt_plot_curve.h"

class QuickQwtPlot;
class GraphCurve;
GraphCurve* get_graph_curve();

class GraphCurve
{
public:
    GraphCurve();
    void set_plot(QuickQwtPlot* plot);
    void add_point(double x, double y);
    void set_style(int style);
    void set_size(int size);
    std::pair<double, double> axis_x_range();

private:
    const QColor kGraphColor = Qt::red;
    QuickQwtPlot* plot_;
    QwtPlotCurve* curve_;
    std::vector<double> data_x;
    std::vector<double> data_y;
    int size_ = 1;
    int style_ = 1;
};

#endif // GRAPHCURVE_H
