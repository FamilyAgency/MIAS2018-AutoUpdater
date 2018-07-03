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


    connect(processService, SIGNAL(processStopped(int)), this, SLOT(onProcessStopped(int)));
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





