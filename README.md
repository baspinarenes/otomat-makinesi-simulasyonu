# ilk-tiva-projem-Otomat-Makinesi

   Yaptığım ilk kart projesi ve aynı zamanda Github'a attığım ilk proje. Projede Tiva TM4C123GXL kartını kullandım.
   
   Devredeki butonlar sırasıyla: 25 Kurus, 50 Kurus, 1 TL, Su, Cay, Kahve, Çikolata, Bisküvi, Bitiş, Reset.
   
   Proje 3 kısımdan oluşuyor:
   
   -İlk kısımda para yükleme kısmı bulunuyor. İstediğimiz miktarda bozuk paraı butonlar yardımıyla atılıyor. Atım bittiğinde Bitiş düğmesine tıklanmalı.
   
   -Sonrasında ürünler yine butonlar yardımıyla seçiliyor VE Bitiş düğmesine ekleniyor. Eğer herhangi bir sıkıntı yoksa (para yetersiz vs.) son aşamaya geçiliyor.
   
   -1-4 arasında rastgele bir sayı üretiliyor ve sayı eğer 2 ye eşitse para sıkışma olasılığı gerçekleştiriliyor. Eğer sorun oluşmazsa para üstü en az miktarda bozuk para kullanarak alıcıya veriliyor. Bu sırada gerekli kasa işlemleri gerçekleştiriliyor.
   
   (Reset tuşu yapılan yanlış işlemlerde alıcıyı en başa , para atma kısmına, yönlendiriyor.)
   
   Devre şemasını ve proje kodlarını burada bulabilirsiniz.
