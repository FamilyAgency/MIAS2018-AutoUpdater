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

void StandData::setConfig(const MainConfig& config)
{
    //TODO
    _mainConfig = config;
    emit configChanged();
}

MainConfig StandData::config() const
{
    return _mainConfig;
}
