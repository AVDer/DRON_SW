#ifndef GRAPHCURVE_H
#define GRAPHCURVE_H

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

private:
    QuickQwtPlot* plot_;
    QwtPlotCurve* curve_;
    std::vector<double> data_x;
    std::vector<double> data_y;
};

#endif // GRAPHCURVE_H
