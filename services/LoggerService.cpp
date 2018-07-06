#include "LoggerService.h"
#include <QDateTime>

LoggerService::LoggerService(QObject *parent) : BaseService(parent)
{
   slackComponent.reset(new SlackComponent());
}

void LoggerService::setConfig(ConfigPtr value)
{
    BaseService::setConfig(value);
    appId = value->mainConfig->appId;
    appName = value->mainConfig->appName;
    slackComponent->setConfig(value);
}

void LoggerService::setQmlContext(QQmlContext* qmlContext)
{
    qmlContext->setContextProperty("logger", this);
}

void LoggerService::log(const QString& message, LogType type, LogRemoteType remoteType, bool saveLocal)
{
    QDateTime now = QDateTime::currentDateTime();
    QString currentTime = "[" + now.date().toString() + " " + now.time().toString() + "] ";
    QString appData =  appName + " " + QString::number(appId) + " ";
    QString logMessage =  currentTime + appData + message;

    qDebug()<<logMessage;

    switch(remoteType)
    {
    case LogRemoteType::Slack:
        slackComponent->sendMessage(logMessage, config->slackConfig->logChannel);
        break;

    case LogRemoteType::Server:
        break;
    }

    QString color;
    switch(remoteType)
    {

    case LogType::Verbose:
        color = "black";
        break;

    case LogType::Error:
        color = "red";
        break;

    case LogType::Warning:
        color = "yellow";
        break;
    }

    if(saveLocal)
    {

    }
}

void LoggerService::start()
{

}

void LoggerService::stop()
{

}

QString LoggerService::getName() const
{
    return "Logger";
}


