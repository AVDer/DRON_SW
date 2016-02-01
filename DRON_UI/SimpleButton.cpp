#include "SimpleButton.h"

SimpleButton::SimpleButton(QString text, ButtonID id, QWidget *parent) :
    QPushButton(text, parent),
    id_(id) { }

void SimpleButton::mousePressEvent(QMouseEvent *eventPress) {
    emit button_pressed(id_);
}

