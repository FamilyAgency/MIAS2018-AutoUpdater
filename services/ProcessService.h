#ifndef PROCESSSERVICE_H
#define PROCESSSERVICE_H

#include <QObject>
#include <QProcess>
#include "BaseService.h"

class ProcessService : public BaseService
{
    Q_OBJECT
public:
    explicit ProcessService(QObject *parent = nullptr);
    virtual void start() override;
    virtual void stop() override;
    virtual QString getName() const override;
    virtual void setQmlContext(QQmlContext* qmlContext);

    Q_PROPERTY(bool running READ running WRITE setRunning NOTIFY runningChanged)

    Q_INVOKABLE void startApp();
    Q_INVOKABLE void stopApp();

    bool running() const;
    void setRunning(bool value);

private:
    QProcess *process;
    QStringList args;
    QString program;
    bool _running = false;

signals:
    void runningChanged();
    void processStopped(int value);

private slots:

    void onReadyReadStandardError();
    void onProcessFinished(int value);
    void onProcessStarted();
    void onErrorOccurred(QProcess::ProcessError error);
};

#endif // PROCESSSERVICE_H
