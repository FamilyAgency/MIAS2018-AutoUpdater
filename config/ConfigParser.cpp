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

        parseConfigData(config->mainConfig, jsonObj);
        parseProcessData(config->processConfig, jsonObj["process"].toObject());
        parseUpdateData(config->updateConfig, jsonObj["update"].toObject());

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

void ConfigParser::parseConfigData(QSharedPointer<MainConfig> mainConfig, const QJsonObject& jsonObj)
{
    mainConfig->version = jsonObj["version"].toInt();
    mainConfig->configUpdateUrl = jsonObj["configUpdateUrl"].toString();
    mainConfig->needRemoteUpdate = jsonObj["needRemoteUpdate"].toBool();
    mainConfig->standId = jsonObj["standId"].toInt();
    mainConfig->workingDirectory = jsonObj["workingDirectory"].toString();
    mainConfig->folderSeparator = jsonObj["folderSeparator"].toString();
}

void ConfigParser::parseProcessData(QSharedPointer<ProcessConfig> processConfig, const QJsonObject& jsonObj)
{
    processConfig->path = jsonObj["path"].toString();
    processConfig->autorun = jsonObj["autorun"].toBool();
    processConfig->startDelayMills = jsonObj["startDelayMills"].toInt();
}

void ConfigParser::parseUpdateData(QSharedPointer<UpdateConfig> updateConfig, const QJsonObject& jsonObj)
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
