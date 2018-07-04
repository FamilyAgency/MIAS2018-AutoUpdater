#ifndef TYPES_H
#define TYPES_H

#include <QObject>
#include <QString>
#include <QDebug>
#include <QAbstractListModel>
#include <QList>
#include <QJsonObject>

enum class LogType
{
    Verbose,
    Warning,
    Error
};

struct MainConfig
{
private:
    Q_GADGET
    Q_PROPERTY(int version MEMBER version)
    Q_PROPERTY(QString configUpdateUrl MEMBER configUpdateUrl)
    Q_PROPERTY(bool needRemoteUpdate MEMBER needRemoteUpdate)
    Q_PROPERTY(int standId MEMBER standId)
    Q_PROPERTY(int appTypeId MEMBER appTypeId)

 public:
    int version;
    QString configUpdateUrl;
    bool needRemoteUpdate;
    int standId;
    int appTypeId;
};
Q_DECLARE_METATYPE(MainConfig)

struct ProcessConfig
{
private:
    Q_GADGET
    Q_PROPERTY(QString path MEMBER path)
    Q_PROPERTY(bool autorun MEMBER autorun)

public:
    QString path = "";
    bool autorun = false;
};
Q_DECLARE_METATYPE(ProcessConfig)

struct UpdateConfig
{
private:
    Q_GADGET
    Q_PROPERTY(QString folderCheck MEMBER folderCheck)
    Q_PROPERTY(QString lastUpdateDate MEMBER lastUpdateDate)
    Q_PROPERTY(int frequency MEMBER frequency)
    Q_PROPERTY(bool autocheck MEMBER autocheck)

public:
    QString folderCheck = "";
    QString lastUpdateDate = "";
    int frequency = 100000;
    bool autocheck = false;
};
Q_DECLARE_METATYPE(UpdateConfig)

#endif // TYPES_H
