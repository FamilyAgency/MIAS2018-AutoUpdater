#ifndef BASEMODULE_H
#define BASEMODULE_H

#include <QObject>
#include <QQmlContext>
#include "config/Config.h"

class BaseModule : public QObject
{
    Q_OBJECT
public:
    explicit BaseModule(QObject *parent = nullptr);

    virtual void setConfig(Config* config);
    virtual void start() = 0;
    virtual void stop() = 0;
    virtual void setQmlContext(QQmlContext* qmlContext);
    virtual QString getName() const = 0;

protected:
    Config* config;
    QQmlContext* qmlContext;

signals:

public slots:
};

#endif // BASEMODULE_H
