#ifndef LOGGERSERVICE_H
#define LOGGERSERVICE_H


#include <QObject>
#include <QQmlContext>
#include "BaseService.h"
//#include "components/SlackComponent.h"
#include "config/Config.h"


class LoggerService : public BaseService
{
    Q_OBJECT
public:
    enum class RemoteType
    {
        Server,
        Slack,
    };

    LoggerService(QObject *parent = nullptr);

    virtual void setConfig(Config* config) override;
    virtual void setQmlContext(QQmlContext* qmlContext) override;
    virtual void start() override;
    virtual void stop() override;
    virtual QString getName() const override;

    void log(const QString& message, LogType type, RemoteType remoteType, bool saveLocal = true);
   // void setSlackComponent(SlackComponent* component);

private:
    //SlackComponent* slackComponent;
    int standId;
};

#endif // LOGGERSERVICE_H
