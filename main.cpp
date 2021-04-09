#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QQmlComponent>
#include "videoproducer.h"
#include "videomanager.h"

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QGuiApplication app(argc, argv);

    std::unique_ptr<VideoManager> videoManager = std::unique_ptr<VideoManager>(new VideoManager());
    QQmlApplicationEngine engine;
    engine.rootContext()->setContextProperty("videoManager", videoManager.get());
    qmlRegisterType<VideoProducer>("VideoProducer", 0, 1, "VideoProducer");

    const QUrl url(QStringLiteral("qrc:/main.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);
    engine.load(url);

    return app.exec();
}
