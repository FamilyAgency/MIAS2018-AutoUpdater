#ifndef BASECOMPONENT_H
#define BASECOMPONENT_H

#include <QObject>
#include <QQmlContext>
#include "core/Types.h"
#include "config/Config.h"

class BaseComponent : public QObject
{
    Q_OBJECT
public:
    explicit BaseComponent(QObject *parent = nullptr);
    virtual ~BaseComponent();
    virtual void setQmlContext(QQmlContext* value);
    virtual QString getName() const;
    virtual void start() = 0;
    virtual void stop() = 0;
    virtual void setConfig(ConfigPtr value);

protected:
    QQmlContext* qmlContext;
    QString name = "";
    ConfigPtr config;
};

#endif // BASECOMPONENT_H
