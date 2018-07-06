#ifndef SLACKCOMPONENT_H
#define SLACKCOMPONENT_H

#include <QObject>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include "components/BaseComponent.h"
#include "network/http/HTTPClient.h"

class SlackComponent : public BaseComponent
{
    Q_OBJECT
public:
    explicit SlackComponent(QObject *parent = nullptr);
    virtual ~SlackComponent();
    void sendMessage(const QString& msg, const QString& channel);
    virtual void setConfig(ConfigPtr value) override;

private:
   QSharedPointer<HTTPClient> httpClient;
   QSharedPointer<SlackConfig> slackConfig;

private slots:
   void httpRequestSuccessHandler(const QString& data);
   void httpRequestFailedHandler(const QString& data);

signals:
   void slackNotifyResponse(const QString& message);
};

#endif // SLACKCOMPONENT_H
