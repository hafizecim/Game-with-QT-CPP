#include <QGuiApplication>             // Qt GUI uygulamaları için temel uygulama sınıfı
#include <QQmlApplicationEngine>       // QML arayüzünü yüklemek için kullanılan motor
#include <QQmlContext>                 // C++ nesnelerini QML'e bağlamak için gerekli sınıf
#include "Controller.h"                // Controller sınıfının başlık (header) dosyası

int main(int argc, char *argv[])
{
#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
#endif
    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;         // QML motoru, QML dosyasını yükleyip çalıştırır

    Controller control;                   // C++ tarafında Controller sınıfından bir nesne oluşturulur

    engine.rootContext()->setContextProperty("control", &control);
    // Oluşturulan 'control' nesnesi QML'e "control" adıyla bağlanır
    // Artık QML dosyası içinde bu nesneye erişilebilir (örneğin: control.x)

    const QUrl url(QStringLiteral("qrc:/main.qml"));
    QObject::connect(
        &engine,
        &QQmlApplicationEngine::objectCreated,
        &app,
        [url](QObject *obj, const QUrl &objUrl) {
            if (!obj && url == objUrl)
                QCoreApplication::exit(-1);
        },
        Qt::QueuedConnection);
    engine.load(url);

    return app.exec();
}
