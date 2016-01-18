#include "MeasureSettings.h"

#include "../DRON_Embedded/include/Commands.h"
#include "Serial.h"

MeasureSettings::MeasureSettings(QObject *parent) : QObject(parent)
{

}

void MeasureSettings::setExposition(double exposition) {
    exposition_ = exposition;
    Message message;
    message.data.command = cmd_exposition;
    message.data.data = static_cast<uint32_t>(exposition * 1000);
    Serial port("COM5");
    port.write(message.chars, kMessageSize);
}
