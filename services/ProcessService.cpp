#include "ProcessService.h"
#include <QDirIterator>

ProcessService::ProcessService(QObject *parent) : BaseService(parent)
{
    process = new QProcess(this);
    connect(process, SIGNAL(readyReadStandardError()),this, SLOT(onReadyReadStandardError()));
    connect(process, SIGNAL(finished(int)), this, SLOT(onProcessFinished(int)));
    connect(process, SIGNAL(started()), this, SLOT(onProcessStarted()));
    connect(process, SIGNAL(errorOccurred(QProcess::ProcessError)), this, SLOT(onErrorOccurred(QProcess::ProcessError)));
}

ProcessService::~ProcessService()
{
    disconnect(process, SIGNAL(readyReadStandardError()),this, SLOT(onReadyReadStandardError()));
    disconnect(process, SIGNAL(finished(int)), this, SLOT(onProcessFinished(int)));
    disconnect(process, SIGNAL(started()), this, SLOT(onProcessStarted()));
    disconnect(process, SIGNAL(errorOccurred(QProcess::ProcessError)), this, SLOT(onErrorOccurred(QProcess::ProcessError)));

    if(process)
    {
        if(process->isOpen())
        {
            process->close();
        }
        delete process;
    }
}

void ProcessService::setQmlContext(QQmlContext* qmlContext)
{
    BaseService::setQmlContext(qmlContext);
    qmlContext->setContextProperty("processService", this);
}

void ProcessService::setConfig(ConfigPtr value)
{
    BaseService::setConfig(value);
    config = value;
    setProcesConfig(value->processData);
}

void ProcessService::setProcesConfig(const ProcessConfig& value)
{
    _processConfig = value;  
    emit processConfigChanged();
}

ProcessConfig ProcessService::processConfig() const
{
    return _processConfig;
}

void ProcessService::startApp()
{
    program = _processConfig.path;
    process->start(program);
}

QString ProcessService::findAppFullPath() const
{
    QDir dir(_processConfig.path);
    QFileInfoList list = dir.entryInfoList(QDir::Files | QDir::Dirs | QDir::NoDotAndDotDot);
    foreach(QFileInfo finfo, list)
    {
        qDebug() <<  finfo.fileName();
    }

    return  "...";
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
    if(_processConfig.autorun)
    {
        startApp();
    }
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


