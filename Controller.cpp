#include "Controller.h"

// Controller sınıfının yapıcı fonksiyonu (constructor)
// Başlangıçta x ve y konumlarını 50, x yönündeki hareket hızını 10 olarak ayarlıyor
Controller::Controller(QObject* parent)
    : m_x(50),        // Başlangıç x konumu: 50 piksel
      m_y(50),        // Başlangıç y konumu: 50 piksel
      xSpeed(10)      // x yönünde her hareket için 10 piksel kayma hızı
{
    // İsteğe bağlı olarak parent nesnesi QObject hiyerarşisi için kullanılabilir
}
