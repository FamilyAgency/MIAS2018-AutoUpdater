#ifndef CONFIG_H
#define CONFIG_H

#include <QVector.h>
#include <QString.h>
#include <QStringList.h>
#include <QObject.h>
#include <QSharedPointer>
#include <QMap>
#include <core/Types.h>

typedef  QSharedPointer<class Config> ConfigPtr;

struct MainConfig
{
private:
    Q_GADGET
    Q_PROPERTY(int version MEMBER version)
    Q_PROPERTY(QString configUpdateUrl MEMBER configUpdateUrl)
    Q_PROPERTY(bool needRemoteUpdate MEMBER needRemoteUpdate)
    Q_PROPERTY(int appId MEMBER appId)
    Q_PROPERTY(QString workingDirectory MEMBER workingDirectory)
    Q_PROPERTY(QString folderSeparator MEMBER folderSeparator)
    Q_PROPERTY(QString appName MEMBER appName)

 public:
    int version;
    QString configUpdateUrl;
    bool needRemoteUpdate;
    int appId;
    QString workingDirectory;
    QString folderSeparator = "\\";
    QString appName = "None";
};
Q_DECLARE_METATYPE(MainConfig)

struct ProcessConfig
{
private:
    Q_GADGET
    Q_PROPERTY(QString path MEMBER path)
    Q_PROPERTY(bool autorun MEMBER autorun)
    Q_PROPERTY(int startDelayMills MEMBER startDelayMills)

public:
    QString path = "";
    bool autorun = false;
    int startDelayMills = 1000;
};
Q_DECLARE_METATYPE(ProcessConfig)

struct UpdateConfig
{
private:
    Q_GADGET
    Q_PROPERTY(QString checkDirectory MEMBER checkDirectory)
    Q_PROPERTY(QString lastUpdateDate MEMBER lastUpdateDate)
    Q_PROPERTY(int millsCheck MEMBER millsCheck)
    Q_PROPERTY(bool autocheck MEMBER autocheck)
    Q_PROPERTY(QString patternCheck MEMBER patternCheck)
    Q_PROPERTY(QString releaseDirectory MEMBER releaseDirectory)
    Q_PROPERTY(QString tempDirectory MEMBER tempDirectory)
    Q_PROPERTY(QString oldDirectory MEMBER oldDirectory)
    Q_PROPERTY(bool runAppAfterUpdate MEMBER runAppAfterUpdate)
    Q_PROPERTY(bool autoupdate MEMBER autoupdate)

public:
    QString checkDirectory = "";
    QString lastUpdateDate = "";
    int millsCheck = 100000;
    bool autocheck = false;
    QString patternCheck = "";
    QString releaseDirectory = "";
    QString tempDirectory = "";
    QString oldDirectory = "";
    bool runAppAfterUpdate = false;
    bool autoupdate = false;
    QVector<QString> filesToCopy;
};
Q_DECLARE_METATYPE(UpdateConfig)

struct SlackAppConfig
{
private:
    Q_GADGET
    Q_PROPERTY(QString logChannel MEMBER logChannel)
    Q_PROPERTY(QString errorChannel MEMBER errorChannel)
    Q_PROPERTY(bool enabled MEMBER enabled)
    Q_PROPERTY(int appId MEMBER appId)

public:
    QString logChannel = "";
    QString errorChannel = "";
    bool enabled = false;
    int appId = 0;
};
Q_DECLARE_METATYPE(SlackAppConfig)


struct SlackFullConfig
{
    QMap<int, SlackAppConfig> slackMap;
};

struct MonitoringConfig
{
private:
    Q_GADGET
    Q_PROPERTY(int memoryCheckMills MEMBER memoryCheckMills)
    Q_PROPERTY(bool enabled MEMBER enabled)

public:
    int memoryCheckMills = 10000;
    bool enabled = false;
};
Q_DECLARE_METATYPE(MonitoringConfig)

struct LoggerConfig
{
private:
    Q_GADGET
    Q_PROPERTY(QString localPath MEMBER localPath)
    Q_PROPERTY(bool localEnabled MEMBER localEnabled)

public:
    QString localPath = "logs";
    bool localEnabled = false;
};
Q_DECLARE_METATYPE(LoggerConfig)

class Config
{
public:
    Config();
    virtual ~Config();
    bool valid = true;

    QSharedPointer<MainConfig> mainConfig;
    QSharedPointer<ProcessConfig> processConfig;
    QSharedPointer<UpdateConfig> updateConfig;
    QSharedPointer<SlackFullConfig> slackConfig;
    QSharedPointer<MonitoringConfig> monitoringConfig;
    QSharedPointer<LoggerConfig> loggerConfig;

    QString getRawData() const;
    void setRawData(const QString& value);

private:
    QString rawData;
};



#endif // CONFIG_H
