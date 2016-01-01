#include "FileManager.h"

#include <QDebug>
#include <QFileDialog>

FileManager::FileManager(QObject *parent) :
    QObject(parent),
    directory_(""),
    filename_("")
{

}

void FileManager::setFilename(QString filename) {
    if (filename_ != filename) {
        int separator_pos = filename.lastIndexOf("/");
        directory_ = filename.left(separator_pos);
        filename_ = filename.right(filename.size() - separator_pos - 1);

        emit filenameChanged();
        emit directoryChanged();
    }
}
