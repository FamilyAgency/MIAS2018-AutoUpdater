#include "Config.h"

Config::Config()
{
    mainConfig.reset(new MainConfig);
    processConfig.reset(new ProcessConfig);
    updateConfig.reset(new UpdateConfig);
}

QString Config::getRawData() const
{
    return rawData;
}

void Config::setRawData(const QString& value)
{
    rawData = value;
}
