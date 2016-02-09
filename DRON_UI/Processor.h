#ifndef PROCESSOR_H
#define PROCESSOR_H

#include <fstream>
#include <queue>

#include <QDebug>
#include <QObject>
#include <QSettings>
#include <QTimer>

#include "FileManager.h"
#include "MeasureSettings.h"
#include "SimpleButton.h"

//#include "Libs/qextserialport/qextserialport.h"
#include "../DRON_Embedded/include/Commands.h"

class Processor : public QObject
{
    Q_OBJECT

public:
    explicit Processor(QObject *parent = 0);
    ~Processor();

    QStringList com_port_names() const {
        return measure_settings_.port_names_list_;
    }

    void setSelectedPort(QString port) {
        measure_settings_.selected_port_ = measure_settings_.ports_map_[port];
    }

    void setStartAngle(QString start_angle) {
        measure_settings_.start_angle_ = start_angle.toDouble();
    }

    void setStopAngle(QString stop_angle) {
        measure_settings_.stop_angle_ = stop_angle.toDouble();
    }

    void setStep(QString step) {
       measure_settings_. step_ = step.toDouble();
    }

    void setExposition(QString exposition) {
        measure_settings_.exposition_ = exposition.toDouble();
    }

    void setBrakeTime(QString brake_time) {
        measure_settings_.brake_time_ = brake_time.toDouble();
    }

    void setDelay(QString delay) {
        measure_settings_.delay_ = delay.toDouble();
    }

    void setMode(int mode) {
        measure_settings_.mode_ = mode;
    }

    QString adcValue() const {
        return adc_value_;
    }

    void setFilename(QString filename);

    QString directory() {
        return file_manager_.directory_;
    }

    QString filename() {
        return file_manager_.filename_;
    }


signals:
    void adcValueChanged(QString);
    void directoryChanged(QString);
    void filenameChanged(QString);

public slots:
    void dataUpdate();
    void processButtons(ButtonID button_number);
    void lineStyleChanged(int style);
    void lineSizeChanged(int size);

private:
    void sendSyncMessage();
    void sendMessage(uint32_t command, uint32_t data, bool queued = true);
    void showAlarm(QString message);
    void prepareFileHeader();
    void prepareFileFooter();

    QTimer timer_;
    FileManager file_manager_;
    MeasureSettings measure_settings_;

    //QextSerialPort com_port_;
    std::ofstream data_file_;
    std::queue<Message> message_queue_;
    QString adc_value_ = 0;
};

#endif // PROCESSOR_H
