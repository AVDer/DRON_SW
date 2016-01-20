#ifndef PROCESSOR_H
#define PROCESSOR_H

#include <QObject>
#include <QMessageBox>

#include "MeasureSettings.h"

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

public:
    explicit Processor(QObject *parent = 0);

    Q_INVOKABLE void processButtons(int button_number);

    QStringList com_port_names() const
    {
        return measure_settings_.port_names_list_;
    }

    void setSelectedPort(QString port) {
        QMessageBox::information(nullptr, "Title", measure_settings_.ports_map_[port]);
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


signals:
    void startAngleChanged();
    void stopAngleChanged();
    void stepChanged();
    void expositionChanged();
    void brakeTimeChanged();
    void delayChanged();

public slots:

private:
    MeasureSettings measure_settings_;
};

#endif // PROCESSOR_H
