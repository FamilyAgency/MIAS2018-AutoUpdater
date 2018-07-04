#ifndef BASESERVICE_H
#define BASESERVICE_H

#include <QObject>
#include <QQmlContext>
#include "config/Config.h"

class BaseService : public QObject
{
    Q_OBJECT
public:
    explicit BaseService(QObject *parent = nullptr);

    virtual void setConfig(ConfigPtr config);
    virtual void start() = 0;
    virtual void stop() = 0;
    virtual void setQmlContext(QQmlContext* qmlContext);
    virtual QString getName() const = 0;

protected:
    ConfigPtr config;
    QQmlContext* qmlContext;

signals:

public slots:
};

#endif // BASESERVICE_H
