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
//      qDebug()<<"configData................"<<endl;
//      qDebug()<<configData <<endl;
//      qDebug()<<"configData................"<<endl;
        QJsonDocument jsonDoc = QJsonDocument::fromJson(configData.toUtf8());
        QJsonObject jsonObj   = jsonDoc.object();

        config->configData   = parseConfigData(jsonObj);
        config->processData  = parseProcessData(jsonObj["process"].toObject());
        config->updateData   = parseUpdateData(jsonObj["update"].toObject());

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

MainConfig ConfigParser::parseConfigData(const QJsonObject& jsonObj)
{
    MainConfig configData;
    configData.version = jsonObj["version"].toInt();
    configData.configUpdateUrl = jsonObj["configUpdateUrl"].toString();
    configData.needRemoteUpdate = jsonObj["needRemoteUpdate"].toBool();
    configData.standId = jsonObj["standId"].toInt();
    configData.appTypeId = jsonObj["appTypeId"].toInt();
    return configData;
}

ProcessConfig ConfigParser::parseProcessData(const QJsonObject& jsonObj)
{
    ProcessConfig process;
    process.path = jsonObj["path"].toString();
    process.autorun = jsonObj["autorun"].toBool();
    return process;
}

UpdateConfig ConfigParser::parseUpdateData(const QJsonObject& jsonObj)
{
    UpdateConfig update;
    update.folderCheck = jsonObj["folderCheck"].toString();
    update.lastUpdateDate = jsonObj["lastUpdateDate"].toString();
    update.frequency = jsonObj["frequency"].toInt();
    update.autocheck = jsonObj["autocheck"].toBool();
    return update;
}
