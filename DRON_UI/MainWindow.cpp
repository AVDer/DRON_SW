#include "MainWindow.h"

#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    settings_(new QSettings("StarCon", "DRON Control"))
{
    create_widgets();
    create_layouts();
    adjust_widgets();
    create_connections();

    restore_settings();

    setCentralWidget(main_splitter_);
    setWindowTitle(tr("DRON User Interface 2.2.0"));
}

MainWindow::~MainWindow() {
    delete processor_;
}

void MainWindow::resizeEvent(QResizeEvent *ev) {
    QMainWindow::resizeEvent(ev);
}

void MainWindow::create_widgets() {
    processor_ = new Processor;

    start_button_ = new SimpleButton(tr("Start"), ButtonID::Start);
    pause_button_ = new SimpleButton(tr("Pause"), ButtonID::Pause);
    stop_button_ = new SimpleButton(tr("Stop"), ButtonID::Stop);

    point_scan_ = new QRadioButton(tr("Point scan"), this);
    integral_scan_ = new QRadioButton(tr("Integral scan"), this);
    adjust_scan_ = new QRadioButton(tr("Adjustment"), this);

    line_style_ = new QRadioButton(tr("Line"), this);
    point_style_ = new QRadioButton(tr("Point"), this);
    line_width_ = new QSpinBox(this);
    com_port_box_ = new QComboBox(this);

    graph_plot_ = new QwtPlot(this);
    graph_grid_ = new QwtPlotGrid;
    graph_magnifier_ = new QwtPlotMagnifier(graph_plot_->canvas());
    graph_panner_ = new QwtPlotPanner(graph_plot_->canvas());

    min_x_edit_ = new LimitsInput(this);
    max_x_edit_ = new LimitsInput(this);
    min_y_edit_ = new LimitsInput(this);
    max_y_edit_ = new LimitsInput(this);
    start_angle_ = new LimitsInput(this);
    stop_angle_ = new LimitsInput(this);
    step_ = new LimitsInput(this);
    exposition_ = new LimitsInput(this);
    voltage_ = new QLineEdit(this);

    braking_time_ = new LimitsInput(this);
    delay_ = new LimitsInput(this);
    directory_ = new QLabel(this);
    filename_ = new QLineEdit(this);
    browse_button_ = new QPushButton(tr("Browse"), this);

    mode_group_box_ = new QGroupBox(tr("Mode"), this);
    angle_group_box_ = new QGroupBox(tr("Parameters"), this);
    meas_widget_ = new QWidget(this);
    settings_widget_ = new QWidget(this);
    line_widget_ = new QWidget(this);
    left_widget_ = new QWidget(this);
    main_splitter_ = new QSplitter(this);
    right_panel_ = new QTabWidget(this);
}

void MainWindow::create_layouts()
{
    left_panel_layout_ = new QVBoxLayout;
    button_layout_ = new QHBoxLayout;
    graph_layout_ = new QGridLayout;
    mode_layout_ = new QVBoxLayout;
    meas_layout_ = new QVBoxLayout;
    angle_layout_ = new QGridLayout;
    settings_layout_ = new QGridLayout;
    settings_v_layout_ = new QVBoxLayout;
    line_layout_ = new QGridLayout;
    line_v_layout_ = new QVBoxLayout;

    button_layout_->addStretch(-1);
    button_layout_->addWidget(start_button_);
    button_layout_->addWidget(pause_button_);
    button_layout_->addWidget(stop_button_);

    graph_layout_->addWidget(max_y_edit_, 0, 0);
    graph_layout_->addWidget(min_y_edit_, 2, 0);
    graph_layout_->addWidget(min_x_edit_, 3, 1);
    graph_layout_->addWidget(max_x_edit_, 3, 3);
    graph_layout_->addWidget(graph_plot_, 0, 1, 3, 3);
    graph_layout_->setColumnStretch(0, 1);
    graph_layout_->setColumnStretch(1, 1);
    graph_layout_->setColumnStretch(3, 1);
    graph_layout_->setColumnStretch(2, 8);

    left_panel_layout_->addLayout(graph_layout_);
    left_panel_layout_->addLayout(button_layout_);
    left_widget_->setLayout(left_panel_layout_);

    mode_layout_->addWidget(point_scan_);
    mode_layout_->addWidget(integral_scan_);
    mode_layout_->addWidget(adjust_scan_);
    mode_group_box_->setLayout(mode_layout_);
    meas_layout_->addWidget(mode_group_box_);

    angle_layout_->addWidget(new QLabel(tr("Start angle:")), 0, 0);
    angle_layout_->addWidget(start_angle_, 0, 1);
    angle_layout_->addWidget(new QLabel(tr("°")), 0, 2);
    angle_layout_->addWidget(new QLabel(tr("Stop angle:")), 1, 0);
    angle_layout_->addWidget(stop_angle_, 1, 1);
    angle_layout_->addWidget(new QLabel(tr("°")), 1, 2);
    angle_layout_->addWidget(new QLabel(tr("Step:")), 2, 0);
    angle_layout_->addWidget(step_, 2, 1);
    angle_layout_->addWidget(new QLabel(tr("x 0.01°")), 2, 2);
    angle_layout_->addWidget(new QLabel(tr("Exposition:")), 3, 0);
    angle_layout_->addWidget(exposition_, 3, 1);
    angle_layout_->addWidget(new QLabel(tr("s")), 3, 2);
    angle_group_box_->setLayout(angle_layout_);
    meas_layout_->addWidget(angle_group_box_);

    meas_layout_->addWidget(voltage_);
    meas_widget_->setLayout(meas_layout_);

    settings_layout_->addWidget(new QLabel(tr("Braking time:")), 0, 0);
    settings_layout_->addWidget(braking_time_, 0, 1);
    settings_layout_->addWidget(new QLabel(tr("ms")), 0, 2);
    settings_layout_->addWidget(new QLabel(tr("Delay:")), 1, 0);
    settings_layout_->addWidget(delay_, 1, 1);
    settings_layout_->addWidget(new QLabel(tr("s")), 1, 2);
    settings_layout_->addWidget(new QLabel(tr("Directory:")), 2, 0);
    settings_layout_->addWidget(directory_, 2, 1, 1, 2);
    settings_layout_->addWidget(new QLabel(tr("File:")), 3, 0);
    settings_layout_->addWidget(filename_, 3, 1);
    settings_layout_->addWidget(browse_button_, 3, 2);
    settings_layout_->addWidget(new QLabel(tr("Port:")), 4, 0);
    settings_layout_->addWidget(com_port_box_, 4, 1, 1, 2);
    settings_v_layout_->addLayout(settings_layout_);
    settings_v_layout_->addStretch(-1);
    settings_widget_->setLayout(settings_v_layout_);

    line_layout_->addWidget(line_style_, 0, 0, 1, 3);
    line_layout_->addWidget(point_style_, 1, 0, 1, 3);
    line_layout_->addWidget(new QLabel(tr("Size:")), 2, 0);
    line_layout_->addWidget(line_width_, 2, 1);
    line_layout_->addWidget(new QLabel(tr("pt")), 2, 2);
    line_v_layout_->addLayout(line_layout_);
    line_v_layout_->addStretch(-1);
    line_widget_->setLayout(line_v_layout_);

    right_panel_->addTab(meas_widget_, tr("Measurement"));
    right_panel_->addTab(settings_widget_, tr("Settings"));
    right_panel_->addTab(line_widget_, tr("Line"));

    main_splitter_->addWidget(left_widget_);
    main_splitter_->addWidget(right_panel_);
}

void MainWindow::create_connections()
{
    connect(start_button_, SIGNAL(button_pressed(ButtonID)), SLOT(start_button_pressed()));
    connect(pause_button_, SIGNAL(button_pressed(ButtonID)), processor_, SLOT(processButtons(ButtonID)));
    connect(stop_button_, SIGNAL(button_pressed(ButtonID)), SLOT(stop_button_pressed()));
    connect(browse_button_, SIGNAL(clicked(bool)), SLOT(file_browse()));

    connect(processor_, SIGNAL(filenameChanged(QString)), filename_, SLOT(setText(QString)));
    connect(processor_, SIGNAL(directoryChanged(QString)), directory_, SLOT(setText(QString)));
    connect(processor_, SIGNAL(adcValueChanged(QString)), voltage_, SLOT(setText(QString)));

    connect(min_x_edit_, SIGNAL(textChanged(QString)), SLOT(x_axis_change()));
    connect(max_x_edit_, SIGNAL(textChanged(QString)), SLOT(x_axis_change()));
    connect(min_y_edit_, SIGNAL(textChanged(QString)), SLOT(y_axis_change()));
    connect(max_y_edit_, SIGNAL(textChanged(QString)), SLOT(y_axis_change()));

    connect(line_style_, SIGNAL(pressed()), SLOT(line_style_changed()));
    connect(point_style_, SIGNAL(pressed()), SLOT(line_style_changed()));
    connect(line_width_, SIGNAL(valueChanged(int)), processor_, SLOT(lineSizeChanged(int)));
}

void MainWindow::adjust_widgets()
{
    pause_button_->setEnabled(false);
    stop_button_->setEnabled(false);
    point_scan_->setChecked(true);
    line_style_->setChecked(true);

    voltage_->setFont(QFont("Courier New", 36));
    voltage_->setText(tr("0 mV"));
    voltage_->setReadOnly(true);
    voltage_->setAlignment(Qt::AlignHCenter);

    line_width_->setValue(1);

    main_splitter_->setStretchFactor(0, 3);
    main_splitter_->setStretchFactor(1, 1);

    com_port_box_->addItems(processor_->com_port_names());

    graph_plot_->setAutoReplot();
    get_graph_curve()->set_plot(graph_plot_);
    graph_grid_->attach(graph_plot_);
}

void MainWindow::store_settings() {
    settings_->setValue("measurement/start_angle", start_angle_->text());
    settings_->setValue("measurement/stop_angle", stop_angle_->text());
    settings_->setValue("measurement/step", step_->text());
    settings_->setValue("measurement/exposition", exposition_->text());
    settings_->setValue("settings/brake_time", braking_time_->text());
    settings_->setValue("settings/delay", delay_->text());
    settings_->setValue("data/filename", file_name_);
    settings_->setValue("graph/min_x", min_x_edit_->text());
    settings_->setValue("graph/max_x", max_x_edit_->text());
    settings_->setValue("graph/min_y", min_y_edit_->text());
    settings_->setValue("graph/max_y", max_y_edit_->text());
    x_axis_change();
    y_axis_change();
}

void MainWindow::restore_settings()
{
    start_angle_->setText(settings_->value("measurement/start_angle", "0").toString());
    stop_angle_->setText(settings_->value("measurement/stop_angle", "90").toString());
    step_->setText(settings_->value("measurement/step", "1").toString());
    exposition_->setText(settings_->value("measurement/exposition", "2").toString());
    braking_time_->setText(settings_->value("settings/brake_time", "1").toString());
    delay_->setText(settings_->value("settings/delay", "1").toString());
    file_name_ = settings_->value("data/filename").toString();
    processor_->setFilename(file_name_);
    min_x_edit_->setText(settings_->value("graph/min_x", "0").toString());
    max_x_edit_->setText(settings_->value("graph/max_x", "1000").toString());
    min_y_edit_->setText(settings_->value("graph/min_y", "0").toString());
    max_y_edit_->setText(settings_->value("graph/max_y", "1000").toString());
}

void MainWindow::closeEvent(QCloseEvent */*event*/) {
    store_settings();
}

void MainWindow::start_button_pressed() {
    if (com_port_box_->currentText().isEmpty()) {
        show_alarm("Please select serial port");
        return;
    }
    if (file_name_.isEmpty()) {
        show_alarm("Please select filename");
        return;
    }
    processor_->setStartAngle(start_angle_->text());
    processor_->setStopAngle(stop_angle_->text());
    processor_->setStep(step_->text());
    processor_->setExposition(exposition_->text());
    processor_->setBrakeTime(braking_time_->text());
    processor_->setDelay(delay_->text());
    processor_->setSelectedPort(com_port_box_->currentText());

    if (point_scan_->isChecked()) {
        processor_->setMode(Mode::mode_points);
    }
    else if (integral_scan_->isChecked()) {
        processor_->setMode(Mode::mode_integral);
    }
    else if (adjust_scan_->isChecked()) {
        processor_->setMode(Mode::mode_justice);
    }

    processor_->processButtons(ButtonID::Start);
    start_button_->setEnabled(false);
    stop_button_->setEnabled(true);
}

void MainWindow::stop_button_pressed() {
    processor_->processButtons(ButtonID::Stop);
    start_button_->setEnabled(true);
    stop_button_->setEnabled(false);
}

void MainWindow::file_browse() {
    file_name_ = QFileDialog::getSaveFileName(this, tr("Select file"), ".", tr("Data files (*.txt *.dat)"));
    processor_->setFilename(file_name_);
}

void MainWindow::x_axis_change() {
    graph_plot_->setAxisScale(QwtPlot::xBottom, min_x_edit_->text().toDouble(), max_x_edit_->text().toDouble());
    graph_plot_->updateAxes();
    graph_plot_->replot();
}

void MainWindow::y_axis_change() {
    graph_plot_->setAxisScale(QwtPlot::xBottom, min_y_edit_->text().toDouble(), max_y_edit_->text().toDouble());
    graph_plot_->updateAxes();
    graph_plot_->replot();
}

void MainWindow::line_style_changed() {
    if (line_style_->isChecked()) {
        processor_->lineStyleChanged(1);
    }
    else {
        processor_->lineStyleChanged(2);
    }
}

void MainWindow::show_alarm(QString message) {
    QMessageBox::information(nullptr, "Alarm", message);
}
