#ifndef MONITORINGCOMPONENT_H
#define MONITORINGCOMPONENT_H

#include "components/BaseComponent.h"
#include <QObject>
#include <QTimer>
#include "config/Config.h"
#include "monitoring/MemoryChecker.h"
#include "services/LoggerService.h"

class MonitoringComponent : public BaseComponent
{
    Q_OBJECT
public:
    explicit MonitoringComponent(QObject *parent = nullptr);
    virtual ~MonitoringComponent();
    virtual void setConfig(ConfigPtr value) override;
    virtual void start() override;

private:
   QSharedPointer<MonitoringConfig> monitoringConfig;
   QTimer* timer;
   MemoryChecker memoryChecker;
   QSharedPointer<LoggerService> loggerService;

private slots:
    void onUpdate();
};

#endif // MONITORINGCOMPONENT_H
