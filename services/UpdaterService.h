#ifndef UPDATERSERVICE_H
#define UPDATERSERVICE_H

#include <QObject>
#include <QDateTime>
#include <QTimer>
#include "BaseService.h"

class UpdaterService : public BaseService
{
    Q_OBJECT

    Q_PROPERTY(int timeToUpdate READ timeToUpdate WRITE setTimeToUpdate NOTIFY timeToUpdateChanged)

public:
    explicit UpdaterService(QObject *parent = nullptr);
    virtual void start() override;
    virtual void stop() override;
    virtual QString getName() const override;
    virtual void setQmlContext(QQmlContext* qmlContext);

    void startUpdate();
    bool hasUpdate() const;

    int timeToUpdate() const;
    void setTimeToUpdate(int);

private:
    int startTime = 0;
    const int taskTimerMills = 10;
    const int timeCheck = 3000;
    QTimer* timer;
    int _timeToUpdate = 0;

signals:
    void pendingUpdate();
    void updateComplete();
    void updateError();
    void updateLoadingError();
    void timeToUpdateChanged();

private slots:
    void onUpdate();
};

#endif // UPDATERSERVICE_H
