#include "UpdaterService.h"
#include <QDirIterator>

UpdaterService::UpdaterService(QObject *parent) : BaseService(parent)
{
    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(onUpdate()));
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
    config = value;
    setUpdateConfig(value->updateData);
}

void UpdaterService::setUpdateConfig(const UpdateConfig& value)
{
    _updateConfig = value;
    emit updateConfigChanged();
}

void UpdaterService::start()
{
    if(_updateConfig.autocheck)
    {
        startTime = QDateTime::currentMSecsSinceEpoch();
        timer->start(taskTimerMills) ;
        qDebug()<<"updaterService start";
    }
}

void UpdaterService::onUpdate()
{
    int time = QDateTime::currentMSecsSinceEpoch() - startTime;
    int diff = _updateConfig.frequency - time;
    if(diff > 0)
    {
        setTimeToUpdate(diff / 1000 + 1);
    }
    else
    {
        timer->stop();
        checkUpdate();
    }
}

UpdateConfig UpdaterService::updateConfig() const
{
    return _updateConfig;
}

void UpdaterService::stop()
{

}

void UpdaterService::checkUpdate()
{
    // startTime = QDateTime::currentMSecsSinceEpoch();
    // timer->start();
     QStringList fileList;
    if(hasUpdate(fileList))
    {
        loadUpdate(fileList);
    }
}

bool UpdaterService::hasUpdate(QStringList& fileList)
{
    int lastVersionNum = config->configData.version;

    QDir dir(_updateConfig.folderCheck);
    QFileInfoList list = dir.entryInfoList(QDir::Dirs | QDir::NoDotAndDotDot);

    QDir newBuildDir = "";

    foreach(QFileInfo finfo, list)
    {
        QString pattern = "build";
        QString fileName = finfo.fileName();
        int index = fileName.indexOf(pattern);
        if(index != -1)
        {
            QString versionNewString = fileName.right(fileName.length() - index - pattern.length());
            int versionNew  = versionNewString.toInt();
            if(versionNew > lastVersionNum)
            {
                lastVersionNum = versionNew;
                newBuildDir = finfo.absoluteFilePath();
            }
        }
    }
   // recurseAddDir(newBuildDir, fileList);

    qDebug()<<"file nums : "<<fileList.length();
    qDebug()<<"file nums : "<<newBuildDir.absolutePath();

    QDir destDir = "c:\\projects\\Qt\\MIAS2018\\AutoUpdater\\process\\release_temp";
    qDebug()<<"........ "<<newBuildDir.absolutePath()<<destDir.absolutePath();
    copyPath(newBuildDir.absolutePath(), destDir.absolutePath(), true);


    setNeedUpdate(fileList.count() > 0 );
    return _needUpdate;
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

void UpdaterService::recurseAddDir(const QDir& fromDir, QStringList& list)
{
    QStringList qsl = fromDir.entryList(QDir::NoDotAndDotDot | QDir::Dirs | QDir::Files);

    foreach (QString file, qsl)
    {

        QFileInfo finfo(QString("%1/%2").arg(fromDir.path()).arg(file));

        if (finfo.isSymLink())
        {
            return;
        }

        if (finfo.isDir())
        {
            QString dirname = finfo.fileName();
            QDir sd(finfo.filePath());
            recurseAddDir(sd, list);
        }
        else
        {
            list << QDir::toNativeSeparators(finfo.filePath());
        }
    }
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

void UpdaterService::loadUpdate(QStringList& fileList)
{

}

void UpdaterService::onUpdateLoaded()
{
    emit pendingUpdate();
}

void UpdaterService::startUpdate()
{
    //rename apps;
    //emit updateComplete();
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
