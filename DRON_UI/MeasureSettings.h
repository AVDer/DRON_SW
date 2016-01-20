#ifndef MEASURESETTINGS_H
#define MEASURESETTINGS_H

#include <QObject>
#include <QMessageBox>

#include "libs/qextserialport/qextserialenumerator.h"

class MeasureSettings : public QObject
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
    explicit MeasureSettings(QObject *parent = 0);

    void scan_com_ports();

    QStringList com_port_names() const
    {
        return port_names_list_;
    }

    void setSelectedPort(QString port) {
        QMessageBox::information(nullptr, "Title", port);
    }

    double startAngle() const {
        return start_angle_;
    }

    void setStartAngle(double start_angle) {
        start_angle_ = start_angle;
        emit startAngleChanged();
    }

    double stopAngle() const {
        return stop_angle_;
    }

    void setStopAngle(double stop_angle) {
        stop_angle_ = stop_angle;
        emit stopAngleChanged();
    }

    double step() const {
        return step_;
    }

    void setStep(double step) {
        step_ = step;
    }

    void setExposition(double exposition) {
        exposition_ = exposition;
    }

    static double exposition() {
        return exposition_;
    }

    double brakeTime() const {
        return brake_time_;
    }

    void setBrakeTime(double brake_time) {
        brake_time_ = brake_time;
    }

    double delay() const {
        return delay_;
    }

    void setDelay(double delay) {
        delay_ = delay;
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
    double start_angle_;
    double stop_angle_;
    double step_;
    static double exposition_;
    double brake_time_;
    double delay_;
    static QString selected_port_;

    QList<QextPortInfo> ports_list_;
    QStringList port_names_list_;
    std::map<QString, QString> ports_map_;
};

#endif // MEASURESETTINGS_H
