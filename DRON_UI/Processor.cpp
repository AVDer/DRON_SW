#include "Processor.h"

#include <chrono>
#include <ctime>

#include <QDebug>
#include <QMessageBox>
#include <QThread>

#include "FileManager.h"
#include "GraphCurve.h"
#include "MeasureSettings.h"

Processor::Processor(QObject *parent) :
    QObject(parent),
    settings_(new QSettings("StarCon", "DRON Control"))
{
    measure_settings_.scan_com_ports();
    connect(&timer_, SIGNAL(timeout()), SLOT(dataUpdate()));
    measure_settings_.start_angle_ =
            settings_->value("measurement/start_angle", 0).toDouble();
    measure_settings_.stop_angle_ =
            settings_->value("measurement/stop_angle", 90).toDouble();
    measure_settings_.step_ =
            settings_->value("measurement/step", 1).toDouble();
    measure_settings_.exposition_ =
            settings_->value("measurement/exposition", 2).toDouble();
    measure_settings_.brake_time_ =
            settings_->value("measurement/brake_time", 1).toDouble();
    measure_settings_.delay_ =
            settings_->value("measurement/delay", 1).toDouble();
    setFilename(settings_->value("data/filename").toString());
}

Processor::~Processor() {
    com_port_.close();
    data_file_.close();
    settings_->setValue("measurement/start_angle", measure_settings_.start_angle_);
    settings_->setValue("measurement/stop_angle", measure_settings_.stop_angle_);
    settings_->setValue("measurement/step", measure_settings_.step_);
    settings_->setValue("measurement/exposition", measure_settings_.exposition_);
    settings_->setValue("settings/brake_time", measure_settings_.brake_time_);
    settings_->setValue("settings/delay", measure_settings_.delay_);
    settings_->setValue("data/filename", file_manager_.full_filename_);
}

void Processor::processButtons(int button_number) {
    sendSyncMessage();
    switch (button_number) {
    case 1: // Start button
        if (measure_settings_.selected_port_.isEmpty()) {
            showAlarm("Please select serial port");
            return;
        }
        if (file_manager_.full_filename_.isEmpty()) {
            showAlarm("Please select filename");
            return;
        }
        com_port_.setBaudRate(BAUD115200);
        com_port_.setDataBits(DATA_8);
        com_port_.setFlowControl(FLOW_OFF);
        com_port_.setParity(PAR_NONE);
        com_port_.setPortName(measure_settings_.selected_port_);
        com_port_.open(QIODevice::ReadWrite);

        if (measure_settings_.mode_ == Mode::mode_points || measure_settings_.mode_ == Mode::mode_integral) {
            data_file_.open(file_manager_.full_filename_.toStdString());
            if (!data_file_.is_open()) {
                showAlarm("File open error");
                com_port_.close();
                return;
            }
            prepareFileHeader();
        }

        sendMessage(cmd_counts,
                    fabs(measure_settings_.start_angle_ - measure_settings_.stop_angle_) * 200. + 1);
        sendMessage(cmd_step, measure_settings_.step_ * 2);
        sendMessage(cmd_direction,
                    (measure_settings_.start_angle_ < measure_settings_.stop_angle_) ?
                        Direction::dir_forward : Direction::dir_backward);
        sendMessage(cmd_exposition, measure_settings_.exposition_ * 1000.);
        sendMessage(cmd_break_time, measure_settings_.brake_time_);
        sendMessage(cmd_delay, measure_settings_.delay_ * 1000.);
        sendMessage(cmd_start, measure_settings_.mode_);

        timer_.start(500);
        get_graph_curve()->clear();
        break;
    case 3: // Stop button
        sendMessage(cmd_stop, 0);
        prepareFileFooter();
        data_file_.close();
        break;
    default:
        break;
    }
}

void Processor::dataUpdate() {
    int read_index = 0;
    char c;
    Message in_message;
    if (!message_queue_.empty()) {
        if (com_port_.isOpen()) {
            com_port_.write(message_queue_.front().chars, kMessageSize);
            message_queue_.pop();
        }
    }
    while (com_port_.bytesAvailable() > 0) {
        com_port_.getChar(&c);
        in_message.chars[read_index] = c;
        if (++read_index >= kMessageSize) {
            read_index = 0;
            qDebug() << in_message.data.command << '\t' << in_message.data.data;
            if (in_message.data.command == Commands::cmd_alarm) {
                showAlarm("Speed is too high");
            }
            else if (in_message.data.command == Commands::cmd_measurement_stopped) {
                showAlarm("Measurement stopped");
                prepareFileFooter();
                data_file_.close();
            }
            else if (measure_settings_.mode_ == Mode::mode_points || measure_settings_.mode_ == Mode::mode_integral){
                get_graph_curve()->add_point(measure_settings_.start_angle_ + in_message.data.command / 200.,
                                             in_message.data.data);
                data_file_ << measure_settings_.start_angle_ + in_message.data.command / 200. << '\t' << in_message.data.data << std::endl;
            }
            else if (measure_settings_.mode_ == Mode::mode_justice) {
                adc_value_ = QString::number(static_cast<double>(in_message.data.data) * 3300 / 4095) + " mV";
                emit adcValueChanged();
            }
        }
    }
}

void Processor::sendMessage(uint32_t command, uint32_t data, bool queued) {
    Message out_message;
    out_message.data.command = command;
    out_message.data.data = data;
    if (queued) {
        message_queue_.push(out_message);
    }
    else {
        com_port_.write(out_message.chars, kMessageSize);
    }
}

void Processor::sendSyncMessage() {
    sendMessage(Commands::cmd_sync_32, Commands::cmd_sync_32);
    sendMessage(Commands::cmd_sync_32, Commands::cmd_sync_32);
}

void Processor::showAlarm(QString message) {
    QMessageBox::information(nullptr, "Alarm", message);
}

void Processor::prepareFileHeader() {
    std::time_t dron_time_;
    dron_time_ = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
    data_file_ << "Measurement start: " << std::ctime(&dron_time_) << std::endl;
    if (measure_settings_.mode_ == Mode::mode_points) {
        data_file_ << "Point scan" << std::endl;
    }
    else if (measure_settings_.mode_ == Mode::mode_integral) {
        data_file_ << "Integral scan" << std::endl;
    }
}

void Processor::prepareFileFooter()
{
    std::time_t dron_time_;
    dron_time_ = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
    data_file_ << "Measurement stop: " << std::ctime(&dron_time_) << std::endl;
}

void Processor::lineStyleChanged(int style) {
    get_graph_curve()->set_style(style);
}

void Processor::lineSizeChanged(int size) {
    get_graph_curve()->set_size(size);
}

void Processor::setFilename(QString filename) {
    if (file_manager_.filename_ != filename) {
        file_manager_.full_filename_ = filename;
        if (file_manager_.full_filename_.startsWith("file")) {
            file_manager_.full_filename_.remove(0, 8);
        }
        int separator_pos = file_manager_.full_filename_.lastIndexOf("/");
        file_manager_.directory_ = file_manager_.full_filename_.left(separator_pos);
        file_manager_.filename_ = file_manager_.full_filename_.right(file_manager_.full_filename_.size() - separator_pos - 1);

        emit filenameChanged();
        emit directoryChanged();
    }
}
