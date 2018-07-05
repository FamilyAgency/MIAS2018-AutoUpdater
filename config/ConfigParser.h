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

    void parseConfigData(QSharedPointer<MainConfig> mainConfig, const QJsonObject& jsonObj);
    void parseProcessData(QSharedPointer<ProcessConfig> processConfig, const QJsonObject& jsonObj);
    void parseUpdateData(QSharedPointer<UpdateConfig> updateConfig, const QJsonObject& jsonObj);
};

#endif // CONFIGPARSER_H
