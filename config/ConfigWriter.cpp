#include "ConfigWriter.h"
#include "ConfigLoader.h"
#include <QJsonDocument.h>
#include <QJsonObject.h>
#include <QJsonArray.h>

ConfigWriter::ConfigWriter()
{

}

void ConfigWriter::save(ConfigPtr config)
{
    qDebug()<< "save config.............";
}
