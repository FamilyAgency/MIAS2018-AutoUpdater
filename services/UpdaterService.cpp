#include "UpdaterService.h"

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

void UpdaterService::start()
{   
    startTime = QDateTime::currentMSecsSinceEpoch();
    timer->start(taskTimerMills);
    qDebug()<<"updaterService start";
}

void UpdaterService::setQmlContext(QQmlContext* qmlContext)
{
    BaseService::setQmlContext(qmlContext);
    qmlContext->setContextProperty("updaterService", this);
}

void UpdaterService::onUpdate()
{
    int time = QDateTime::currentMSecsSinceEpoch() - startTime;
    int diff = timeCheck - time;
    if(diff > 0)
    {
        setTimeToUpdate(diff / 1000 + 1);
    }
    else
    {
        timer->stop();
        startTime = QDateTime::currentMSecsSinceEpoch();
        timer->start();
    }
}

void UpdaterService::stop()
{

}

void UpdaterService::startUpdate()
{

}

bool UpdaterService::hasUpdate() const
{
    return false;
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
