#ifndef CONFIGCONTROLLER_H
#define CONFIGCONTROLLER_H

#include <QObject>
#include <QVector>
#include "core/Types.h"
#include "config/ConfigLoader.h"
#include "config/ConfigParser.h"
#include "config/ConfigWriter.h"
#include "config/Config.h"

class ConfigController : public QObject
{
    Q_OBJECT

public:
    ConfigController(); 
    virtual ~ConfigController();
    void load();

    QString getConfigPath(ConfigLoader::CONFIG_LOAD_METHOD method) const;
    void serviceFinished(bool success);
    void setLoadingMethod(ConfigLoader::CONFIG_LOAD_METHOD loadingMethod);

private:
    QSharedPointer<ConfigLoader> configLoader;
    QSharedPointer<ConfigParser> configParser;
    QSharedPointer<ConfigWriter> configWriter;
    ConfigLoader::CONFIG_LOAD_METHOD currentConfigLoadingMethod;
    ConfigLoader::CONFIG_LOAD_METHOD defaultConfigLoadingMethod;

    QString currentConfigPath;
    bool saveRemote;
    ConfigPtr config;

private slots:
     void onConfigParsingComplete(ConfigPtr configParsed);
     void onConfigLoadingError();

public slots:
     void save();

signals:
     void configServiceReady(ConfigPtr config);
     void configServiceError();
};

#endif // CONFIGCONTROLLER_H
