#ifndef CONFIG_H
#define CONFIG_H

#include <QVector.h>
#include <QString.h>
#include <QStringList.h>
#include <QObject.h>
#include <QDebug.h>
#include <core/Types.h>

typedef  QSharedPointer<class Config> ConfigPtr;

class Config
{
public:
    Config();
    bool valid = true;

    QSharedPointer<MainConfig> mainConfig;
    QSharedPointer<ProcessConfig> processConfig;
    QSharedPointer<UpdateConfig> updateConfig;
    QSharedPointer<SlackConfig> slackConfig;

    QString getRawData() const;
    void setRawData(const QString& value);

private:
    QString rawData;
};



#endif // CONFIG_H
