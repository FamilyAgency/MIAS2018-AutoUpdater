#ifndef UPDATESERVICEFOLDER_H
#define UPDATESERVICEFOLDER_H

#include <QObject>
#include "services/UpdaterService.h"

class UpdaterServiceFolder : public UpdaterService
{
    Q_OBJECT
public:
    explicit UpdaterServiceFolder(QObject *parent = nullptr);

     virtual void startUpdate() override;

protected:
    virtual void checkUpdate() override;
    virtual bool hasUpdate() override;

private:
    bool copyPath(QString sourceDir, QString destinationDir, bool overWriteDirectory);

};

#endif // UPDATESERVICEFOLDER_H
