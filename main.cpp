#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlEngine>
#include <QQmlContext>
#include <QScopedPointer>

#include "config/ConfigController.h"
#include "core/AppController.h"


int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QGuiApplication app(argc, argv);
    QQmlApplicationEngine engine;

    QScopedPointer<ConfigController> configController(new ConfigController);
    engine.rootContext()->setContextProperty("configController", configController.data());

    QScopedPointer<AppController> appController(new AppController());
    engine.rootContext()->setContextProperty("appController", appController.data());
    appController.data()->setQmlContext(engine.rootContext());

    QObject::connect(appController.data(), SIGNAL(pendingSaveConfig()), configController.data(), SLOT(save()));
    QObject::connect(configController.data(), SIGNAL(configServiceReady(ConfigPtr)), appController.data(), SLOT(onConfigLoaded(ConfigPtr)));
    QObject::connect(configController.data(), SIGNAL(configServiceError()), appController.data(), SLOT(onConfigError()));

    qmlRegisterType<AppController>("com.app", 1, 0, "AppState");
    qmlRegisterType<ProcessService>("com.app", 1, 0, "ProcessState");

    engine.load(QUrl(QLatin1String("qrc:/qml/main.qml")));

    if (engine.rootObjects().isEmpty())
    {
        return -1;
    }

    // config load. entry point
    configController.data()->setLoadingMethod(ConfigLoader::CONFIG_LOAD_METHOD::LOCAL_FILE);
    configController.data()->load();

    return app.exec();
}
