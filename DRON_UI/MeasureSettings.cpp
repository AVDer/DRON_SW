#include "MeasureSettings.h"

void MeasureSettings::scan_com_ports() {
    ports_list_ = QextSerialEnumerator::getPorts();
    for (const QextPortInfo& port : ports_list_) {
        if (port.portName.contains("COM"))
            ports_map_[port.friendName] = port.portName;
    }
    port_names_list_.clear();
    for (const auto& e : ports_map_)
        port_names_list_.append(e.first);
}

