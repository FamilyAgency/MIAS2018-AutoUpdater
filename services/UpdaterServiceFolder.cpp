#include "UpdaterServiceFolder.h"

UpdaterServiceFolder::UpdaterServiceFolder(QObject *parent) : UpdaterService(parent)
{

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

bool UpdaterServiceFolder::copyPath(QString sourceDir, QString destinationDir, bool overWriteDirectory)
{
    QDir originDirectory(sourceDir);

    if (!originDirectory.exists())
    {
        return false;
    }

    QDir destinationDirectory(destinationDir);

    if(destinationDirectory.exists() && !overWriteDirectory)
    {
        return false;
    }
    else if(destinationDirectory.exists() && overWriteDirectory)
    {
        destinationDirectory.removeRecursively();
    }

    originDirectory.mkpath(destinationDir);

    foreach (QString directoryName, originDirectory.entryList(QDir::Dirs | \
                                                              QDir::NoDotAndDotDot))
    {
        QString destinationPath = destinationDir + "/" + directoryName;
        originDirectory.mkpath(destinationPath);
        copyPath(sourceDir + "/" + directoryName, destinationPath, overWriteDirectory);
    }

    foreach (QString fileName, originDirectory.entryList(QDir::Files))
    {
        auto fileSource = sourceDir + "/" + fileName;
        auto fileDist = destinationDir + "/" + fileName;
        qDebug()<<"........ fileSource "<<fileSource;
        qDebug()<<"........ fileDist "<<fileDist;
        QFile::copy(fileSource, fileDist);
    }

    /*! Possible race-condition mitigation? */
    QDir finalDestination(destinationDir);
    finalDestination.refresh();

    if(finalDestination.exists())
    {
        return true;
    }

    return false;
}

void UpdaterServiceFolder::startUpdate()
{
    if(loadingBuild)
    {
        return;
    }

    loadingBuild = true;

    loggerComponent->log("Start update", LogType::Verbose, LogRemoteType::Slack, true);

    QDir processDir = config->mainConfig->workingDirectory;
    QString releaseCurrent = _updateConfig.releaseDirectory;
    QString releaseTemp = _updateConfig.tempDirectory;
    QString releaseOld = _updateConfig.oldDirectory;
    QString separator = config->mainConfig->folderSeparator;

    if(!newBuildDir.path().isEmpty())
    {
        QDir destDir = processDir.absolutePath() + separator + releaseTemp;
        bool status = copyPath(newBuildDir.absolutePath(), destDir.absolutePath(), true);
        if(status)
        {
            bool status = false;
            status = processDir.rename(releaseCurrent, releaseOld);
            qDebug()<<"..rename status 1..... "<<status;
            status = processDir.rename(releaseTemp, releaseCurrent);
            qDebug()<<"..rename status 2..... "<<status;
            QDir removeDir = processDir.absolutePath() + separator + releaseOld;
            status =  removeDir.removeRecursively();
            qDebug()<<"..remove status..... "<<status;
        }
    }
    setNeedUpdate(false);
    loggerComponent->log("Update complete, software version " + QString::number(newBuildVersion), LogType::Verbose, LogRemoteType::Slack, true);

    emit updateComplete(_updateConfig.runAppAfterUpdate, newBuildVersion);
    start();
    loadingBuild = false;
}
