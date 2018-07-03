#include "Config.h"

Config::Config()
{

}

QString Config::getRawData() const
{
    return rawData;
}

void Config::setRawData(const QString& value)
{
    rawData = value;
}
