#include "Processor.h"

#include <QDebug>
#include <QMessageBox>
#include <QThread>

#include "FileManager.h"
#include "GraphCurve.h"
#include "MeasureSettings.h"

Processor::Processor(QObject *parent) :
        QObject(parent)
{
    measure_settings_.scan_com_ports();

    connect(&timer_, SIGNAL(timeout()), SLOT(dataUpdate()));
}

Processor::~Processor() {
    data_file_.close();
}

void Processor::processButtons(ButtonID button_number) {
    sendSyncMessage();
    switch (button_number) {
    case Start:
        if (measure_settings_.mode_ == mode_points || measure_settings_.mode_ == mode_integral) {
            data_file_.open(file_manager_.full_filename_.toStdString().c_str());
            if (!data_file_.is_open()) {
                showAlarm("File open error");
                return;
            }
            prepareFileHeader();
            emit voltmeterVisible(false);
        }
        else {
            emit voltmeterVisible(true);
        }
        uart_.set_port(measure_settings_.selected_port_);

        sendMessage(cmd_sw_version, 0);
        sendMessage(cmd_counts,
                    fabs(measure_settings_.start_angle_ - measure_settings_.stop_angle_) * 100. + 2);
        sendMessage(cmd_step, measure_settings_.step_);
        sendMessage(cmd_direction,
                    (measure_settings_.start_angle_ < measure_settings_.stop_angle_) ?
                    dir_forward : dir_backward);
        sendMessage(cmd_exposition, measure_settings_.exposition_ * 1000.);
        sendMessage(cmd_break_time, measure_settings_.brake_time_);
        sendMessage(cmd_delay, measure_settings_.delay_);
        sendMessage(cmd_start, measure_settings_.mode_);

        timer_.start(500);
        get_graph_curve()->clear();
        ticks_received_ = 0;
        last_tick_ = 0;
        break;
    case Stop: // Stop button
        sendMessage(cmd_stop, 0);
        prepareFileFooter();
        data_file_.close();
        break;
    case Open_Damper:
        sendMessage(cmd_damper, 1);
        break;
    case Close_Damper:
        sendMessage(cmd_damper, 2);
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
        if (uart_.is_open()) {
            uart_.write(message_queue_.front().chars, kMessageSize);
            message_queue_.pop();
        }
    }
    while (uart_.is_bytes_available() > 0) {
        c = uart_.get_char();
        in_message.chars[read_index] = c;
        if (++read_index >= kMessageSize) {
            read_index = 0;
            //qDebug() << in_message.data.command << '\t' << in_message.data.data;
            if (in_message.data.command == cmd_alarm) {
                showAlarm("Speed is too high");
            }
            else if (in_message.data.command == cmd_sw_version) {
                emit embeddedSW(QString::number(in_message.raw_data[7]) + '.' +
                        QString::number(in_message.raw_data[6]) + '.' +
                        QString::number(in_message.raw_data[5]));
            }
            else if (in_message.data.command == cmd_measurement_stopped) {
                prepareFileFooter();
                data_file_.close();
                showAlarm("Measurement stopped");
            }
            else if (measure_settings_.mode_ == mode_points || measure_settings_.mode_ == mode_integral){
                double received_angle = measure_settings_.start_angle_ + in_message.data.command / 100.;
                if (received_angle >= measure_settings_.start_angle_ &&
                    received_angle <= measure_settings_.stop_angle_) {
                    get_graph_curve()->add_point(received_angle, in_message.data.data);
                    data_file_ << received_angle << '\t' << in_message.data.data << std::endl;
                    ++ticks_received_;
                    last_tick_ = in_message.data.command;
                    emit angleReceived(QString::number(received_angle));
                }
            }
            else if (measure_settings_.mode_ == mode_justice) {
                adc_value_ = QString::number(static_cast<double>(in_message.data.data) * 3300 / 4095) + " mV";
                emit adcValueChanged(adc_value_);
            }
        }
    }
    get_graph_curve()->redraw();
}

void Processor::sendMessage(uint32_t command, uint32_t data, bool queued) {
    Message out_message;
    out_message.data.command = command;
    out_message.data.data = data;
    if (queued) {
        message_queue_.push(out_message);
    }
    else {
        uart_.write(out_message.chars, kMessageSize);
    }
}

void Processor::sendSyncMessage() {
    sendMessage(cmd_sync_32, cmd_sync_32);
    sendMessage(cmd_sync_32, cmd_sync_32);
}

void Processor::showAlarm(QString message) {
    QMessageBox::information(NULL, "Alarm", message);
}

void Processor::prepareFileHeader() {
    data_file_ << "Measurement start: " << QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss").toStdString() << std::endl;
    if (measure_settings_.mode_ == mode_points) {
        data_file_ << "Point scan" << std::endl;
    }
    else if (measure_settings_.mode_ == mode_integral) {
        data_file_ << "Integral scan" << std::endl;
    }
}

void Processor::prepareFileFooter()
{
    data_file_ << "Measurement stop: " << QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss").toStdString() << std::endl;
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

        emit filenameChanged(file_manager_.filename_);
        emit directoryChanged(file_manager_.directory_);
    }
}
