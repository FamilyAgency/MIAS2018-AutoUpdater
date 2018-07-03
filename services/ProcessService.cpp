#include "ProcessService.h"

ProcessService::ProcessService(QObject *parent) : BaseService(parent)
{
    process = new QProcess(this);
    connect(process, SIGNAL(readyReadStandardError()),this, SLOT(onReadyReadStandardError()));
    connect(process, SIGNAL(finished(int)), this, SLOT(onProcessFinished(int)));
    connect(process, SIGNAL(started()), this, SLOT(onProcessStarted()));
    connect(process, SIGNAL(errorOccurred(QProcess::ProcessError)), this, SLOT(onErrorOccurred(QProcess::ProcessError)));

}

void ProcessService::setQmlContext(QQmlContext* qmlContext)
{
    BaseService::setQmlContext(qmlContext);
    qmlContext->setContextProperty("processService", this);
}


void ProcessService::startApp()
{
    program = "c:\\projects\\Qt\\MIAS2018\\StandClient\\release\\MindwaveGameClient.exe";
    args.clear();
    //QString argStr = "processConfig=" + processConfig[id].getConfigPath();
   // args.push_back(argStr);
    process->start(program, args);
}

bool ProcessService::running() const
{
    return _running;
}

void ProcessService::setRunning(bool value)
{
    _running = value;
    emit runningChanged();
}

void ProcessService::stopApp()
{
    process->close();
}


void ProcessService::start()
{

}

void ProcessService::stop()
{

}

QString ProcessService::getName() const
{
     return "ProcessService";
}

void ProcessService::onReadyReadStandardError()
{
    qDebug()<<"ready Read Standard Error";
}

void ProcessService::onProcessFinished(int value)
{
    qDebug()<<"process Finished";
    setRunning(false);
    emit processStopped(value);
}

void ProcessService::onProcessStarted()
{
   qDebug()<<"process Started";
   setRunning(true);
}

void ProcessService::onErrorOccurred(QProcess::ProcessError error)
{
    qDebug()<<"error Occurred "<<error;
}


