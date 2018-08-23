#ifndef UPDATESERVICEFOLDER_H
#define UPDATESERVICEFOLDER_H

#include <QObject>
#include <QThread>
#include "services/UpdaterService.h"
#include "updater/CopyThread.h"

class UpdaterServiceFolder : public UpdaterService
{
    Q_OBJECT

public:
    explicit UpdaterServiceFolder(QObject *parent = nullptr);
    virtual ~UpdaterServiceFolder();
    virtual void startUpdate() override;

protected:
    virtual void checkUpdate() override;
    virtual bool hasUpdate() override;

    QThread workerThread;

private slots:
    void onCopyFile();
    void onFilesCounted(int filesCount);
    void onCopyProcessComplete(bool status);

private:
    CopyThread *worker;
    int filesCopied = 0;
    int totalFilesCount = 0;


    bool fileExists(QString path);

};

#endif // UPDATESERVICEFOLDER_H
