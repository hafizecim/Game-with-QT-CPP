/*
 ✳️ Açıklama Özeti:
 - class1: Bir sinyal (signal) yayınlar.
 - class2: Bu sinyale cevap verecek bir fonksiyon (print()) içerir.
 - QObject::connect: Sinyal ve slot bağlantısını kurar. (main.cpp)
 - classOne.printIt();: Sinyali manuel tetikler. (main.cpp)
 - QML motoru yüklenir ve arayüz başlatılır. --> engine.load(url); return app.exec();
*/

#ifndef CLASS1_H
#define CLASS1_H

#include <QObject>

// class1 sinyal gönderen bir QObject türevi sınıftır
class class1 : public QObject
{
    Q_OBJECT

public:
    class1();              // Kurucu fonksiyon

signals:
    void printIt();        // Dış dünyaya sinyal gönderen fonksiyon (parametresiz)
};

#endif // CLASS1_H
