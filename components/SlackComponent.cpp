#include "SlackComponent.h"
#include <QHttpPart>
#include <QUrlQuery>
#include <QJsonObject>
#include <QJsonDocument>

SlackComponent::SlackComponent(QObject *parent) : BaseComponent(parent)
{
    name = "Slack";

    httpClient.reset(new HTTPClient());
    connect(httpClient.data(), SIGNAL(httpRequestSuccess(const QString&)), this, SLOT(httpRequestSuccessHandler(const QString&)));
    connect(httpClient.data(), SIGNAL(httpRequestFailed(const QString&)), this, SLOT(httpRequestFailedHandler(const QString&)));
}

SlackComponent::~SlackComponent()
{
    disconnect(httpClient.data(), SIGNAL(httpRequestSuccess(const QString&)), this, SLOT(httpRequestSuccessHandler(const QString&)));
    disconnect(httpClient.data(), SIGNAL(httpRequestFailed(const QString&)), this, SLOT(httpRequestFailedHandler(const QString&)));
}

void SlackComponent::start()
{

}

void SlackComponent::stop()
{

}

void SlackComponent::setConfig(ConfigPtr value)
{
    BaseComponent::setConfig(value);
    auto appId = value->mainConfig->appId;
    auto slackMap = value->slackConfig->slackMap;

    if(slackMap.contains(appId))
    {
        init = true;
        slackConfig = value->slackConfig->slackMap[appId];
    }
    else
    {
        init = false;
    }
}

void SlackComponent::sendMessage(const QString& msg, bool isError)
{
    if(!init || !slackConfig.enabled)
    {
        return;
    }

    QJsonObject recordObject;
    recordObject.insert("text", QJsonValue::fromVariant(msg));

    QJsonDocument doc(recordObject);
    QByteArray jsonString = doc.toJson();
    QByteArray postDataSize = QByteArray::number(jsonString.size());

    QString channel = isError ? slackConfig.errorChannel : slackConfig.logChannel;
    QUrl serviceURL(channel);

    QNetworkRequest request(serviceURL);
    request.setRawHeader("Content-Type", "application/json");
    request.setRawHeader("Content-Length", postDataSize);
    httpClient->runPostRequest(request, jsonString);
}

void SlackComponent::httpRequestSuccessHandler(const QString& data)
{
    QString message = "Server ok: "  + data;
    emit slackNotifyResponse(message);
}

void SlackComponent::httpRequestFailedHandler(const QString& data)
{
    QString message = "Server error: " + data;
    emit slackNotifyResponse(message);
}

