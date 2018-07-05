#ifndef PROCESSSERVICE_H
#define PROCESSSERVICE_H

#include <QObject>
#include <QProcess>
#include "BaseService.h"

class ProcessService : public BaseService
{
    Q_OBJECT
    Q_PROPERTY(ProcessState processState READ processState WRITE setProcessState NOTIFY processStateChanged)
    Q_PROPERTY(ProcessConfig processConfig READ processConfig WRITE setProcesConfig NOTIFY processConfigChanged)

public:
    enum class ProcessState
    {
       Stopped,
       PendingStart,
       Running
    };
    Q_ENUMS(ProcessState)

    explicit ProcessService(QObject *parent = nullptr);
    virtual ~ProcessService();

    Q_INVOKABLE void startApp();
    Q_INVOKABLE void stopApp();
    Q_INVOKABLE QString getProcessFullPath() const;

    virtual void start() override;
    virtual void stop() override;
    virtual QString getName() const override;
    virtual void setQmlContext(QQmlContext* qmlContext) override;
    virtual void setConfig(ConfigPtr value) override;

    void setProcesConfig(const ProcessConfig& config);
    ProcessConfig processConfig() const;

    ProcessState processState() const;
    void setProcessState(ProcessState value);

private:
    ProcessConfig _processConfig;
    QProcess *process;   
    QString program;
    ProcessState _processState = ProcessState::Stopped;

signals:
    void processStateChanged();
    void processConfigChanged();
    void processStopped(int value);

private slots:
    void onReadyReadStandardError();
    void onProcessFinished(int value);
    void onProcessStarted();
    void onErrorOccurred(QProcess::ProcessError error);

    void startUpWithDelay();
};

#endif // PROCESSSERVICE_H
