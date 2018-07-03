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

    void load();

    QScopedPointer<ConfigLoader> configLoader;
    QScopedPointer<ConfigParser> configParser;
    QScopedPointer<ConfigWriter> configWriter;

    QString getConfigPath(ConfigLoader::CONFIG_LOAD_METHOD method) const;
    void serviceFinished(bool success);
    void setLoadingMethod(ConfigLoader::CONFIG_LOAD_METHOD loadingMethod);

private:
    ConfigLoader::CONFIG_LOAD_METHOD currentConfigLoadingMethod, defaultConfigLoadingMethod;
    QString currentConfigPath;
    bool saveRemote;
    Config* configData;

private slots:
     void onConfigParsingComplete(Config* configParsed);
     void onConfigLoadingError();

public slots:
     void onUpdateConfigOfStartingApp(int id);

signals:
     void configServiceReady(Config* configData);
     void configServiceError();
};

#endif // CONFIGCONTROLLER_H
