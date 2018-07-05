#include "Config.h"

Config::Config()
{
    mainConfig.reset(new MainConfig);
    processConfig.reset(new ProcessConfig);
    updateConfig.reset(new UpdateConfig);
    slackConfig.reset(new SlackConfig);
    monitoringConfig.reset(new MonitoringConfig);
}

QString Config::getRawData() const
{
    return rawData;
}

void Config::setRawData(const QString& value)
{
    rawData = value;
}
