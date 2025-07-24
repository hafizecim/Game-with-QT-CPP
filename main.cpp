#include <QGuiApplication>             // Qt GUI uygulamaları için temel uygulama sınıfı
#include <QQmlApplicationEngine>       // QML arayüzünü yüklemek için kullanılan motor
#include <QQmlContext>                 // C++ nesnelerini QML'e bağlamak için gerekli sınıf
#include "Controller.h"                // Controller sınıfının başlık (header) dosyası
#include "class1.h"                    // class1 sinyal gönderen sınıf
#include "class2.h"                    // class2 slot'u içeren sınıf
#include "QObject"                     // QObject temel sınıfı, sinyal-slot mekanizması için gerekli


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


// -------------------- [ class1 & class2: Sinyal-Slot Bağlantısı ] --------------------

    // class1 ve class2 nesneleri oluşturuluyor
    class1 classOne;                   // Sinyal gönderen nesne
    class2 classTwo;                   // Slot (print fonksiyonu) içeren nesne

    // Sinyal-slot bağlantısı yapılır
    // classOne nesnesindeki printIt() sinyali tetiklendiğinde classTwo.print() fonksiyonu çalıştırılır
    QObject::connect(&classOne, &class1::printIt, &classTwo, &class2::print); //connect(sender, signal, receiver, slot)

    classOne.printIt();                // Sinyali elle tetikleyerek sonucu görebiliriz

// -------------------- [ /class1 & class2: Sinyal-Slot Bağlantısı ] --------------------


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

    // QML motoru yüklenir ve arayüz başlatılır.
    engine.load(url);
    return app.exec();
}
