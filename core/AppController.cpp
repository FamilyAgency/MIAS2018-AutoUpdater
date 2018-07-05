#include "AppController.h"

AppController::AppController(QObject *parent) : QObject(parent)
{ 
    standData.reset(new StandData());

    processService.reset(new ProcessService());
    connect(processService.data(), SIGNAL(processStopped(int)), this, SLOT(onProcessStopped(int)));

    updaterService.reset(new UpdaterService());
    connect(updaterService.data(), SIGNAL(pendingUpdate()), this, SLOT(onPendingUpdate()));
    connect(updaterService.data(), SIGNAL(updateComplete(bool, int)), this, SLOT(onUpdateComplete(bool, int)));
    connect(updaterService.data(), SIGNAL(updateError()), this, SLOT(onUpdateError()));
    connect(updaterService.data(), SIGNAL(updateLoadingError()), this, SLOT(onUpdateLoadingError()));

    monitoringComponent.reset(new MonitoringComponent());
}

AppController::~AppController()
{
    disconnect(processService.data(), SIGNAL(processStopped(int)), this, SLOT(onProcessStopped(int)));
    disconnect(updaterService.data(), SIGNAL(pendingUpdate()), this, SLOT(onPendingUpdate()));
    disconnect(updaterService.data(), SIGNAL(updateComplete(bool, int)), this, SLOT(onUpdateComplete(bool, int)));
    disconnect(updaterService.data(), SIGNAL(updateError()), this, SLOT(onUpdateError()));
    disconnect(updaterService.data(), SIGNAL(updateLoadingError()), this, SLOT(onUpdateLoadingError()));
}

void AppController::setQmlContext(QQmlContext* qmlContext)
{
    standData->setQmlContext(qmlContext);
    processService->setQmlContext(qmlContext);
    updaterService->setQmlContext(qmlContext);
}

void AppController::onConfigLoaded(ConfigPtr value)
{
    config = value;
    start();
}

void AppController::onPendingUpdate()
{    
    if(processService->processState() != ProcessService::ProcessState::Stopped)
    {
        processService->stopApp();
    }
    else
    {
        updaterService->startUpdate();
    }
}

void AppController::onUpdateComplete(bool runApp, int newBuildVersion)
{
    config->mainConfig->version = newBuildVersion;
    updateAllConfigs();
    emit pendingSaveConfig();

    if(runApp)
    {
         processService->startApp();
    }
}

void AppController::onProcessStopped(int value)
{
    if(updaterService->needUpdate())
    {
        updaterService->startUpdate();
    }
}

void AppController::onUpdateError()
{

}

void AppController::onUpdateLoadingError()
{

}

void AppController::onConfigError()
{
    qDebug() << "config Service Error";
}

void AppController::start()
{
    updateAllConfigs();
    updaterService->start();
    processService->start();
    monitoringComponent->start();
}

void AppController::updateAllConfigs()
{
    updaterService->setConfig(config);
    standData->setConfig(config);
    processService->setConfig(config);
    monitoringComponent->setConfig(config);
}
