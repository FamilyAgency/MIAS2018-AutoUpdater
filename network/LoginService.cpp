#include "LoginService.h"

LoginService::LoginService(QObject *parent) : QObject(parent)
{
    httpClient = new HTTPClient();
    connect(httpClient, SIGNAL(httpRequestSuccess(const QString&)), this, SLOT(httpRequestSuccessHandler(const QString&)));
    connect(httpClient, SIGNAL(httpRequestFailed()), this, SLOT(httpRequestFailedHandler()));
}

void LoginService::setConfig(Config* config)
{
   loginUrl = config->loginData.url;
}

void LoginService::login(const QString& login, const QString& password)
{
    emit startLogin();
    qDebug()<<"login url " << loginUrl;
    httpClient->runRequest(loginUrl + "?login=" + login +"&pass="+ password);
}

void LoginService::setLoginUrl(const QString& url)
{
    loginUrl = url;
}

void LoginService::httpRequestSuccessHandler(const QString& data)
{
    emit loginSuccess();

    return;//
    if(data == "fail")
    {
        emit loginFailed();
    }
    else if(data == "success")
    {
        emit loginSuccess();
    }
    qDebug()<<"LoginService RequestSuccessHandler" << data;
}

void LoginService::httpRequestFailedHandler()
{
    emit loginFailed();
    qDebug()<<"LoginService RequestFailed";

}
