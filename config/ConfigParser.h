#ifndef CONFIGPARSER_H
#define CONFIGPARSER_H

#include <QObject>
#include <QString>
#include "Config.h"

class ConfigParser : public QObject
{
    Q_OBJECT

public:
    ConfigParser();

signals:
    void parseComplete(Config* );
    void parseError();

public slots:
    void parse(const QString& configData);

private:
    Config* config;

    MainConfig parseConfigData(const QJsonObject& jsonObj);
    RFIDConfig parseRFIDData(const QJsonObject& jsonObj);
    MindwaveConfig parseMindwaveData(const QJsonObject& jsonObj);
    ServerConfig parseServerData(const QJsonObject& jsonObj);
    SlackConfig parseSlackData(const QJsonObject& jsonObj);
};

#endif // CONFIGPARSER_H
