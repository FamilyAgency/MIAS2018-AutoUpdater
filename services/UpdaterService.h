#ifndef UPDATERSERVICE_H
#define UPDATERSERVICE_H

#include <QObject>
#include "BaseService.h"

class UpdaterService : public BaseService
{
    Q_OBJECT
public:
    explicit UpdaterService(QObject *parent = nullptr);
    virtual void start() override;
    virtual void stop() override;
    virtual QString getName() const override;

    void startUpdate();
    bool hasUpdate() const;

signals:
    void pendingUpdate();
    void updateComplete();
    void updateError();
    void updateLoadingError();

public slots:
};

#endif // UPDATERSERVICE_H
