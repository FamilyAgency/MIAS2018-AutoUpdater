#ifndef APPCOPCONTROLLER_H
#define APPCOPCONTROLLER_H

#include <QQmlContext>
#include <QObject>
#include <QList>

#include "StandData.h"
#include "config/Config.h"
#include "services/ProcessService.h"
#include "services/UpdaterService.h"
#include "Types.h"

class AppController : public QObject
{
    Q_OBJECT

public:
    enum class AppState
    {
       Idle,
       Loading,
       Updating
    };
    Q_ENUMS(AppState)

    AppController(QObject *parent = nullptr);

public:
    void setQmlContext(QQmlContext* qmlContext);

    Q_INVOKABLE void start();

private:
    StandData* standData;  
    ProcessService* processService = nullptr;
    UpdaterService* updaterService = nullptr;
    Config* config = nullptr;

public slots:
    void onConfigLoaded(Config* config);
    void onConfigError();

private slots:
    void onPendingUpdate();
    void onUpdateComplete();
    void onUpdateError();
    void onUpdateLoadingError();
};

#endif // APPCOPCONTROLLER_H
