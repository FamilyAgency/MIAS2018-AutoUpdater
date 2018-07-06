#include "AppController.h"
#include "services/UpdaterServiceFolder.h"

AppController::AppController(QObject *parent) : QObject(parent)
{ 
    standData.reset(new StandData());

    processService.reset(new ProcessService());
    services.push_back(processService);
    connect(processService.data(), SIGNAL(processStopped(int)), this, SLOT(onProcessStopped(int)));

    updaterService.reset(new UpdaterServiceFolder());
    services.push_back(updaterService);
    connect(updaterService.data(), SIGNAL(pendingUpdate()), this, SLOT(onPendingUpdate()));
    connect(updaterService.data(), SIGNAL(updateComplete(bool, int)), this, SLOT(onUpdateComplete(bool, int)));
    connect(updaterService.data(), SIGNAL(updateError()), this, SLOT(onUpdateError()));
    connect(updaterService.data(), SIGNAL(updateLoadingError()), this, SLOT(onUpdateLoadingError()));

    monitoringComponent.reset(new MonitoringComponent());
    components.push_back(monitoringComponent);
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

    for(auto service: services)
    {
        service->setQmlContext(qmlContext);
    }
}

void AppController::onConfigLoaded(ConfigPtr value)
{
    config = value;
    start();
}

void AppController::onPendingUpdate()
{    
    if(processService->isStopped())
    {
        updaterService->startUpdate();
    }
    else
    {
        processService->stopApp();
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
    for(auto service: services)
    {
        service->start();
    }

    for(auto comp: components)
    {
        comp->start();
    }
}

void AppController::updateAllConfigs()
{
    standData->setConfig(config);

    for(auto service: services)
    {
        service->setConfig(config);
    }

    for(auto comp: components)
    {
        comp->setConfig(config);
    }
}
