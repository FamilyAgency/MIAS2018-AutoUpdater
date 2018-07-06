#include "LoggerService.h"
#include <QDateTime>
#include <QCoreApplication>
#include <QDir>

LoggerService::LoggerService(QObject *parent) : BaseService(parent)
{
    slackComponent.reset(new SlackComponent());
    connect(slackComponent.data(), SIGNAL(slackNotifyResponse(const QString&)), this, SLOT(onSlackNotifyResponse(const QString&)));
}

LoggerService::~LoggerService()
{
    disconnect(slackComponent.data(), SIGNAL(slackNotifyResponse(const QString&)), this, SLOT(onSlackNotifyResponse(const QString&)));
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
    qDebug()<<message;

    QString color;
    QString slackChannel = config->slackConfig->logChannel;

    switch(type)
    {
    case LogType::Verbose:
        color = "black";
        break;

    case LogType::Error:
        color = "red";
        slackChannel = config->slackConfig->errorChannel;
        break;

    case LogType::Warning:
        color = "yellow";
        break;
    }

    switch(remoteType)
    {
    case LogRemoteType::Slack:
        slackComponent->sendMessage(createSlackMessage(message), slackChannel);
        break;

    case LogRemoteType::Server:
        break;
    }

    if(saveLocal && config->loggerConfig->localEnabled)
    {
        logTofile(message);
    }
}

void LoggerService::onSlackNotifyResponse(const QString& message)
{
    if(config->loggerConfig->localEnabled)
    {
        logTofile("Slack notify : " + message);
    }
}

void LoggerService::logTofile(const QString& message)
{
    QFile file(getLocalLogAbsoluteFilePath());
    file.open(QIODevice::Append | QIODevice::Text);
    if(file.isOpen())
    {
        QTextStream out(&file);
        out<<createLocalMessage(message)<<endl;
        file.close();
    }
}

QString LoggerService::createSlackMessage(const QString& message) const
{
    QDateTime now = QDateTime::currentDateTime();
    QString currentTime = "[" + now.date().toString() + " " + now.time().toString() + ": ";
    QString appData =  appName + " " + QString::number(appId) + "] ";
    return  currentTime + appData + message;
}

QString LoggerService::createLocalMessage(const QString& message) const
{
    QDateTime now = QDateTime::currentDateTime();
    QString currentTime = "[" + now.time().toString() + ": ";
    QString appData =  appName + " " + QString::number(appId) + "] ";
    QString localMessage = currentTime + appData + message;
    return localMessage;
}

QString LoggerService::getLocalLogAbsoluteFilePath() const
{
    QDateTime now = QDateTime::currentDateTime();
    QString fileFullPath = getLocalLogDirPath() + "/" + now.date().toString() +".txt";
    return fileFullPath;
}

QString LoggerService::getLocalLogDirPath() const
{
   return QCoreApplication::applicationDirPath() + "/" + config->loggerConfig->localPath;
}

void LoggerService::start()
{
    if(!QDir(getLocalLogDirPath()).exists())
    {
        QDir().mkdir(getLocalLogDirPath());
    }
}

void LoggerService::stop()
{

}

QString LoggerService::getName() const
{
    return "Logger";
}
