#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QQmlComponent>
#include "videoproducer.h"
#include "camera.h"

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QGuiApplication app(argc, argv);

    std::shared_ptr<VideoManager> videoManager = std::make_shared<VideoManager>();
    QQmlApplicationEngine engine;
    engine.rootContext()->setContextProperty("videoManager", videoManager.get());
    qmlRegisterType<VideoProducer>("VideoProducer", 0, 1, "VideoProducer");


    Camera *camera_thread = new Camera;
    camera_thread->setVideoManager(videoManager.get());
    QObject::connect(camera_thread, &Camera::finished, camera_thread, &QObject::deleteLater);

    camera_thread->start();

    const QUrl url(QStringLiteral("qrc:/main.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);
    engine.load(url);

    return app.exec();
}
