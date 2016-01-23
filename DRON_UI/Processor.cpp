#include "Processor.h"

#include <QDebug>
#include <QMessageBox>

#include "FileManager.h"
#include "GraphCurve.h"
#include "MeasureSettings.h"

#include "../DRON_Embedded/include/Commands.h"

Processor::Processor(QObject *parent) : QObject(parent) {
    measure_settings_.scan_com_ports();
    connect(&timer_, SIGNAL(timeout()), SLOT(dataUpdate()));
}

Processor::~Processor() {
    com_port_.close();
}

void Processor::processButtons(int button_number) {
    Message out_message;
    switch (button_number) {
    case 1: // Start button
        com_port_.setBaudRate(BAUD115200);
        com_port_.setDataBits(DATA_8);
        com_port_.setFlowControl(FLOW_OFF);
        com_port_.setParity(PAR_NONE);
        com_port_.setPortName(measure_settings_.selected_port_);
        com_port_.open(QIODevice::ReadWrite);

        out_message.data.command = cmd_start;
        out_message.data.data = measure_settings_.mode_;
        com_port_.write(out_message.chars, kMessageSize);

        timer_.start(500);
        break;
    case 3: // Stop button
        out_message.data.command = cmd_stop;
        out_message.data.data = 0;
        com_port_.write(out_message.chars, kMessageSize);
        com_port_.close();
    }
}

void Processor::dataUpdate() {
    int read_index = 0;
    char c;
    Message in_message;
    while (com_port_.bytesAvailable() > 0) {
        com_port_.getChar(&c);
        in_message.chars[read_index] = c;
        if (++read_index >= kMessageSize) {
            read_index = 0;
            get_graph_curve()->add_point(in_message.data.command, in_message.data.data);
        }
    }
}

void Processor::lineStyleChanged(int style) {
    get_graph_curve()->set_style(style);
}

void Processor::lineSizeChanged(int size) {
    get_graph_curve()->set_size(size);
}
