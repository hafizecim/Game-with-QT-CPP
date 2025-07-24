#include "Controller.h"

// Controller sınıfının yapıcı fonksiyonu (constructor)
// Başlangıçta x ve y konumlarını belirler, hız ve sınırları tanımlar
Controller::Controller(QObject* parent)
    : m_x(1315 / 2 - 50),  // Başlangıç x konumu: ekranın yatay ortasında (örneğin 1315px genişlikte, 50px nesne ortalanır)
      m_y(685 - 50),       // Başlangıç y konumu: ekranın alt kısmına yakın (örneğin 685px yükseklikte, 50px yukarıdan)
      xSpeed(10),          // x yönünde her hareket için 10 piksel kayma hızı
      minX(0),             // x ekseninde minimum sınır (sol kenar)
      maxX(1315),          // x ekseninde maksimum sınır (sağ kenar)
      bottomY(685)         // y ekseninde maksimum sınır (aşağıya düşmesini engellemek için kullanılabilir)
{
    // parent: QObject hiyerarşisinde üst nesne olarak kullanılabilir
}
