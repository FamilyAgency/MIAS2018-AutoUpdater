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
    virtual ~ConfigParser();

signals:
    void parseComplete(ConfigPtr config);
    void parseError();

public slots:
    void parse(const QString& configData);

private:
    ConfigPtr config;

    MainConfig parseConfigData(const QJsonObject& jsonObj);
    ProcessConfig parseProcessData(const QJsonObject& jsonObj);
    UpdateConfig parseUpdateData(const QJsonObject& jsonObj);
};

#endif // CONFIGPARSER_H
