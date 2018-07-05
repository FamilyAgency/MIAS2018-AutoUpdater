#include "MonitoringComponent.h"

MonitoringComponent::MonitoringComponent(QObject *parent) : BaseComponent(parent)
{
    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(onUpdate()));
    loggerService.reset(new LoggerService());
}

MonitoringComponent::~MonitoringComponent()
{
    if(timer)
    {
        disconnect(timer, SIGNAL(timeout()), this, SLOT(onUpdate()));
        delete timer;
    }
}

void MonitoringComponent::setConfig(ConfigPtr value)
{
    BaseComponent::setConfig(value);
    monitoringConfig = value->monitoringConfig;
    loggerService->setConfig(value);
}

void MonitoringComponent::start()
{
    BaseComponent::start();
    timer->start(monitoringConfig->memoryCheckMills);
}

void MonitoringComponent::onUpdate()
{
    QString outMemory = "check memory: " +  QString::number(memoryChecker.memoryUsed()) + " MB";
    loggerService->log(outMemory, LogType::Verbose, LogRemoteType::Slack, true);
}
