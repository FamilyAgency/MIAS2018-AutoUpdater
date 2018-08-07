#include "UpdaterServiceFolder.h"


UpdaterServiceFolder::UpdaterServiceFolder(QObject *parent) : UpdaterService(parent)
{
    worker = new CopyThread();
    worker->moveToThread(&workerThread);
    connect(&workerThread, SIGNAL(started()), worker, SLOT(doWork()));
    connect(worker, &CopyThread::copyFile, this, &UpdaterServiceFolder::onCopyFile);
    connect(worker, &CopyThread::filesCounted, this, &UpdaterServiceFolder::onFilesCounted);
    connect(worker, &CopyThread::copyProcessComplete, this, &UpdaterServiceFolder::onCopyProcessComplete);
}

UpdaterServiceFolder::~UpdaterServiceFolder()
{
    workerThread.quit();
    workerThread.wait();
    disconnect(&workerThread, SIGNAL(started()), worker, SLOT(doWork()));

    if(worker)
    {
        delete worker;
        disconnect(worker, &CopyThread::filesCounted, this, &UpdaterServiceFolder::onFilesCounted);
        disconnect(worker, &CopyThread::copyFile, this, &UpdaterServiceFolder::onCopyFile);
        disconnect(worker, &CopyThread::copyProcessComplete, this, &UpdaterServiceFolder::onCopyProcessComplete);
    }
}

void UpdaterServiceFolder::checkUpdate()
{
    timer->stop();
    newBuildDir.setPath("");
    bool status = hasUpdate();
    emit updateCheckingComplete(status);
}

bool UpdaterServiceFolder::hasUpdate()
{
    int lastVersionNum = newBuildVersion = config->mainConfig->version;
    bool foundNewVersion = false;

    QDir dir(_updateConfig.checkDirectory);
    QFileInfoList list = dir.entryInfoList(QDir::Dirs | QDir::NoDotAndDotDot);

    foreach(QFileInfo finfo, list)
    {
        QString pattern = _updateConfig.patternCheck;
        QString fileName = finfo.fileName();
        int index = fileName.indexOf(pattern);
        if(index != -1)
        {
            QString versionNewString = fileName.right(fileName.length() - index - pattern.length());
            newBuildVersion  = versionNewString.toInt();
            if(newBuildVersion > lastVersionNum)
            {
                lastVersionNum = newBuildVersion;
                newBuildDir = finfo.absoluteFilePath();
                foundNewVersion = true;
            }
        }
    }

    if(foundNewVersion)
    {
        newBuildVersion = lastVersionNum;
        loggerComponent->log("Software version " + QString::number(newBuildVersion)+ " detected", LogType::Verbose, LogRemoteType::Slack, true);
    }
    else
    {
        // loggerComponent->log("No updates detected", LogType::Verbose, LogRemoteType::Slack, true);
    }

    setNeedUpdate(foundNewVersion);
    return foundNewVersion;
}

void UpdaterServiceFolder::startUpdate()
{
    if(loadingBuild)
    {
        return;
    }

    loadingBuild = true;
    filesCopied = 0;
    totalFilesCount = 0;

    loggerComponent->log("Start update", LogType::Verbose, LogRemoteType::Slack, true);

    QDir processDir = config->mainConfig->workingDirectory;
    QString separator = config->mainConfig->folderSeparator;
    QString releaseTemp = _updateConfig.tempDirectory;

    emit loadingStarted();

    if(!newBuildDir.path().isEmpty())
    {
        QDir destDir = processDir.absolutePath() + separator + releaseTemp;
        worker->setFilesToCopy(config->updateConfig->filesToCopy);
        worker->setPath(newBuildDir.absolutePath(), destDir.absolutePath(), true);

        if(workerThread.isRunning())
        {
           // worker->doWork();
        }

        workerThread.start();
    }
    else
    {
        //error
    }
}

void UpdaterServiceFolder::onCopyFile()
{
    filesCopied++;
    qDebug()<<"........ files Count "<<filesCopied<<"/"<<totalFilesCount;
    setUpdatePercent(filesCopied /float(totalFilesCount));
}

void UpdaterServiceFolder::onFilesCounted(int filesCount)
{
    totalFilesCount = filesCount;
    setUpdatePercent(0);
}

void UpdaterServiceFolder::onCopyProcessComplete(bool _status)
{
    workerThread.terminate();
    // bool status = copyPath(newBuildDir.absolutePath(), destDir.absolutePath(), true);
    if(_status)
    {
        QString releaseCurrent = _updateConfig.releaseDirectory;
        QString releaseTemp = _updateConfig.tempDirectory;
        QString separator = config->mainConfig->folderSeparator;
        QString releaseOld = _updateConfig.oldDirectory;
        QDir processDir = config->mainConfig->workingDirectory;

        bool status = false;
        status = processDir.rename(releaseCurrent, releaseOld);
        qDebug()<<"..rename status 1..... "<<status;
        status = processDir.rename(releaseTemp, releaseCurrent);
        qDebug()<<"..rename status 2..... "<<status;
        QDir removeDir = processDir.absolutePath() + separator + releaseOld;
        status =  removeDir.removeRecursively();
        qDebug()<<"..remove status..... "<<status;
    }

    setNeedUpdate(false);
    loggerComponent->log("Update complete, software version " + QString::number(newBuildVersion), LogType::Verbose, LogRemoteType::Slack, true);

    emit updateComplete(_updateConfig.runAppAfterUpdate, newBuildVersion);
    start();
    loadingBuild = false;
}
