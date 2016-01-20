#ifndef MEASURESETTINGS_H
#define MEASURESETTINGS_H

#include <map>

#include <QList>
#include <QString>
#include <QStringList>

#include "libs/qextserialport/qextserialenumerator.h"

struct MeasureSettings
{
    void scan_com_ports();

    double start_angle_;
    double stop_angle_;
    double step_;
    double exposition_;
    double brake_time_;
    double delay_;
    QString selected_port_;

    QList<QextPortInfo> ports_list_;
    QStringList port_names_list_;
    std::map<QString, QString> ports_map_;
};

#endif // MEASURESETTINGS_H
