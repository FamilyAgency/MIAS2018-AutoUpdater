#include "SlackComponent.h"
#include <QHttpPart>
#include <QUrlQuery>
#include <QJsonObject>
#include <QJsonDocument>

SlackComponent::SlackComponent(QObject *parent) : BaseComponent(parent)
{
    networkManager = new QNetworkAccessManager(this);
    connect(networkManager, SIGNAL(finished(QNetworkReply*)), this, SLOT(httpRequestSuccessHandler(QNetworkReply*)));
}

SlackComponent::~SlackComponent()
{
    if(networkManager)
    {
        disconnect(networkManager, SIGNAL(finished(QNetworkReply*)), this, SLOT(httpRequestSuccessHandler(QNetworkReply*)));
        delete networkManager;
    }
}

void SlackComponent::setConfig(ConfigPtr value)
{
    BaseComponent::setConfig(value);
    slackConfig = value->slackConfig;
}

void SlackComponent::sendMessage(const QString& msg, const QString& channel)
{
    if(!slackConfig->enabled)
    {
        return;
    }

    QJsonObject recordObject;
    recordObject.insert("text", QJsonValue::fromVariant(msg));

    QJsonDocument doc(recordObject);
    QByteArray jsonString = doc.toJson();
    QByteArray postDataSize = QByteArray::number(jsonString.size());
    QUrl serviceURL(channel);
    QNetworkRequest request(serviceURL);

    request.setRawHeader("Content-Type", "application/json");
    request.setRawHeader("Content-Length", postDataSize);
    QNetworkReply* reply = networkManager->post(request, jsonString);
}

void SlackComponent::httpRequestSuccessHandler(QNetworkReply* reply)
{
    if (reply->error() != QNetworkReply::NoError )
    { 
        QString message = "Server error, "  + reply->errorString();
        emit slackNotifyResponse(message);
    }
    else
    {
        QByteArray ba = reply->readAll();
        QString s_data = QString::fromUtf8(ba);
        QString message = "Server ok: "  + s_data;
        emit slackNotifyResponse(message);
    }

    reply->deleteLater();
}

void SlackComponent::onRequestFailed()
{
    qDebug()<<"request failed, we tried several times((( ";
}


