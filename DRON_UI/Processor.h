#ifndef PROCESSOR_H
#define PROCESSOR_H

#include <QObject>

class Processor : public QObject
{
    Q_OBJECT
public:
    explicit Processor(QObject *parent = 0);

    Q_INVOKABLE void processButtons(int button_number);

signals:

public slots:
};

#endif // PROCESSOR_H
