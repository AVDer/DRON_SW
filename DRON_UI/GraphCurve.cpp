#include "GraphCurve.h"

GraphCurve* get_graph_curve() {
    static GraphCurve graph_curve_;
    return &graph_curve_;
}

GraphCurve::GraphCurve() {
    curve_ = new QwtPlotCurve();
}

void GraphCurve::set_plot(QwtPlot *plot) {
    plot_ = plot;
    curve_->attach(plot);
    set_style(style_);
}

void GraphCurve::add_point(double x, double y) {
    data_x.push_back(x);
    data_y.push_back(y);
    curve_->setSamples(data_x.data(), data_y.data(), data_x.size());
    plot_->update();
}

void GraphCurve::clear() {
    data_x.clear();
    data_y.clear();
    curve_->setSamples(data_x.data(), data_y.data(), data_x.size());
    plot_->update();
}

void GraphCurve::set_style(int style) {
    style_ = style;
    if (style_ == 1) {
        curve_->setStyle(QwtPlotCurve::Lines);
        curve_->setPen(QPen(QBrush(kGraphColor), size_));
    }
    else {
        curve_->setStyle(QwtPlotCurve::Dots);
        curve_->setSymbol(new QwtSymbol(QwtSymbol::Ellipse, QBrush(kGraphColor), QPen(kGraphColor), QSize(size_, size_)));
    }
    plot_->update();
}

void GraphCurve::set_size(int size) {
    size_ = size;
    set_style(style_);
}

std::pair<double, double> GraphCurve::axis_x_range() {
    auto minmax = std::minmax_element(std::begin(data_x), std::end(data_x));
    return std::make_pair(*minmax.first, *minmax.second);
}
