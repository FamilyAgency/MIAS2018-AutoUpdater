#include "UpdaterService.h"
#include <QDirIterator>

UpdaterService::UpdaterService(QObject *parent) : BaseService(parent)
{
    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(onUpdate()));

    loggerService.reset(new LoggerService());
}

UpdaterService::~UpdaterService()
{
    if(timer)
    {
        disconnect(timer, SIGNAL(timeout()), this, SLOT(onUpdate()));
        delete timer;
    }
}

void UpdaterService::setQmlContext(QQmlContext* qmlContext)
{
    BaseService::setQmlContext(qmlContext);
    qmlContext->setContextProperty("updaterService", this);
}

void UpdaterService::setConfig(ConfigPtr value)
{
    BaseService::setConfig(value);
    setUpdateConfig(*value->updateConfig);
    loggerService->setConfig(value);
}

void UpdaterService::setUpdateConfig(const UpdateConfig& value)
{
    _updateConfig = value;
    emit updateConfigChanged();
}

void UpdaterService::resetTimer()
{
     timer->stop();
     if(_updateConfig.autocheck)
     {
         startTime = QDateTime::currentMSecsSinceEpoch();
         timer->start(taskTimerMills);
     }
}

void UpdaterService::start()
{
    if(_updateConfig.autocheck)
    {       
        startTime = QDateTime::currentMSecsSinceEpoch();
        timer->start(taskTimerMills);
    }
}

void UpdaterService::onUpdate()
{
    int time = QDateTime::currentMSecsSinceEpoch() - startTime;
    int diff = _updateConfig.millsCheck - time;
    if(diff > 0)
    {
        setTimeToUpdate(diff / 1000 + 1);
    }
    else
    {       
        bool updateCome = checkUpdate();
        if(updateCome && _updateConfig.autoupdate)
        {
            emit pendingUpdate();
        }
        else
        {
            resetTimer();
        }
    }
}

UpdateConfig UpdaterService::updateConfig() const
{
    return _updateConfig;
}

void UpdaterService::stop()
{

}

void UpdaterService::forceCheckUpdate()
{
    timer->stop();
    checkUpdate();
    resetTimer();
}

bool UpdaterService::checkUpdate()
{
    newBuildDir.setPath("");
    return hasUpdate(newBuildDir);
}

bool UpdaterService::hasUpdate(QDir& newBuildDir)
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
        loggerService->log("Software version " + QString::number(newBuildVersion)+ " detected", LogType::Verbose, LogRemoteType::Slack, true);
    }
    else
    {
        loggerService->log("No updates detected", LogType::Verbose, LogRemoteType::Slack, true);
    }

    setNeedUpdate(foundNewVersion);
    return foundNewVersion;
}

bool UpdaterService::needUpdate() const
{
    return _needUpdate;
}

void UpdaterService::setNeedUpdate(bool value)
{
    _needUpdate = value;
    emit needUpdateChanged();
}

bool UpdaterService::copyPath(QString sourceDir, QString destinationDir, bool overWriteDirectory)
{
    QDir originDirectory(sourceDir);

    if (! originDirectory.exists())
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

void UpdaterService::onUpdateLoaded()
{
    emit pendingUpdate();
}

void UpdaterService::forceStartUpdate()
{
    timer->stop();
    emit pendingUpdate();
}

void UpdaterService::startUpdate()
{
    loggerService->log("Start update", LogType::Verbose, LogRemoteType::Slack, true);

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
    loggerService->log("Update complete, software version " + QString::number(newBuildVersion), LogType::Verbose, LogRemoteType::Slack, true);

    emit updateComplete(_updateConfig.runAppAfterUpdate, newBuildVersion);
    start();
}

void UpdaterService::autoCheckChanged(bool value)
{
    //TODO
    _updateConfig.autocheck = value;
    config->updateConfig->autocheck = value;
    //

    if(value)
    {
        resetTimer();
    }
    else
    {
        timer->stop();
    }
}

QString UpdaterService::getName() const
{
    return "UpdaterService";
}

int UpdaterService::timeToUpdate() const
{
    return _timeToUpdate;
}

void UpdaterService::setTimeToUpdate(int value)
{
    _timeToUpdate = value;
    emit timeToUpdateChanged();
}
