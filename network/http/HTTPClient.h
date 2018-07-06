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
    virtual ~HTTPClient();
    bool getRequestStatus() const;
    void runGetRequest(const QString& url);
    void runPostRequest(const QNetworkRequest& request, const QByteArray& data);

signals:
    void httpRequestSuccess(const QString& data);
    void httpRequestFailed(const QString& data);

public slots:
    void httpRequestSuccessHandler(QNetworkReply*);
    void httpRequestErrorHandler(QNetworkReply::NetworkError);
    void sslErrorHandler(QNetworkReply*, const QList<QSslError> &errors);

private:
     QNetworkAccessManager *networkManager;
};

#endif // HTTPCLIENT_H
