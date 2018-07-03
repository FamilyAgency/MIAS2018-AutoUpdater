#ifndef PROCESSSERVICE_H
#define PROCESSSERVICE_H

#include <QObject>
#include "BaseService.h"

class ProcessService : public BaseService
{
    Q_OBJECT
public:
    explicit ProcessService(QObject *parent = nullptr);
    virtual void start() override;
    virtual void stop() override;
    virtual QString getName() const override;

    void startApp();
    void stopApp();

signals:

public slots:
};

#endif // PROCESSSERVICE_H
