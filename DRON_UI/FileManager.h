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

    QString directory() const {
        return directory_;
    }

    QString filename() const {
        return filename_;
    }

    void setFilename(QString filename);

signals:
    void directoryChanged();
    void filenameChanged();

public slots:

private:
    QString directory_;
    QString filename_;
};

#endif // FILEMANAGER_H
