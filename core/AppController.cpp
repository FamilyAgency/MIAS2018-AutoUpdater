#include "AppController.h"

AppController::AppController(QObject *parent) : QObject(parent)
{ 
    standData.reset(new StandData());

    processService.reset(new ProcessService());
    connect(processService.data(), SIGNAL(processStopped(int)), this, SLOT(onProcessStopped(int)));

    updaterService.reset(new UpdaterService());
    connect(updaterService.data(), SIGNAL(pendingUpdate()), this, SLOT(onPendingUpdate()));
    connect(updaterService.data(), SIGNAL(updateComplete()), this, SLOT(onUpdateComplete()));
    connect(updaterService.data(), SIGNAL(updateError()), this, SLOT(onUpdateError()));
    connect(updaterService.data(), SIGNAL(updateLoadingError()), this, SLOT(onUpdateLoadingError()));
}

AppController::~AppController()
{
    disconnect(processService.data(), SIGNAL(processStopped(int)), this, SLOT(onProcessStopped(int)));
    disconnect(updaterService.data(), SIGNAL(pendingUpdate()), this, SLOT(onPendingUpdate()));
    disconnect(updaterService.data(), SIGNAL(updateComplete()), this, SLOT(onUpdateComplete()));
    disconnect(updaterService.data(), SIGNAL(updateError()), this, SLOT(onUpdateError()));
    disconnect(updaterService.data(), SIGNAL(updateLoadingError()), this, SLOT(onUpdateLoadingError()));
}

void AppController::setQmlContext(QQmlContext* qmlContext)
{
    processService->setQmlContext(qmlContext);
    updaterService->setQmlContext(qmlContext);
}

void AppController::onConfigLoaded(ConfigPtr config)
{    
    updaterService->setConfig(config);
    processService->setConfig(config);
    updaterService->start();
    processService->start();

    if( !updaterService->hasUpdate())
    {
       // processService->startApp();
    }
    else
    {
        //wait for loading;
    }
}

void AppController::onPendingUpdate()
{
    processService->stopApp();
}

void AppController::onUpdateComplete()
{

}

void AppController::onProcessStopped(int value)
{
    updaterService->startUpdate();
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

}
