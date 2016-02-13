#include "MeasureSettings.h"

void MeasureSettings::scan_com_ports() {
    port_names_list_.clear();
    ports_list_ = QextSerialEnumerator::getPorts();
    for (size_t i = 0; i < ports_list_.size(); ++i) {
        if (ports_list_.at(i).portName.contains("COM")) {
            ports_map_[ports_list_.at(i).friendName] = ports_list_.at(i).portName;
            port_names_list_.append(ports_list_.at(i).friendName);
        }
    }
}

