#include "StandData.h"
#include <QGuiApplication.h>
#include <QScreen.h>

StandData::StandData(QObject *parent) : QObject(parent)
{

}

void StandData::setQmlContext(QQmlContext* value)
{
    qmlContext = value;
    qmlContext->setContextProperty("standData", this);
}

void StandData::setConfig(ConfigPtr value)
{
    setMainConfig(*value->mainConfig);
}

void StandData::setMainConfig(MainConfig config)
{
    _mainConfig = config;
    emit mainConfigChanged();
}

MainConfig StandData::mainConfig() const
{
    return _mainConfig;
}
