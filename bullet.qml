import QtQuick  // Qt Quick modülünü içe aktarır; temel grafik ve etkileşim bileşenleri sağlar

Rectangle
{
    id: bullet               // Mermi nesnesi: hareket eden küçük dikdörtgen
    width: 10                // Merminin genişliği 10 piksel
    height: 30               // Merminin yüksekliği 30 piksel
    color: "black"           // Mermi siyah renkte gösterilir

    // Mermi, move1 nesnesinin tam üstünde konumlanır
    anchors.bottom: move1.top

    // Mermi, yatay olarak move1 ile aynı hizada olur
    anchors.horizontalCenter: move1.horizontalCenter

    // NOT: Mermi tuşa başıldığında, her zaman move1'in tam üstünde görünecektir.
    // Bu, örneğin ateş etme efekti için mermi nesnesinin pozisyonunu sürekli güncellemek için önemlidir.
}
