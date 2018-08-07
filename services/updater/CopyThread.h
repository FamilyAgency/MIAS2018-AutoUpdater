#ifndef COPYTHREAD_H
#define COPYTHREAD_H

#include <QObject>
#include <QDebug>
#include <QThread>
#include <QFile>
#include <QDir>

class CopyThread : public QObject
{
    Q_OBJECT
private:
    QString sourceDir;
    QString destinationDir;
    bool overWriteDirectory;

public:
    CopyThread();
    void setPath(QString _sourceDir, QString _destinationDir, bool _overWriteDirectory);
    bool copyPath(QString sourceDir, QString destinationDir, bool overWriteDirectory, bool counting);
    void setFilesToCopy(QVector<QString> files);

public slots:
    void doWork();

private:
    int filesCount;
    QVector<QString> filesToCopy;
    bool fileNeedCopy(const QString& fileName);


signals:
    void copyFile();
    void copyProcessComplete(float status);
    void filesCounted(int filesCount);
};

#endif
