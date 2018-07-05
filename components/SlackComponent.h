#ifndef SLACKCOMPONENT_H
#define SLACKCOMPONENT_H

#include <QObject>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include "components/BaseComponent.h"
#include "config/Config.h"
#include "core/Types.h"

class SlackComponent : public BaseComponent
{
    Q_OBJECT
public:
    explicit SlackComponent(QObject *parent = nullptr);
    virtual ~SlackComponent();
    void SlackComponent::sendMessage(const QString& msg, const QString& channel);

private:
   QNetworkAccessManager* networkManager;

private slots:
   void httpRequestSuccessHandler(QNetworkReply* reply);
   void onRequestFailed();
};

#endif // SLACKCOMPONENT_H
