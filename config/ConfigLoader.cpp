#include "ConfigLoader.h"
#include <QDir>
#include <QDebug>

ConfigLoader::ConfigLoader()
{
    httpClient.reset(new HTTPClient());
    connect(httpClient.data(), SIGNAL(httpRequestSuccess(const QString&)), this, SLOT(httpRequestSuccessHandler(const QString&)));
    connect(httpClient.data(), SIGNAL(httpRequestFailed(const QString&)), this, SLOT(httpRequestFailedHandler(const QString&)));
}

ConfigLoader::~ConfigLoader()
{
    disconnect(httpClient.data(), SIGNAL(httpRequestSuccess(const QString&)), this, SLOT(httpRequestSuccessHandler(const QString&)));
    disconnect(httpClient.data(), SIGNAL(httpRequestFailed(const QString&)), this, SLOT(httpRequestFailedHandler(const QString&)));
}

void ConfigLoader::load(CONFIG_LOAD_METHOD method, const QString& path)
{
    if(method == CONFIG_LOAD_METHOD::LOCAL_FILE ||
            method == CONFIG_LOAD_METHOD::RESOURCE_FILE)
    {
        QFile file(path);

        if(file.open(QIODevice::ReadOnly | QIODevice::Text))
        {
            configContext = file.readAll();
            emit configLoaded(configContext);
        }
        else
        {
            qDebug()<<"config read error";
            emit configLoadingError();
            //todo error
        }
    }
    else if(method == CONFIG_LOAD_METHOD::URL)
    {
        qDebug()<<"config url " << path;
        httpClient->runGetRequest(path);
    }
}

void ConfigLoader::httpRequestSuccessHandler(const QString& data)
{
    qDebug()<<"httpRequestSuccessHandler";
    emit configLoaded(data);
}

void ConfigLoader::httpRequestFailedHandler(const QString& error)
{
    qDebug()<<"httpRequestFailed";
    configLoadingError();
}

QString ConfigLoader::getConfig() const
{
    return configContext;
}

bool ConfigLoader::isValid() const
{
    return configContext.length() > 0;
}
