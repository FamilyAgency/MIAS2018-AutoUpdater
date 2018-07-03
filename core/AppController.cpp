#include "AppController.h"

AppController::AppController(QObject *parent) : QObject(parent)
{ 
    standData = new StandData();
    processService = new ProcessService();
    updaterService  = new UpdaterService();
    connect(updaterService, SIGNAL(pendingUpdate()), this, SLOT(onPendingUpdate()));
    connect(updaterService, SIGNAL(updateComplete()), this, SLOT(onUpdateComplete()));
    connect(updaterService, SIGNAL(updateError()), this, SLOT(onUpdateError()));
    connect(updaterService, SIGNAL(updateLoadingError()), this, SLOT(onUpdateLoadingError()));
}

void AppController::setQmlContext(QQmlContext* qmlContext)
{
    processService->setQmlContext(qmlContext);
    updaterService->setQmlContext(qmlContext);
}

void AppController::onConfigLoaded(Config* config)
{
    updaterService->setConfig(config);
    processService->setConfig(config);

    if( !updaterService->hasUpdate())
    {
        processService->startApp();
    }
    else
    {
        //wait for loading;
    }

}

void AppController::onPendingUpdate()
{
    processService->stopApp();
    updaterService->startUpdate();
}

void AppController::onUpdateComplete()
{

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





