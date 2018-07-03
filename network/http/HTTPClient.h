#ifndef HTTPCLIENT_H
#define HTTPCLIENT_H

#include <QObject>
#include <QNetworkRequest>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QSslError>

class HTTPClient : public QObject
{
    Q_OBJECT
public:
    explicit HTTPClient(QObject *parent = nullptr);
    bool getRequestStatus() const;
    void runRequest(const QString& URL);

signals:
    void httpRequestSuccess(const QString& data);
    void httpRequestFailed();

public slots:
    void httpRequestSuccessHandler(QNetworkReply*);
    void httpRequestErrorHandler(QNetworkReply::NetworkError);
    void sslErrorHandler(QNetworkReply*, const QList<QSslError> &errors);

private:
     QNetworkAccessManager *networkManager;
};

#endif // HTTPCLIENT_H
