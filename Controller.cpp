#include "Controller.h"

// -------------------- [ Controller Yapıcısı: Başlangıç Değerleri ve Timer Ayarı ] --------------------

// Controller sınıfının yapıcı fonksiyonu (constructor)
// Başlangıçta x ve y konumlarını belirler, hız ve sınırları tanımlar
Controller::Controller(QObject* parent)
    : m_x(1315 / 2 - 50),  // Başlangıç x konumu: ekranın ortası (1315px genişlikte, 50px nesne ortalanır)
    m_y(685 - 50),       // Başlangıç y konumu: ekranın alt kısmına yakın (örnek: 685px yükseklik - 50px)
    xSpeed(10),          // Her tuşla 10 piksel yatay kayma
    minX(0),             // x ekseninde minimum sınır (sol kenar)
    maxX(1315),          // x ekseninde maksimum sınır (sağ kenar)
    bottomY(685 - 50)    // y ekseninde maksimum sınır (nesne zeminden aşağı inmesin diye)
{
    // -------------------- [ Zamanlayıcı (QTimer) ile Fizik Güncelleyici Kurulumu ] --------------------

    // QTimer sinyali timeout olduğunda (her 16ms'de bir), updateState() fonksiyonu tetiklenir
    connect(&time, &QTimer::timeout, this, &Controller::updateState);

    // Zamanlayıcıyı başlat: 16ms aralıkla çalışacak şekilde ayarlandı (yaklaşık 60 FPS)
    time.start(16);

    // -------------------- [ /QTimer Kurulumu ] --------------------
}


// -------------------- [ Nesneyi Sola Hareket Ettirme Fonksiyonu ] --------------------
// Nesneyi sola hareket ettirir ve sol sınırı aşmasını engeller
void Controller::moveLeft()
{
    setX(m_x - xSpeed); // Nesneyi sola doğru xSpeed (10) kadar kaydır
    if(m_x < minX) // Eğer konum min sınırdan daha küçükse
    {
        setX(minX); // Nesneyi min sınır olan 0'a sabitle
    }
}
// -------------------- [ /moveLeft ] --------------------


// -------------------- [ Nesneyi Sağa Hareket Ettirme Fonksiyonu ] --------------------
// Nesneyi sağa hareket ettirir ve sağ sınırı aşmasını engeller
void Controller::moveRight()
{
    setX(m_x + xSpeed); // Nesneyi sağa doğru xSpeed (10) kadar kaydır
    if(m_x > maxX) // Eğer konum max sınırı aşarsa
    {
        setX(maxX); // Nesneyi max sınır olan 1366'ya sabitle
    }
}
// -------------------- [ /moveRight ] --------------------


// -------------------- [ Yukarı Thrust Uygulama Fonksiyonu ] --------------------
// Yukarı hareket için anlık thrust (itme) uygular
void Controller::applyThrust()
{
    ySpeed = maxThrust;  // ySpeed değerine anlık negatif hız atanır (örneğin -15)
    // Bu, bir sonraki updateState çağrısında nesnenin yukarı hareket etmesine neden olur.
    if(m_y < bottomY/1.5) // Nesne, belirlenen üst sınırın (bottomY'nin 1/1.5’i kadar yukarısı) üstüne çıktıysa
    {
        ySpeed = 0; // yukarı hareket durdurulur, böylece nesne ekrandan çıkmaz.
    }
}
// -------------------- [ /applyThrust ] --------------------


// -------------------- [ Yerçekimi & Thrust Güncelleyici Zamanlayıcı Slot ] --------------------
// Nesnenin düşme ve yukarı zıplama hareketlerini günceller; yerçekimi ve thrust etkisini uygular
void Controller::updateState()
{
    m_y += ySpeed;         // Y konumu mevcut ySpeed kadar değiştirilir (yukarı/şağı hareket)
    ySpeed += gravity;     // ySpeed değerine yerçekimi eklenir (her seferde biraz daha aşağı çeker)

    if (m_y > bottomY)     // Eğer nesne alt sınırdan aşağıya düşerse
    {
        m_y = bottomY;     // Y konumu alt sınır değeri olan bottomY'ye sabitlenir (örneğin zemin)
    }

    emit yChanged();       // y konumu değiştiği için QML'e değişiklik bildirimi gönderilir
}
// -------------------- [ /updateState ] --------------------


// -------------------- [ /Controller Yapıcısı ] --------------------




// --------------------------------------------------------------------------------------------------
// 🧠 Controller Sınıfı Mantığı:
// Bu sınıf, ekrandaki bir nesnenin (örneğin bir karakter veya araç) konumunu ve hareketini kontrol eder.
// - Başlangıçta konum, hız ve sınır değerleri tanımlanır.
// - QTimer ile her 16 milisaniyede bir updateState() fonksiyonu çağrılarak,
//   yerçekimi ve thrust (itme kuvveti) gibi fiziksel etkiler simüle edilir.
// - Bu yapı, 60 FPS'e yakın bir güncelleme sağlar ve oyun mekaniği oluşturmak için kullanılır.
// --------------------------------------------------------------------------------------------------
