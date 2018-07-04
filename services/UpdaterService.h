#ifndef UPDATERSERVICE_H
#define UPDATERSERVICE_H

#include <QObject>
#include <QDateTime>
#include <QTimer>
#include <QDir>
#include <QStringList>
#include "BaseService.h"

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

    Q_INVOKABLE void checkUpdate();

    virtual void start() override;
    virtual void stop() override;
    virtual QString getName() const override;
    virtual void setQmlContext(QQmlContext* qmlContext);
    virtual void setConfig(ConfigPtr value) override;

    virtual void loadUpdate(QStringList& fileList);

    void startUpdate();
    bool hasUpdate(QStringList& fileList);

    int timeToUpdate() const;
    void setTimeToUpdate(int);

    void setUpdateConfig(const UpdateConfig& config);
    UpdateConfig updateConfig() const;

    bool needUpdate() const;
    void setNeedUpdate(bool value);

private:
    UpdateConfig _updateConfig;
    int startTime = 0;
    const int taskTimerMills = 10;
    QTimer* timer;
    int _timeToUpdate = 0;
    bool _needUpdate = false;

    void recurseAddDir(const QDir& fromDir, QStringList& list);
    bool copyPath(QString sourceDir, QString destinationDir, bool overWriteDirectory);

signals:
    void pendingUpdate();
    void updateComplete();
    void updateError();
    void updateLoadingError();
    void timeToUpdateChanged();
    void updateConfigChanged();
    void needUpdateChanged();

private slots:
    void onUpdate();
    void onUpdateLoaded();
};

#endif // UPDATERSERVICE_H
