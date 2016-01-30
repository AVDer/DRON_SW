#ifndef PROCESSOR_H
#define PROCESSOR_H

#include <fstream>
#include <memory>
#include <queue>

#include <QDebug>
#include <QtMultimedia/QMediaPlayer>
#include <QObject>
#include <QSettings>
#include <QSound>
#include <QTimer>

#include "FileManager.h"
#include "MeasureSettings.h"

#include "Libs/qextserialport/qextserialport.h"
#include "../DRON_Embedded/include/Commands.h"

class Processor : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString startAngle READ startAngle WRITE setStartAngle NOTIFY startAngleChanged)
    Q_PROPERTY(QString stopAngle READ stopAngle WRITE setStopAngle NOTIFY stopAngleChanged)
    Q_PROPERTY(double step READ step WRITE setStep NOTIFY stepChanged)
    Q_PROPERTY(double exposition READ exposition WRITE setExposition NOTIFY expositionChanged)
    Q_PROPERTY(double brakeTime READ brakeTime WRITE setBrakeTime NOTIFY brakeTimeChanged)
    Q_PROPERTY(double delay READ delay WRITE setDelay NOTIFY delayChanged)
    Q_PROPERTY(QStringList com_port_names READ com_port_names)
    Q_PROPERTY(QString selectedPort WRITE setSelectedPort)
    Q_PROPERTY(int mode WRITE setMode)
    Q_PROPERTY(QString adcValue READ adcValue NOTIFY adcValueChanged)

    Q_PROPERTY(QString directory READ directory NOTIFY directoryChanged)
    Q_PROPERTY(QString filename READ filename WRITE setFilename NOTIFY filenameChanged)

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

    QString startAngle() const {
        return QString::number(measure_settings_.start_angle_);
    }

    void setStartAngle(QString start_angle) {
        measure_settings_.start_angle_ = start_angle.toDouble();
        emit startAngleChanged();
    }

    QString stopAngle() const {
        return QString::number(measure_settings_.stop_angle_);
    }

    void setStopAngle(QString stop_angle) {
        measure_settings_.stop_angle_ = stop_angle.toDouble();
        //qDebug() << stop_angle;
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
    void startAngleChanged();
    void stopAngleChanged();
    void stepChanged();
    void expositionChanged();
    void brakeTimeChanged();
    void delayChanged();
    void adcValueChanged();
    void directoryChanged();
    void filenameChanged();

public slots:
    void dataUpdate();

private:
    void sendSyncMessage();
    void sendMessage(uint32_t command, uint32_t data, bool queued = true);
    void showAlarm(QString message);
    void prepareFileHeader();
    void prepareFileFooter();

    QMediaPlayer media_player_;
    QTimer timer_;
    FileManager file_manager_;
    MeasureSettings measure_settings_;

    QextSerialPort com_port_;
    std::ofstream data_file_;
    std::unique_ptr<QSettings> settings_;
    std::queue<Message> message_queue_;
    QString adc_value_ = 0;
};

#endif // PROCESSOR_H
