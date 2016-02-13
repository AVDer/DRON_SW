#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <memory>

#include <QBoxLayout>
#include <QComboBox>
#include <QFileDialog>
#include <QGridLayout>
#include <QGroupBox>
#include <QLabel>
#include <QMainWindow>
#include <QPushButton>
#include <QRadioButton>
#include <QSpinBox>
#include <QSplitter>
#include <QString>
#include <QTabWidget>

#include "GraphCurve.h"
#include "LimitsInput.h"
#include "Processor.h"
#include "SimpleButton.h"

#include "Libs/qwt/include/qwt_plot_magnifier.h"
#include "Libs/qwt/include/qwt_plot_panner.h"
#include "Libs/qwt/include/qwt_plot_grid.h"
#include "Libs/qwt/include/qwt_symbol.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
protected:
    void resizeEvent(QResizeEvent *);
private:
    void create_widgets();
    void create_layouts();
    void create_connections();
    void adjust_widgets();

    void store_settings();
    void restore_settings();
    void show_alarm(QString message);

    void closeEvent(QCloseEvent * event);

    QWidget *meas_widget_;
    QWidget *settings_widget_;
    QWidget *line_widget_;

    QWidget *left_widget_;
    QSplitter *main_splitter_;
    SimpleButton *start_button_;
    SimpleButton *pause_button_;
    SimpleButton *stop_button_;
    SimpleButton *damper_open_button_;
    SimpleButton *damper_close_button_;

    QRadioButton *point_scan_;
    QRadioButton *integral_scan_;
    QRadioButton *adjust_scan_;

    QRadioButton *line_style_;
    QRadioButton *point_style_;

    LimitsInput *min_x_edit_;
    LimitsInput *max_x_edit_;
    LimitsInput *min_y_edit_;
    LimitsInput *max_y_edit_;
    LimitsInput *start_angle_;
    LimitsInput *stop_angle_;
    LimitsInput *step_;
    LimitsInput *exposition_;
    LimitsInput *braking_time_;
    LimitsInput *delay_;
    QLabel *directory_;
    QLineEdit *filename_;
    QPushButton *browse_button_;

    QLineEdit *voltage_;
    QSpinBox *line_width_;
    QComboBox *com_port_box_;

    QwtPlot *graph_plot_;
    QwtPlotGrid *graph_grid_;
    QwtPlotMagnifier *graph_magnifier_;
    QwtPlotPanner *graph_panner_;

    QTabWidget *right_panel_;

    QGroupBox *mode_group_box_;
    QGroupBox *angle_group_box_;

    QVBoxLayout *left_panel_layout_;
    QHBoxLayout *button_layout_;
    QGridLayout *graph_layout_;
    QGridLayout *angle_layout_;
    QGridLayout *settings_layout_;
    QVBoxLayout *settings_v_layout_;
    QGridLayout *line_layout_;
    QVBoxLayout *line_v_layout_;
    QVBoxLayout *mode_layout_;
    QVBoxLayout *meas_layout_;
    QHBoxLayout *damper_layout_;

    Processor *processor_;

    QSettings *settings_;
    QString file_name_;
signals:

public slots:
    void start_button_pressed();
    void stop_button_pressed();
    void open_damper_pressed();
    void close_damper_pressed();
    void file_browse();
    void x_axis_change();
    void y_axis_change();
    void line_style_changed();
};

#endif // MAINWINDOW_H
