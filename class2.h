#ifndef CLASS2_H
#define CLASS2_H

#include <QObject>
#include <QDebug>

// class2 bir QObject türevi sınıftır ve bir slot fonksiyonu içerir
class class2 : public QObject
{
    Q_OBJECT

public:
    class2();              // Kurucu fonksiyon

public:
    void print()           // Slot olarak kullanılacak fonksiyon
    {
        qDebug() << "I have printed";  // Konsola yazı basar
    }
};

#endif // CLASS2_H
