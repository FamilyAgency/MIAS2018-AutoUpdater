#ifndef CONFIGWRITER_H
#define CONFIGWRITER_H

#include <QObject>
#include "Config.h"

class ConfigWriter: public QObject
{
    Q_OBJECT

public:
    ConfigWriter();

    void save(ConfigPtr config, const QString& path);
    void saveProcessConfigData(ConfigPtr config, int processId);
};

#endif // CONFIGWRITER_H
