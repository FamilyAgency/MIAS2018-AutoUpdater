#include "HTTPClient.h"
#include <QThread.h>

HTTPClient::HTTPClient(QObject *parent) : QObject(parent)
{
    networkManager = new QNetworkAccessManager(this);
    networkManager->setNetworkAccessible(QNetworkAccessManager::Accessible);
    networkManager->moveToThread(QThread::currentThread());

    connect(networkManager, SIGNAL(finished(QNetworkReply*)), this, SLOT(httpRequestSuccessHandler(QNetworkReply*)));
   // connect(networkManager, SIGNAL(error(QNetworkReply::NetworkError)), this, SLOT(httpRequestErrorHandler(QNetworkReply::NetworkError)));
    connect(networkManager, SIGNAL(sslErrors(QNetworkReply*, QList<QSslError>)), this, SLOT(sslErrorHandler(QNetworkReply*, QList<QSslError>)));
}

void HTTPClient::runRequest(const QString& URL)
{
    QNetworkRequest request = QNetworkRequest(QUrl(URL));
    //httpReply =
    networkManager->get(request);
}

void HTTPClient::httpRequestSuccessHandler(QNetworkReply* reply)
{
    if ( reply->error() != QNetworkReply::NoError )
    {
        qDebug() << "Request failed, " << reply->errorString();
        emit httpRequestFailed();
    }
    else
    {
        QByteArray ba = reply->readAll();
        emit httpRequestSuccess(QString::fromUtf8(ba));
    }
}

void HTTPClient::httpRequestErrorHandler(QNetworkReply::NetworkError data)
{

}

void HTTPClient::sslErrorHandler(QNetworkReply* reply,const QList<QSslError> &errors)
{
    foreach ( const QSslError &e, errors) {
        qDebug() << "SSL Error:" << e.errorString();
    }

    reply->ignoreSslErrors(errors);
    emit httpRequestFailed();
}
