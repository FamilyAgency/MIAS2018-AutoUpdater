#include "BaseComponent.h"

BaseComponent::BaseComponent(QObject *parent) : QObject(parent)
{

}

void BaseComponent::setQmlContext(QQmlContext* value)
{
    qmlContext = value;
}

QString BaseComponent::getName() const
{
    return name;
}

void BaseComponent::setConfig(ConfigPtr value)
{
    config = value;
}
