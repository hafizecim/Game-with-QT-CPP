import QtQuick              // QML'in temel grafik bileşenlerini içe aktarır
import QtQuick.Window 2.15  // Window bileşenini ve pencere özelliklerini kullanmak için gerekli modül

// Uygulama penceresini tanımlar
Window {
    width: 1366             // Pencere genişliği
    height: 768             // Pencere yüksekliği yada istediğin uygun bir değer
    visible: true           // Uygulama başlatıldığında pencere görünür olacak
    title: qsTr("Hello World")  // Pencerenin başlığı

    // Kırmızı renkli hareketli kutu
    Rectangle {
        id: move1              // Nesneye referans için kimlik
        width: 50              // Genişlik
        height: 50             // Yükseklik
        color: "red"           // Renk

        //x ve y pozisyonları C++ tarafındaki Controller sınıfından alınır
        x: control.x           // x konumu Controller’dan alınır
        y: control.y           // y konumu Controller’dan alınır

        focus: true            // Bu nesne klavye girişlerini alabilir

        // Klavye tuşlarına basıldığında gerçekleşecek olaylar
        Keys.onPressed: (event) => {
            if (event.key === Qt.Key_Left) {
                control.moveLeft();    // Sol tuşa basılırsa C++ fonksiyonu ile sola kay
            }
            if (event.key === Qt.Key_Right) {
                control.moveRight();   // Sağ tuşa basılırsa C++ fonksiyonu ile sağa kay
            }
            if (event.key === Qt.Key_Up) {
                control.applyThrust();  // Yukarı tuşuna basıldığında thrust uygulanır
            }
            if (event.key === Qt.Key_Down) {
                move1.y += 10;         // Aşağı tuşuna basılırsa y konumunu artır (aşağı hareket)
            }
        }
    }
}
