#ifndef STANDINFO_H
#define STANDINFO_H

#include <QObject>
#include <QQmlContext>
#include "config/Config.h"

class StandData : public QObject
{
    Q_OBJECT
    Q_PROPERTY(MainConfig config READ config WRITE setConfig NOTIFY configChanged)

public:
    explicit StandData(QObject *parent = nullptr);
    void setQmlContext(QQmlContext* value);

    void setConfig(const MainConfig& config);
    MainConfig config() const;

private:   
    QQmlContext* qmlContext;
    MainConfig _mainConfig;

signals:
    void configChanged();

};

#endif // STANDINFO_H
