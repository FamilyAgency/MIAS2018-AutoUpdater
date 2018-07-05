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
    Q_PROPERTY(QString workingDirectory MEMBER workingDirectory)

 public:
    int version;
    QString configUpdateUrl;
    bool needRemoteUpdate;
    int standId;
    QString workingDirectory;
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
    Q_PROPERTY(QString checkDirectory MEMBER checkDirectory)
    Q_PROPERTY(QString lastUpdateDate MEMBER lastUpdateDate)
    Q_PROPERTY(int millsCheck MEMBER millsCheck)
    Q_PROPERTY(bool autocheck MEMBER autocheck)
    Q_PROPERTY(QString patternCheck MEMBER patternCheck)
    Q_PROPERTY(QString releaseDirectory MEMBER releaseDirectory)
    Q_PROPERTY(QString tempDirectory MEMBER tempDirectory)
    Q_PROPERTY(QString oldDirectory MEMBER oldDirectory)
    Q_PROPERTY(QString folderSeparator MEMBER folderSeparator)

public:
    QString checkDirectory = "";
    QString lastUpdateDate = "";
    int millsCheck = 100000;
    bool autocheck = false;
    QString patternCheck = "";
    QString releaseDirectory = "";
    QString tempDirectory = "";
    QString oldDirectory = "";
    QString folderSeparator = "";
};
Q_DECLARE_METATYPE(UpdateConfig)

#endif // TYPES_H
