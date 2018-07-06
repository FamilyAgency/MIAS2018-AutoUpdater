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
    void parseMainConfig(QSharedPointer<MainConfig> mainConfig, const QJsonObject& jsonObj);
    void parseProcessConfig(QSharedPointer<ProcessConfig> processConfig, const QJsonObject& jsonObj);
    void parseUpdateConfig(QSharedPointer<UpdateConfig> updateConfig, const QJsonObject& jsonObj);
    void parseSlackConfig(QSharedPointer<SlackConfig> slackConfig, const QJsonObject& jsonObj);
    void parseMonitoringConfig(QSharedPointer<MonitoringConfig> monitoringConfig, const QJsonObject& jsonObj);
    void parseLoggerConfig(QSharedPointer<LoggerConfig> loggerConfig, const QJsonObject& jsonObj);
};

#endif // CONFIGPARSER_H
