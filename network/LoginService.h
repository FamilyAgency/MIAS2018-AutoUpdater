#ifndef LOGINSERVICE_H
#define LOGINSERVICE_H

#include <QObject>
#include "http/HTTPClient.h"
#include "../config/Config.h"

class LoginService : public QObject
{
    Q_OBJECT
public:
    explicit LoginService(QObject *parent = nullptr);
    Q_INVOKABLE void login(const QString& login, const QString& password);
    void setLoginUrl(const QString& url);
    void setConfig(Config* config);

private:
    HTTPClient* httpClient;
    QString loginUrl;

private slots:
    void httpRequestSuccessHandler(const QString& data);
    void httpRequestFailedHandler();

signals:
    void startLogin();
    void loginSuccess();
    void loginFailed();
};

#endif // LOGINSERVICE_H
