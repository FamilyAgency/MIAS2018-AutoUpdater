#include "LoggerService.h"
#include <QDateTime>

LoggerService::LoggerService(QObject *parent) : BaseService(parent)
{

}

void LoggerService::setConfig(ConfigPtr config)
{
    standId = config->configData.standId;
}

void LoggerService::setQmlContext(QQmlContext* qmlContext)
{
    qmlContext->setContextProperty("LoggerService", this);
}

//void LoggerService::setSlackComponent(SlackComponent* component)
//{
//    slackComponent = component;
//}

void LoggerService::log(const QString& message, LogType type, RemoteType remoteType, bool saveLocal)
{
    QDateTime now = QDateTime::currentDateTime();
    QString logMessage = "[" +now.date().toString() + " " +  now.time().toString() + "] : Stand " + QString::number(standId) + " :  " + message;

    switch(remoteType)
    {

    case RemoteType::Slack:
       // slackComponent->sendMessage(logMessage, type);
        break;

    case RemoteType::Server:

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


