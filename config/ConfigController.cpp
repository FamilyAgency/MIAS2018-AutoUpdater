#include "ConfigController.h"
#include <QFile>
#include <QDebug>
#include <QJsonDocument>
#include <QCoreApplication>
#include <QJsonObject>
#include <QJsonArray>
#include <QDir>


ConfigController::ConfigController()
{
    configLoader.reset(new ConfigLoader);
    configParser.reset(new ConfigParser);
    configWriter.reset(new ConfigWriter);

    defaultConfigLoadingMethod = ConfigLoader::CONFIG_LOAD_METHOD::LOCAL_FILE;
    saveRemote = true;

    currentConfigLoadingMethod = defaultConfigLoadingMethod;
    currentConfigPath = getConfigPath(defaultConfigLoadingMethod);
    qDebug() << "currentConfigPath "<<currentConfigPath;

    connect(configLoader.data(), SIGNAL(configLoaded(const QString&)), configParser.data(), SLOT(parse(const QString&)));
    connect(configLoader.data(), SIGNAL(configLoadingError()), this, SLOT(onConfigLoadingError()));
    connect(configParser.data(), SIGNAL(parseComplete(Config* )), this, SLOT(onConfigParsingComplete(Config* )));
}

QString ConfigController::getConfigPath(ConfigLoader::CONFIG_LOAD_METHOD method) const
{
    switch(method)
    {
    case ConfigLoader::CONFIG_LOAD_METHOD::RESOURCE_FILE:
        return  ":/resources/config.json";
    case ConfigLoader::CONFIG_LOAD_METHOD::LOCAL_FILE:
        return   QCoreApplication::applicationDirPath() + "/" + "config.json";
    }

    return "";
}

void ConfigController::setLoadingMethod(ConfigLoader::CONFIG_LOAD_METHOD loadingMethod)
{
    currentConfigLoadingMethod = loadingMethod;
    currentConfigPath = getConfigPath(currentConfigLoadingMethod);
}

void ConfigController::load()
{
    qDebug() << "starting config loading"<<currentConfigPath;
    configLoader->load(currentConfigLoadingMethod, currentConfigPath);
}

void ConfigController::onConfigParsingComplete(Config* configParsed)
{
    configData = configParsed;

    switch(currentConfigLoadingMethod)
    {
    case ConfigLoader::CONFIG_LOAD_METHOD::RESOURCE_FILE:
    case ConfigLoader::CONFIG_LOAD_METHOD::LOCAL_FILE:
        qDebug() << "ConfigLoader::CONFIG_LOAD_METHOD::LOCAL_FILE: "<<configData->configData.needRemoteUpdate;
        if(configData->configData.needRemoteUpdate)
        {
            qDebug() << "will load from remote";
            currentConfigLoadingMethod =  ConfigLoader::CONFIG_LOAD_METHOD::URL;
            currentConfigPath = configData->configData.configUpdateUrl;
            load();
        }
        else
        {
            serviceFinished(true);
        }
        break;

    case ConfigLoader::CONFIG_LOAD_METHOD::URL:
        if(saveRemote && configData->valid && defaultConfigLoadingMethod!= ConfigLoader::CONFIG_LOAD_METHOD::RESOURCE_FILE)
        {
            configWriter->save(configData, getConfigPath(ConfigLoader::CONFIG_LOAD_METHOD::LOCAL_FILE));
        }        
        serviceFinished(configData->valid);
        break;
    }
}

void ConfigController::onConfigLoadingError()
{
    switch(currentConfigLoadingMethod)
    {
    case ConfigLoader::CONFIG_LOAD_METHOD::RESOURCE_FILE:
    case ConfigLoader::CONFIG_LOAD_METHOD::LOCAL_FILE:
        serviceFinished(false);
        break;

    case ConfigLoader::CONFIG_LOAD_METHOD::URL:
        qDebug() << "load from url error";
        if(configData->valid)
        {
            qDebug() << "but config loaded from disk.. can run";
            serviceFinished(true);
        }
        else
        {
            qDebug() << "config loaded from disk invalid";
            serviceFinished(false);
        }
        break;
    }
}

void ConfigController::serviceFinished(bool success)
{
    if(success)
    {
        emit configServiceReady(configData);
    }
    else
    {
        emit configServiceError();
    }
}

void ConfigController::onUpdateConfigOfStartingApp(int id)
{
    configWriter->saveProcessConfigData(configData, id);
}

