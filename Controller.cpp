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

// -------------------- [ /Controller Yapıcısı ] --------------------




// --------------------------------------------------------------------------------------------------
// 🧠 Controller Sınıfı Mantığı:
// Bu sınıf, ekrandaki bir nesnenin (örneğin bir karakter veya araç) konumunu ve hareketini kontrol eder.
// - Başlangıçta konum, hız ve sınır değerleri tanımlanır.
// - QTimer ile her 16 milisaniyede bir updateState() fonksiyonu çağrılarak,
//   yerçekimi ve thrust (itme kuvveti) gibi fiziksel etkiler simüle edilir.
// - Bu yapı, 60 FPS'e yakın bir güncelleme sağlar ve oyun mekaniği oluşturmak için kullanılır.
// --------------------------------------------------------------------------------------------------
