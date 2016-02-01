#include "LimitsInput.h"

#include <QDoubleValidator>

LimitsInput::LimitsInput(QWidget *parent) :
    QLineEdit(parent) {
    setValidator(new QDoubleValidator(this));
}
