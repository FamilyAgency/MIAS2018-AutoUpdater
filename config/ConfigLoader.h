#ifndef CONFIGLOADER_H
#define CONFIGLOADER_H

#include <QString>
#include <QByteArray>
#include <QObject>
#include "network/http/HTTPClient.h"

class ConfigLoader : public QObject
{
    Q_OBJECT

signals:
    void configLoaded(const QString& config);
    void configLoadingError();

public:
    enum class CONFIG_LOAD_METHOD
    {
        URL,
        LOCAL_FILE,
        RESOURCE_FILE
    };

    ConfigLoader();
    virtual ~ConfigLoader();

    void load(CONFIG_LOAD_METHOD method, const QString& path = "");
    QString getConfig() const;
    bool isValid() const;

private:   
    QSharedPointer<HTTPClient> httpClient;
    QString configContext = "";

private slots:
    void httpRequestSuccessHandler(const QString& data);
    void httpRequestFailedHandler(const QString&);
};

#endif // CONFIGLOADER_H
