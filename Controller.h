#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <QObject>

// Controller sınıfı, QML ile veri alışverişi yapabilen bir QObject türevidir.
// x ve y konumlarını yönetir ve değişimlerini sinyallerle bildirir.
class Controller : public QObject
{
    Q_OBJECT

    // QML'den erişilebilir özellikler tanımlanıyor.
    // 'x' ve 'y' özellikleri okunabilir (READ), yazılabilir (WRITE) ve değişim bildirilebilir (NOTIFY).
    Q_PROPERTY(double x READ x WRITE setX NOTIFY xChanged)
    Q_PROPERTY(double y READ y WRITE setY NOTIFY yChanged)

public:
    // Yapıcı fonksiyon: Controller nesnesi oluşturulurken çağrılır.
    // parent parametresi varsayılan olarak nullptr, QObject hiyerarşisine bağlanmak için kullanılabilir.
    Controller(QObject* parent = nullptr);

    // Getter fonksiyonu: x değerini döndürür
    double x()
    {
        return m_x;
    }

    // Getter fonksiyonu: y değerini döndürür
    double y()
    {
        return m_y;
    }

    // Setter fonksiyonu: x değerini günceller ve değişmişse xChanged sinyali gönderir
    void setX(double value)
    {
        if (m_x != value)
        {
            m_x = value;
            emit xChanged();  // QML tarafına x'in değiştiği bildirilir
        }
    }

    // Setter fonksiyonu: y değerini günceller ve değişmişse yChanged sinyali gönderir
    void setY(double value)
    {
        if (m_y != value)
        {
            m_y = value;
            emit yChanged();  // QML tarafına y'nin değiştiği bildirilir
        }
    }

    // QML'den çağrılabilir bir fonksiyon (Q_INVOKABLE)
    // x konumunu xSpeed kadar azaltarak sola hareket ettirir
    Q_INVOKABLE void moveLeft()
    {
        setX(m_x - xSpeed); // Nesneyi sola doğru xSpeed (10) kadar kaydır
        if(m_x < minX) // Eğer konum min sınırdan daha küçükse
        {
            setX(minX); // Nesneyi min sınır olan 0'a sabitle
        }
    }

    // QML'den çağrılabilir bir fonksiyon (Q_INVOKABLE)
    // x konumunu xSpeed kadar artırarak sağa hareket ettirir
    Q_INVOKABLE void moveRight()
    {
        setX(m_x + xSpeed); // Nesneyi sağa doğru xSpeed (10) kadar kaydır
        if(m_x > maxX) // Eğer konum max sınırı aşarsa
        {
            setX(maxX); // Nesneyi max sınır olan 1366'ya sabitle
        }
    }

signals:
    // x veya y değeri değiştiğinde QML tarafına bildirim için sinyaller
    void xChanged();
    void yChanged();

private:
    // x ve y koordinatları - dikdörtgenin konumu
    double m_x;
    double m_y;

    // x yönünde hareket hızı (her hareket komutunda bu kadar piksel kaydırılır)
    double xSpeed;

    double minX;
    double maxX;
    double bottomY;
};

#endif // CONTROLLER_H
