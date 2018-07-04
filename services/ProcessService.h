#ifndef PROCESSSERVICE_H
#define PROCESSSERVICE_H

#include <QObject>
#include <QProcess>
#include "BaseService.h"

class ProcessService : public BaseService
{
    Q_OBJECT
    Q_PROPERTY(bool running READ running WRITE setRunning NOTIFY runningChanged)
    Q_PROPERTY(ProcessConfig processConfig READ processConfig WRITE setProcesConfig NOTIFY processConfigChanged)

public:
    explicit ProcessService(QObject *parent = nullptr);
    virtual ~ProcessService();

    Q_INVOKABLE void startApp();
    Q_INVOKABLE void stopApp();

    virtual void start() override;
    virtual void stop() override;
    virtual QString getName() const override;
    virtual void setQmlContext(QQmlContext* qmlContext) override;
    virtual void setConfig(ConfigPtr value) override;

    void setProcesConfig(const ProcessConfig& config);
    ProcessConfig processConfig() const;

    bool running() const;
    void setRunning(bool value);

private:
    ProcessConfig _processConfig;
    QProcess *process;   
    QString program;
    bool _running = false;

    QString findAppFullPath() const;

signals:
    void runningChanged();
    void processConfigChanged();
    void processStopped(int value);

private slots:
    void onReadyReadStandardError();
    void onProcessFinished(int value);
    void onProcessStarted();
    void onErrorOccurred(QProcess::ProcessError error);
};

#endif // PROCESSSERVICE_H
