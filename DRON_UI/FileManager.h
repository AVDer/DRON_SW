#ifndef FILEMANAGER_H
#define FILEMANAGER_H

#include <QDebug>
#include <QObject>
#include <QString>

class FileManager : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString directory READ directory NOTIFY directoryChanged)
    Q_PROPERTY(QString filename READ filename WRITE setFilename NOTIFY filenameChanged)

public:
    explicit FileManager(QObject *parent = 0);

    static QString directory() {
        return directory_;
    }

    static QString filename() {
        return filename_;
    }

    static QString full_filename() {
        return full_filename_;
    }

    void setFilename(QString filename);

signals:
    void directoryChanged();
    void filenameChanged();

public slots:

private:
    static QString full_filename_;
    static QString directory_;
    static QString filename_;
};

#endif // FILEMANAGER_H
