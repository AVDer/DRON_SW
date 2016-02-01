#ifndef SIMPLEBUTTON_H
#define SIMPLEBUTTON_H

#include <QPushButton>
#include <QString>
#include <QWidget>

enum class ButtonID {
    Start,
    Pause,
    Stop
};

class SimpleButton : public QPushButton
{
    Q_OBJECT
public:
    SimpleButton(QString text, ButtonID id, QWidget *parent = 0);

signals:
    void button_pressed(ButtonID id);

public slots:

private:
    void mousePressEvent(QMouseEvent *eventPress);
    ButtonID id_;
};

#endif // SIMPLEBUTTON_H
