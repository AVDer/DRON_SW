#ifndef GRAPHCURVE_H
#define GRAPHCURVE_H

#define QWT_VER_5

#include <algorithm>
#include <utility>
#include <vector>

#include "qwt_plot.h"
#include "qwt_plot_curve.h"
#include "qwt_symbol.h"

#define kGraphColor Qt::red

class QuickQwtPlot;
class GraphCurve;
GraphCurve* get_graph_curve();

class GraphCurve
{
public:
    GraphCurve();
    void set_plot(QwtPlot *plot);
    void add_point(double x, double y);
    void redraw();
    void clear();
    void set_style(int style);
    void set_size(int size);
    std::pair<double, double> axis_x_range();

private:
    QwtPlot* plot_;
    QwtPlotCurve* curve_;
    std::vector<double> data_x;
    std::vector<double> data_y;
    int size_;
    int style_;
};

#endif // GRAPHCURVE_H
