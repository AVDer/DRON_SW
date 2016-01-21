#include "GraphCurve.h"

#include "QuickQwtPlot.h"

GraphCurve* get_graph_curve() {
    static GraphCurve graph_curve_;
    return &graph_curve_;
}

GraphCurve::GraphCurve() {
    curve_ = new QwtPlotCurve();
}

void GraphCurve::set_plot(QuickQwtPlot *plot) {
    plot_ = plot;
    curve_->attach(plot->getPlot());
}

void GraphCurve::add_point(double x, double y) {
    data_x.push_back(x);
    data_y.push_back(y);
    curve_->setSamples(data_x.data(), data_y.data(), data_x.size());
    plot_->update();
}
