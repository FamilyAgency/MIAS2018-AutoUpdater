#ifndef BASECOMPONENT_H
#define BASECOMPONENT_H

#include <QObject>
#include <QQmlContext>

class BaseComponent : public QObject
{
    Q_OBJECT
public:
    explicit BaseComponent(QObject *parent = nullptr);
    virtual void setQmlContext(QQmlContext* value);
    virtual QString getName() const;
    virtual void start(){}

protected:
    QQmlContext* qmlContext;
    QString name = "";

signals:

public slots:
};

#endif // BASECOMPONENT_H
