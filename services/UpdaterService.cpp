#include "UpdaterService.h"
#include <QDirIterator>

UpdaterService::UpdaterService(QObject *parent) : BaseService(parent)
{
    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(onUpdate()));
    connect(this, SIGNAL(updateCheckingComplete(bool)), this, SLOT(onUpdateCheckingComplete(bool)));
    loggerComponent.reset(new LoggerComponent());    

    setUpdatePercent(0.0f);
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
    loggerComponent->setConfig(value);
}

void UpdaterService::setUpdateConfig(const UpdateConfig& value)
{
    _updateConfig = value;
    emit updateConfigChanged();
}

void UpdaterService::start()
{
    loggerComponent->start();

    if(_updateConfig.autocheck)
    {
        startTime = QDateTime::currentMSecsSinceEpoch();
        timer->start(taskTimerMills);
    }
}

void UpdaterService::stop()
{
    timer->stop();
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
        checkUpdate();
    }
}

void UpdaterService::forceCheckUpdate()
{
    checkUpdate();
}

void UpdaterService::onUpdateCheckingComplete(bool updateAvailable)
{
    if(updateAvailable && _updateConfig.autoupdate)
    {
        emit pendingUpdate();
    }
    else
    {
        resetTimer();
    }
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

void UpdaterService::onUpdateLoaded()
{
    emit pendingUpdate();
}

void UpdaterService::forceStartUpdate()
{
    timer->stop();
    emit pendingUpdate();
}

void UpdaterService::autoCheckChanged(bool value)
{
    //TODO
    _updateConfig.autocheck = value;
    config->updateConfig->autocheck = value;

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

float UpdaterService::updatePercent() const
{
    return _updatePercent;
}

void UpdaterService::setUpdatePercent(float value)
{
    _updatePercent = value;
    emit updatePercentChanged();
}

void setUpdatePercent(float value);

UpdateConfig UpdaterService::updateConfig() const
{
    return _updateConfig;
}
