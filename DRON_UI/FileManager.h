#ifndef FILEMANAGER_H
#define FILEMANAGER_H

#include <QDebug>
#include <QWidget>
#include <QString>

class FileManager : public QWidget
{
    Q_OBJECT
    Q_PROPERTY(QString filename READ filename WRITE setFilename NOTIFY filenameChanged)
public:
    explicit FileManager(QWidget *parent = 0);
    QString filename() const {
        return filename_;
    }
    void setFilename(QString filename) {
        if (filename_ != filename) {
            qDebug() << "!!!";
            filename_ == filename;
            emit filenameChanged();
        }

    }

    void setDiaParent(QWidget *dialog_parent) {
        dialog_parent_ = dialog_parent;
    }


signals:
    void filenameChanged();

public slots:
    void selectNewFile();

private:
    QString filename_;
    QWidget *dialog_parent_;
};

#endif // FILEMANAGER_H
