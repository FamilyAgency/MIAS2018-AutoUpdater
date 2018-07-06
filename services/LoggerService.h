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
    virtual ~LoggerService();

    virtual void setConfig(ConfigPtr config) override;
    virtual void setQmlContext(QQmlContext* qmlContext) override;
    virtual void start() override;
    virtual void stop() override;
    virtual QString getName() const override;

    void log(const QString& message, LogType type, LogRemoteType remoteType, bool saveLocal = true);

    QString createSlackMessage(const QString& message) const;
    QString createLocalMessage(const QString& message) const;
    QString getLocalLogAbsoluteFilePath() const;
    QString getLocalLogDirPath() const;

private:
    QSharedPointer<SlackComponent> slackComponent;
    int appId = 0;
    QString appName = "None";

    void logTofile(const QString& message);

private slots:
    void onSlackNotifyResponse(const QString& message);
};

#endif // LOGGERSERVICE_H
