#ifndef SLACKCOMPONENT_H
#define SLACKCOMPONENT_H

#include <QObject>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include "components/BaseComponent.h"

class SlackComponent : public BaseComponent
{
    Q_OBJECT
public:
    explicit SlackComponent(QObject *parent = nullptr);
    virtual ~SlackComponent();
    void sendMessage(const QString& msg, const QString& channel);
    virtual void setConfig(ConfigPtr value) override;

private:
   QNetworkAccessManager* networkManager;
   QSharedPointer<SlackConfig> slackConfig;

private slots:
   void httpRequestSuccessHandler(QNetworkReply* reply);
   void onRequestFailed();
};

#endif // SLACKCOMPONENT_H
