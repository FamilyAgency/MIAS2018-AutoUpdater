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
    QJsonDocument jsonDoc = QJsonDocument::fromJson(config->getRawData().toUtf8());
    QJsonObject jsonObj   = jsonDoc.object();
    jsonObj["version"] = QJsonValue::fromVariant(config->mainConfig->version);

    QJsonDocument doc(jsonObj);
    QFile saveFile(path);

    if (!saveFile.open(QIODevice::WriteOnly))
    {
        qWarning("Couldn't open save file.");
    }
    else
    {
        saveFile.write(doc.toJson());
    }
}
