#include "UartManager.h"

UartManager::UartManager() :
    current_port("None")
{
    com_port_.setBaudRate(BAUD115200);
    com_port_.setDataBits(DATA_8);
    com_port_.setFlowControl(FLOW_OFF);
    com_port_.setParity(PAR_NONE);
}

UartManager::~UartManager()
{
    if (com_port_.isOpen()) {
        com_port_.close();
    }
}

void UartManager::set_port(QString port_name)
{
    if (com_port_.isOpen()) {
        if (current_port == port_name) {
            return;
        }
        com_port_.close();
    }
    com_port_.setPortName(port_name);
    com_port_.open(QIODevice::ReadWrite);
    current_port = port_name;
}
