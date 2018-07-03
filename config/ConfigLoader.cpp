#include "ConfigLoader.h"
#include <QDir>
#include <QDebug>

ConfigLoader::ConfigLoader()
{

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
       httpClient = new HTTPClient();
       connect(httpClient, SIGNAL(httpRequestSuccess(const QString&)), this, SLOT(httpRequestSuccessHandler(const QString&)));
       connect(httpClient, SIGNAL(httpRequestFailed()), this, SLOT(httpRequestFailedHandler()));
       qDebug()<<"config url " << path;
       httpClient->runRequest(path);
    }   
}

void ConfigLoader::httpRequestSuccessHandler(const QString& data)
{
     qDebug()<<"httpRequestSuccessHandler";
     emit configLoaded(data);
}

void ConfigLoader::httpRequestFailedHandler()
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
