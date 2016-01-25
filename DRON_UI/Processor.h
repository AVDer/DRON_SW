#ifndef PROCESSOR_H
#define PROCESSOR_H

#include <memory>
#include <queue>

#include <QObject>
#include <QMessageBox>
#include <QSettings>
#include <QTimer>

#include "MeasureSettings.h"

#include "Libs/qextserialport/qextserialport.h"
#include "../DRON_Embedded/include/Commands.h"

class Processor : public QObject
{
    Q_OBJECT
    Q_PROPERTY(double startAngle READ startAngle WRITE setStartAngle NOTIFY startAngleChanged)
    Q_PROPERTY(double stopAngle READ stopAngle WRITE setStopAngle NOTIFY stopAngleChanged)
    Q_PROPERTY(double step READ step WRITE setStep NOTIFY stepChanged)
    Q_PROPERTY(double exposition READ exposition WRITE setExposition NOTIFY expositionChanged)
    Q_PROPERTY(double brakeTime READ brakeTime WRITE setBrakeTime NOTIFY brakeTimeChanged)
    Q_PROPERTY(double delay READ delay WRITE setDelay NOTIFY delayChanged)
    Q_PROPERTY(QStringList com_port_names READ com_port_names)
    Q_PROPERTY(QString selectedPort WRITE setSelectedPort)
    Q_PROPERTY(int mode WRITE setMode)

public:
    explicit Processor(QObject *parent = 0);
    ~Processor();

    Q_INVOKABLE void processButtons(int button_number);
    Q_INVOKABLE void lineStyleChanged(int style);
    Q_INVOKABLE void lineSizeChanged(int size);

    QStringList com_port_names() const
    {
        return measure_settings_.port_names_list_;
    }

    void setSelectedPort(QString port) {
        measure_settings_.selected_port_ = measure_settings_.ports_map_[port];
    }

    double startAngle() const {
        return measure_settings_.start_angle_;
    }

    void setStartAngle(double start_angle) {
        measure_settings_.start_angle_ = start_angle;
        emit startAngleChanged();
    }

    double stopAngle() const {
        return measure_settings_.stop_angle_;
    }

    void setStopAngle(double stop_angle) {
        measure_settings_.stop_angle_ = stop_angle;
        emit stopAngleChanged();
    }

    double step() const {
        return measure_settings_.step_;
    }

    void setStep(double step) {
       measure_settings_. step_ = step;
    }

    void setExposition(double exposition) {
        measure_settings_.exposition_ = exposition;
    }

    double exposition() {
        return measure_settings_.exposition_;
    }

    double brakeTime() const {
        return measure_settings_.brake_time_;
    }

    void setBrakeTime(double brake_time) {
        measure_settings_.brake_time_ = brake_time;
    }

    double delay() const {
        return measure_settings_.delay_;
    }

    void setDelay(double delay) {
        measure_settings_.delay_ = delay;
    }

    void setMode(int mode) {
        measure_settings_.mode_ = mode;
    }


signals:
    void startAngleChanged();
    void stopAngleChanged();
    void stepChanged();
    void expositionChanged();
    void brakeTimeChanged();
    void delayChanged();

public slots:
    void dataUpdate();

private:
    void sendMessage(uint32_t command, uint32_t data);

    MeasureSettings measure_settings_;
    QextSerialPort com_port_;
    QTimer timer_;
    std::unique_ptr<QSettings> settings_;
    std::queue<Message> message_queue_;
};

#endif // PROCESSOR_H
