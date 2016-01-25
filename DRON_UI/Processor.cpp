#include "Processor.h"

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
    //FileManager::setFilename(settings_->value("data/filename").toString);
}

Processor::~Processor() {
    com_port_.close();
    settings_->setValue("measurement/start_angle", measure_settings_.start_angle_);
    settings_->setValue("measurement/stop_angle", measure_settings_.stop_angle_);
    settings_->setValue("measurement/step", measure_settings_.step_);
    settings_->setValue("measurement/exposition", measure_settings_.exposition_);
    settings_->setValue("settings/brake_time", measure_settings_.brake_time_);
    settings_->setValue("settings/delay", measure_settings_.delay_);
    settings_->setValue("data/filename", FileManager::full_filename());
}

void Processor::processButtons(int button_number) {

    switch (button_number) {
    case 1: // Start button
        com_port_.setBaudRate(BAUD115200);
        com_port_.setDataBits(DATA_8);
        com_port_.setFlowControl(FLOW_OFF);
        com_port_.setParity(PAR_NONE);
        com_port_.setPortName(measure_settings_.selected_port_);
        com_port_.open(QIODevice::ReadWrite);

        sendMessage(cmd_direction,
                    (measure_settings_.start_angle_ < measure_settings_.stop_angle_) ?
                        Direction::dir_forward : Direction::dir_backward);

        sendMessage(cmd_counts,
                    fabs(measure_settings_.start_angle_ - measure_settings_.stop_angle_) /
                    measure_settings_.step_ * 100.);

        sendMessage(cmd_exposition, measure_settings_.exposition_ * 1000.);
        sendMessage(cmd_step, measure_settings_.step_ * 2);
        sendMessage(cmd_start, measure_settings_.mode_);

        timer_.start(500);
        get_graph_curve()->clear();
        break;
    case 3: // Stop button
        sendMessage(cmd_stop, 0);
        com_port_.close();
    }
}

void Processor::dataUpdate() {
    int read_index = 0;
    char c;
    Message in_message;
    if (!message_queue_.empty()) {
        if (com_port_.isOpen()) {
            qDebug() << message_queue_.front().data.command << '\t' << message_queue_.front().data.data;
            com_port_.write(message_queue_.front().chars, kMessageSize);
            message_queue_.pop();
        }
    }
    while (com_port_.bytesAvailable() > 0) {
        com_port_.getChar(&c);
        in_message.chars[read_index] = c;
        if (++read_index >= kMessageSize) {
            read_index = 0;
            if (in_message.data.command == Commands::cmd_alarm) {
                QMessageBox::information(nullptr, "Alarm", "Too fast");
            }
            else {
                get_graph_curve()->add_point(measure_settings_.start_angle_ +
                                             measure_settings_.step_ * in_message.data.command / 100.,
                                             in_message.data.data);
            }
        }
    }
}

void Processor::sendMessage(uint32_t command, uint32_t data)
{
    Message out_message;
    out_message.data.command = command;
    out_message.data.data = data;
    message_queue_.push(out_message);
}

void Processor::lineStyleChanged(int style) {
    get_graph_curve()->set_style(style);
}

void Processor::lineSizeChanged(int size) {
    get_graph_curve()->set_size(size);
}
