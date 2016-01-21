#include "Processor.h"

#include <QDebug>
#include <QMessageBox>

#include "FileManager.h"
#include "GraphCurve.h"
#include "MeasureSettings.h"

#include "../DRON_Embedded/include/Commands.h"

Processor::Processor(QObject *parent) : QObject(parent) {
    measure_settings_.scan_com_ports();
}

void Processor::processButtons(int button_number) {
    static double i = 1;
    if (button_number/* == 1*/) { // Start button
        //QMessageBox::information(nullptr, "Title", QString::number(measure_settings_.mode_));
        get_graph_curve()->add_point(i, i*i);
        i++;
    }
}

