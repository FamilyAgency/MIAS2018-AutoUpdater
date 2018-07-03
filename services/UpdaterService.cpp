#include "UpdaterService.h"

UpdaterService::UpdaterService(QObject *parent) : BaseService(parent)
{

}

void UpdaterService::start()
{

}

void UpdaterService::stop()
{

}

void UpdaterService::startUpdate()
{

}

bool UpdaterService::hasUpdate() const
{
    return false;
}

QString UpdaterService::getName() const
{
     return "UpdaterService";
}
