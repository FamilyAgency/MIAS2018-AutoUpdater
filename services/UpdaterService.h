#ifndef UPDATERSERVICE_H
#define UPDATERSERVICE_H

#include <QObject>
#include <QDateTime>
#include <QTimer>
#include <QDir>
#include <QStringList>
#include "BaseService.h"
#include "components/LoggerComponent.h"

class UpdaterService : public BaseService
{
    Q_OBJECT

    Q_PROPERTY(int timeToUpdate READ timeToUpdate WRITE setTimeToUpdate NOTIFY timeToUpdateChanged)
    Q_PROPERTY(UpdateConfig updateConfig READ updateConfig WRITE setUpdateConfig NOTIFY updateConfigChanged)
    Q_PROPERTY(bool needUpdate READ needUpdate WRITE setNeedUpdate NOTIFY needUpdateChanged)

public:
    explicit UpdaterService(QObject *parent = nullptr);
    virtual ~UpdaterService();

    enum class UpdateState
    {
       Idle,
       Loading,
       ChangingVersion
    };
    Q_ENUMS(UpdateState)

    Q_INVOKABLE void autoCheckChanged(bool value);
    Q_INVOKABLE void forceCheckUpdate();
    Q_INVOKABLE void forceStartUpdate();

    virtual void start() override;
    virtual void stop() override;
    virtual QString getName() const override;
    virtual void setQmlContext(QQmlContext* qmlContext);
    virtual void setConfig(ConfigPtr value) override;

    bool hasUpdate(QDir& newBuildDir);

    int timeToUpdate() const;
    void setTimeToUpdate(int);

    void setUpdateConfig(const UpdateConfig& config);
    UpdateConfig updateConfig() const;

    bool needUpdate() const;
    void setNeedUpdate(bool value);
    virtual void startUpdate() = 0;

protected:
    QTimer* timer;
    QDir newBuildDir = "";
    int newBuildVersion = 0;
    UpdateConfig _updateConfig;
    QSharedPointer<LoggerComponent> loggerComponent;

    virtual void checkUpdate() = 0;
    virtual bool hasUpdate() = 0;

private:
    int startTime = 0;
    const int taskTimerMills = 10;    
    int _timeToUpdate = 0;
    bool _needUpdate = false;

   bool copyPath(QString sourceDir, QString destinationDir, bool overWriteDirectory);
   void resetTimer();

signals:
    void pendingUpdate();
    void updateComplete(bool runApp, int newBuildVersion);
    void updateError();
    void updateLoadingError();
    void timeToUpdateChanged();
    void updateConfigChanged();
    void needUpdateChanged();
    void updateCheckingComplete(bool);

private slots:
    void onUpdate();
    void onUpdateCheckingComplete(bool);
    void onUpdateLoaded();
};

#endif // UPDATERSERVICE_H
