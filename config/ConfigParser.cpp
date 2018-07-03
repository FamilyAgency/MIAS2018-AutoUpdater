#include "ConfigParser.h"
#include "ConfigLoader.h"
#include "Config.h"

#include <QJsonDocument.h>
#include <QJsonObject.h>
#include <QJsonArray.h>
#include <QDebug.h>

ConfigParser::ConfigParser()
{
    config = new Config();
}

void ConfigParser::parse(const QString& configData)
{
    try
    {
//        qDebug()<<"configData................"<<endl;
//        qDebug()<<configData <<endl;
//        qDebug()<<"configData................"<<endl;
        QJsonDocument jsonDoc = QJsonDocument::fromJson(configData.toUtf8());
        QJsonObject jsonObj   = jsonDoc.object();

        config->configData   = parseConfigData(jsonObj);
        config->arduinoData  = parseRFIDData(jsonObj["rfid"].toObject());
        config->mindwaveData = parseMindwaveData(jsonObj["mindwave"].toObject());
        config->serverData   = parseServerData(jsonObj["server"].toObject());
        config->slackData    = parseSlackData(jsonObj["slack"].toObject());

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
    configData.version = jsonObj["version"].toString();
    configData.configUpdateUrl = jsonObj["configUpdateUrl"].toString();
    configData.needRemoteUpdate = jsonObj["needRemoteUpdate"].toBool();
    configData.standId = jsonObj["standId"].toInt();
    configData.appTypeId = jsonObj["appTypeId"].toInt();

    QJsonObject touchScreenData = jsonObj["screens"].toObject()["touch"].toObject();
    configData.touchScreen.setX(touchScreenData["x"].toInt());
    configData.touchScreen.setY(touchScreenData["y"].toInt());
    configData.touchScreen.setWidth(touchScreenData["width"].toInt());
    configData.touchScreen.setHeight(touchScreenData["height"].toInt());

    QJsonObject gameScreenData = jsonObj["screens"].toObject()["game"].toObject();
    configData.gameScreen.setX(gameScreenData["x"].toInt());
    configData.gameScreen.setY(gameScreenData["y"].toInt());
    configData.gameScreen.setWidth(gameScreenData["width"].toInt());
    configData.gameScreen.setHeight(gameScreenData["height"].toInt());

    return configData;
}

RFIDConfig ConfigParser::parseRFIDData(const QJsonObject& jsonObj)
{
    RFIDConfig rfid;
    rfid.serialPort = jsonObj["serialPort"].toString();
    rfid.baudRate = jsonObj["baudRate"].toInt();
    rfid.autoConnect = jsonObj["autoConnect"].toBool();
    rfid.portKeyWord = jsonObj["portKeyWord"].toString();
    rfid.useKeyword = jsonObj["useKeyword"].toBool();
    return rfid;
}

MindwaveConfig ConfigParser::parseMindwaveData(const QJsonObject& jsonObj)
{
    MindwaveConfig mindwave;
    mindwave.ip = jsonObj["ip"].toString();
    mindwave.port = jsonObj["port"].toInt();
    mindwave.autoConnect = jsonObj["autoConnect"].toBool();
    mindwave.delimeter = jsonObj["delimeter"].toString();
    mindwave.initialCommand = jsonObj["initialCommand"].toString();
    mindwave.authCommand = jsonObj["authCommand"].toString();
    return mindwave;
}

ServerConfig ConfigParser::parseServerData(const QJsonObject& jsonObj)
{
    ServerConfig server;
    server.url = jsonObj["url"].toString();
    return server;
}

SlackConfig ConfigParser::parseSlackData(const QJsonObject& jsonObj)
{
    SlackConfig slack;

    int id = 0; //config->configData.standId

    QJsonArray logChannels = jsonObj["logChannels"].toArray();
    slack.logChannel = logChannels[id].toString();

    QJsonArray errChannels = jsonObj["errorChannels"].toArray();
    slack.errChannel = errChannels[id].toString();

    return slack;
}
