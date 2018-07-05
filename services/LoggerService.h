#ifndef LOGGERSERVICE_H
#define LOGGERSERVICE_H


#include <QObject>
#include <QQmlContext>
#include "BaseService.h"
#include "components/SlackComponent.h"
#include "config/Config.h"

enum class LogType
{
    Verbose,
    Warning,
    Error
};

enum class LogRemoteType
{
    None,
    Server,
    Slack,
};

class LoggerService : public BaseService
{
    Q_OBJECT
public:

    LoggerService(QObject *parent = nullptr);

    virtual void setConfig(ConfigPtr config) override;
    virtual void setQmlContext(QQmlContext* qmlContext) override;
    virtual void start() override;
    virtual void stop() override;
    virtual QString getName() const override;

    void log(const QString& message, LogType type, LogRemoteType remoteType, bool saveLocal = true);


private:
    QSharedPointer<SlackComponent> slackComponent;
    int standId;
};

#endif // LOGGERSERVICE_H
