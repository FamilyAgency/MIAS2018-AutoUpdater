#include "ConfigWriter.h"
#include "ConfigLoader.h"
#include <QJsonDocument.h>
#include <QJsonObject.h>
#include <QJsonArray.h>
#include <QFile.h>

ConfigWriter::ConfigWriter()
{

}

ConfigWriter::~ConfigWriter()
{

}

void ConfigWriter::save(ConfigPtr config, const QString& path)
{ 
    saveSelfConfig(config, path);
    saveProcessfConfig(config, path);
}

void ConfigWriter::saveSelfConfig(ConfigPtr config, const QString& path)
{
    QJsonDocument jsonDoc = QJsonDocument::fromJson(config->getRawData().toUtf8());
    QJsonObject jsonObj   = jsonDoc.object();
    jsonObj["version"] = QJsonValue::fromVariant(config->mainConfig->version);

    QJsonDocument doc(jsonObj);
    QFile saveFile(path);

    if (saveFile.open(QIODevice::WriteOnly))
    {
        saveFile.write(doc.toJson());
        saveFile.close();
    }
    else
    {
       qWarning("Couldn't open save file.");
    }
}

void ConfigWriter::saveProcessfConfig(ConfigPtr config, const QString& path)
{
    QString processConfigPath = config->mainConfig->workingDirectory +  config->mainConfig->folderSeparator + "release\\config.json";
    QFile file(processConfigPath);

    if(file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        QString configContext = file.readAll();

        QJsonDocument jsonDoc = QJsonDocument::fromJson(configContext.toUtf8());
        QJsonObject jsonObj   = jsonDoc.object();
        jsonObj["version"] = QJsonValue::fromVariant(config->mainConfig->version);
        jsonObj["appId"] = QJsonValue::fromVariant(config->mainConfig->appId);
        qDebug()<<"write appid"<<QJsonValue::fromVariant(config->mainConfig->appId);

        QFile saveFile(processConfigPath);
        QJsonDocument doc(jsonObj);

        if (!saveFile.open(QIODevice::WriteOnly))
        {
            qWarning("Couldn't open save file.");
        }
        else
        {
            saveFile.write(doc.toJson());
            saveFile.close();
        }

        file.close();
    }
}
