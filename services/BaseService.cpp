#include "BaseService.h"

BaseService::BaseService(QObject *parent) : QObject(parent)
{

}

void BaseService::setConfig(ConfigPtr value)
{
    config = value;
}

void BaseService::setQmlContext(QQmlContext* value)
{
    qmlContext = value;
}




