#include "Processor.h"

#include <QDebug>
#include <QMessageBox>

#include "FileManager.h"

Processor::Processor(QObject *parent) : QObject(parent)
{

}

void Processor::processButtons(int button_number)
{
    if (button_number == 1) { // Start button
        //QMessageBox::information(nullptr, "Title", FileManager::directory());
    }
}

