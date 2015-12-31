#include "FileManager.h"

#include <QDebug>
#include <QFileDialog>

FileManager::FileManager(QWidget *parent) :
    QWidget(parent),
    filename_("Hello"),
    dialog_parent_(nullptr)
{

}

void FileManager::selectNewFile()
{
    filename_ = QFileDialog::getOpenFileName(dialog_parent_, tr("Open Image"));
    //qDebug() << "Pressed";
}

