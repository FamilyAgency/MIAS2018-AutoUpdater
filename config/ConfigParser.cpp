#include "ConfigParser.h"
#include "ConfigLoader.h"
#include "Config.h"

#include <QJsonDocument.h>
#include <QJsonObject.h>
#include <QJsonArray.h>
#include <QDebug.h>

ConfigParser::ConfigParser()
{
    config.reset(new Config());
}

ConfigParser::~ConfigParser()
{

}

void ConfigParser::parse(const QString& configData)
{
    try
    {
        //qDebug()<<"configData................"<<endl;
        //qDebug()<<configData <<endl;
        //qDebug()<<"configData................"<<endl;
        QJsonDocument jsonDoc = QJsonDocument::fromJson(configData.toUtf8());
        QJsonObject jsonObj   = jsonDoc.object();

        parseMainConfig(config->mainConfig, jsonObj);
        parseProcessConfig(config->processConfig, jsonObj["process"].toObject());
        parseUpdateConfig(config->updateConfig, jsonObj["update"].toObject());
        parseSlackConfig(config->slackConfig, jsonObj["slack"].toObject());
        parseMonitoringConfig(config->monitoringConfig, jsonObj["monitoring"].toObject());

        config->setRawData(configData);
        config->valid = true;
        emit parseComplete(config);
    }
    catch(...)
    {
        config->valid = false;
        qDebug()<<"parsing error................";
    }
}

void ConfigParser::parseMainConfig(QSharedPointer<MainConfig> mainConfig, const QJsonObject& jsonObj)
{
    mainConfig->version = jsonObj["version"].toInt();
    mainConfig->configUpdateUrl = jsonObj["configUpdateUrl"].toString();
    mainConfig->needRemoteUpdate = jsonObj["needRemoteUpdate"].toBool();
    mainConfig->standId = jsonObj["standId"].toInt();
    mainConfig->workingDirectory = jsonObj["workingDirectory"].toString();
    mainConfig->folderSeparator = jsonObj["folderSeparator"].toString();
}

void ConfigParser::parseProcessConfig(QSharedPointer<ProcessConfig> processConfig, const QJsonObject& jsonObj)
{
    processConfig->path = jsonObj["path"].toString();
    processConfig->autorun = jsonObj["autorun"].toBool();
    processConfig->startDelayMills = jsonObj["startDelayMills"].toInt();
}

void ConfigParser::parseUpdateConfig(QSharedPointer<UpdateConfig> updateConfig, const QJsonObject& jsonObj)
{
    UpdateConfig ;
    updateConfig->checkDirectory = jsonObj["checkDirectory"].toString();
    updateConfig->lastUpdateDate = jsonObj["lastUpdateDate"].toString();
    updateConfig->millsCheck = jsonObj["millsCheck"].toInt();
    updateConfig->autocheck = jsonObj["autocheck"].toBool();
    updateConfig->patternCheck = jsonObj["patternCheck"].toString();
    updateConfig->releaseDirectory = jsonObj["releaseDirectory"].toString();
    updateConfig->tempDirectory = jsonObj["tempDirectory"].toString();
    updateConfig->oldDirectory = jsonObj["oldDirectory"].toString();
    updateConfig->runAppAfterUpdate = jsonObj["runAppAfterUpdate"].toBool();
    updateConfig->autoupdate = jsonObj["autoupdate"].toBool();
}

void ConfigParser::parseSlackConfig(QSharedPointer<SlackConfig> slackConfig, const QJsonObject& jsonObj)
{  
    slackConfig->logChannel = jsonObj["logChannel"].toString();
    slackConfig->errorChannel = jsonObj["errorChannel"].toString();
    slackConfig->enabled = jsonObj["enabled"].toBool();
}

void ConfigParser::parseMonitoringConfig(QSharedPointer<MonitoringConfig> monitoringConfig, const QJsonObject& jsonObj)
{
     monitoringConfig->memoryCheckMills = jsonObj["memoryCheckMills"].toInt();
     monitoringConfig->enabled = jsonObj["enabled"].toBool();
}
