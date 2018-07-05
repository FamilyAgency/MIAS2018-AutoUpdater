#include "ProcessService.h"
#include <QDirIterator>
#include <QTimer>

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

    if(process && process->isOpen())
    {
        process->close();
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
    setProcesConfig(*value->processConfig);
}

QString ProcessService::getProcessFullPath() const
{
    return config->mainConfig->workingDirectory +
           config->mainConfig->folderSeparator +
           _processConfig.path;
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

void ProcessService::start()
{
    if(_processConfig.autorun)
    {
        startApp();
    }
}

void ProcessService::stop()
{
    stopApp();
}

void ProcessService::startApp()
{
    if(_processState == ProcessState::Stopped)
    {
       setProcessState(ProcessState::PendingStart);
       QTimer::singleShot(_processConfig.startDelayMills, this, SLOT(startUpWithDelay()));
    }
}

void ProcessService::startUpWithDelay()
{
    program = getProcessFullPath();
    process->start(program);
}

void ProcessService::onProcessStarted()
{
    qDebug()<<"process Started";
    setProcessState(ProcessState::Running);
}

void ProcessService::stopApp()
{
    process->close();
}

void ProcessService::onProcessFinished(int value)
{
   setProcessState(ProcessState::Stopped);
   emit processStopped(value);
}

ProcessService::ProcessState ProcessService::processState() const
{
    return _processState;
}

void ProcessService::setProcessState(ProcessState value)
{
    _processState = value;
    emit processStateChanged();
}

QString ProcessService::getName() const
{
    return "ProcessService";
}

void ProcessService::onReadyReadStandardError()
{
    qDebug()<<"ready Read Standard Error";
}

void ProcessService::onErrorOccurred(QProcess::ProcessError error)
{
    qDebug()<<"error Occurred "<<error;
}


