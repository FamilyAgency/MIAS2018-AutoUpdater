#ifndef LOGGERSERVICE_H
#define LOGGERSERVICE_H


#include <QObject>
#include <QQmlContext>
#include "components/BaseComponent.h"
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

class LoggerComponent : public BaseComponent
{
    Q_OBJECT

public:
    LoggerComponent(QObject *parent = nullptr);
    virtual ~LoggerComponent();

    virtual void setQmlContext(QQmlContext* qmlContext) override;
    virtual void setConfig(ConfigPtr config) override;
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
    QString logFormat = "dd.MM.yyyy";

    void logTofile(const QString& message);

private slots:
    void onSlackNotifyResponse(const QString& message);
};

#endif // LOGGERSERVICE_H
