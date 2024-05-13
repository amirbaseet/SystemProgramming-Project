# Sistem Programlama Projesi - Bahar 2024

## Proje Ekibi
- AMRO MOUSA ISMAIL BASEET (Öğrenci Numarası: G211210578)
- Lina Elsavadi (Öğrenci Numarası: G201210570)

## Proje Tanımı
Bu proje, bir giriş dosyasından komutlar okuyarak bu komutlara göre bir çıkış dosyası oluşturan bir C programı geliştirmeyi içermektedir. Program, proje talimatlarında belirtilen özel biçimlendirmeleri ve özel karakterleri işlemekle yükümlüdür. Ayrıca, verilen sayıda karakteri tekrar edecek şekilde çıkış dosyasında karakter yazma işlemi de gerçekleştirecektir. Bu, giriş dosyasında belirtilen talimatlara göre dinamik olarak gerçekleştirilecektir.


## Özellikler
- **Giriş/Çıkış İşleme:** Dosya giriş ve çıkışlarını yönetmek için `libfdr` kütüphanesi kullanılmaktadır.
- **Hata Yönetimi:** Giriş dosyasının doğru formatta olup olmadığını kontrol eden sağlam hata denetimi. Eğer format uygun değilse, program çökmeden kullanıcıyı uyarır.
- **Komut Satırı Entegrasyonu:** Kullanıcıya giriş ve çıkış dosya isimlerini komut satırı üzerinden belirtme imkanı tanır. İsim verilmezse, program isimleri sorar veya öntanımlı isimleri kullanır.

## Dosya Yapısı
- `*.h`: Fonksiyonlar ve makrolar için bildirimler içeren başlık dosyaları.
- `*.c`: Programın ana mantığının tanımlandığı uygulama dosyaları.
- `*.a`: Projede kullanılan önceden derlenmiş fonksiyonları içeren arşiv dosyaları.

## Derleme ve Çalıştırma
Projeyi derlemeden önce `libfdr` kütüphanesinin yüklü olduğundan emin olun.

### Projeyi Derleme
Projeyi derlemek için terminalde aşağıdaki komutu çalıştırın:
- **Dosya isimleri girmeden Derlemesi :** make
- **Giris Dosya isimi girerek Derlemesi:** make FILE1="txt/input.dat"
- **Giris ve Cikis Dosya isimi girerek Derlemesi:** make FILE1="txt/input.dat" FILE2="txt/output.dat"

Dosya isimleri verilmezse, program isimleri sorar veya öntanımlı isimleri kullanır.

## Örnek Giriş/Çıkış
- **Giriş Dosyası:** `txt/input.dat`
- **Çıkış Dosyası:** `txt/output.dat`
Örnek içerikler için projeye dahil edilen dosyalara bakınız.

## Ek Dokümantasyon
- Programın beklenen davranışını göstermek için örnek çalışmaların ekran görüntülerini içeren PDF dökümanı dahildir.

## Teşekkürler
Bu proje, [Sakarya] University 

