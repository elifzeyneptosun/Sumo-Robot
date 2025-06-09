# Sumo-Robot
Arduino tabanlı otonom sumo robot; çizgi ve mesafe sensörlerinden aldığı verilerle karar ağacı kullanarak saldırı, kaçınma ve savunma manevraları yapar. L298N motor sürücüsüyle yön kontrolü sağlar, çizgi algıladığında geri çekilir, rakip algıladığında hızlı saldırıya geçer.
# Çizgi Algılamalı Engel Kaçan Sumo Robotu

Bu proje, hem çizgi algılayarak ring dışına çıkmayı önleyen hem de mesafe sensörleri ile rakip algılayıp tepki veren bir sumo robot sistemidir. Arduino tabanlı bu robot, çizgi sensörleri ve ultrasonik mesafe sensörleri kullanarak çevresiyle etkileşim kurar. Motorlar, L298N motor sürücü üzerinden kontrol edilir.

## Özellikler

- 3 adet TCRT5000 kızılötesi sensör ile çizgi algılama
- 4 adet HC-SR04 ultrasonik mesafe sensörü ile 360° engel/rakip tespiti (ön, arka, sağ, sol)
- Engel ve rakip konumuna göre hareket stratejisi
- Ring dışına çıkmayı önlemek için otomatik geri çekilme ve dönüş
- L298N motor sürücü ile hassas motor kontrolü
- Hız ayarı ve yön tayini

## Donanım Gereksinimleri

- Arduino UNO (veya uyumlu kart)
- 3 adet TCRT5000 çizgi sensörü
- 4 adet HC-SR04 ultrasonik mesafe sensörü
- L298N motor sürücü kartı
- 2 adet DC motor
- 2 adet tekerlek + 1 adet denge tekeri
- Güç kaynağı (Lipo veya pil paketi)

## Bağlantı Şeması (Özet)

| Bileşen         | Arduino Pinleri      |
|----------------|----------------------|
| TCRT5000 (arka) | A2                   |
| TCRT5000 (sol)  | A3                   |
| TCRT5000 (sağ)  | A4                   |
| HC-SR04 (ön)    | Trig: 7, Echo: 6     |
| HC-SR04 (arka)  | Trig: 8, Echo: 9     |
| HC-SR04 (sağ)   | Trig: A0, Echo: A1   |
| HC-SR04 (sol)   | Trig: 12, Echo: 13   |
| Motor PWM Sol   | D10                  |
| Motor PWM Sağ   | D11                  |
| Motor yön sol   | D2 (geri), D3 (ileri)|
| Motor yön sağ   | D4 (ileri), D5 (geri)|

## Kullanım

1. Arduino IDE’yi açın ve gerekli kütüphaneler yüklü olduğundan emin olun (ekstra kütüphane gerektirmez).
2. Kod dosyasını açın ve Arduino kartınıza uygun portu seçin.
3. Kodunuzu Arduino’ya yükleyin.
4. Robotu ring alanına yerleştirin ve güç verin.
5. Robot çizgiye yaklaşırsa geri kaçar; engel algılarsa yön değiştirip ilerler.

## Davranış Mantığı

- **Çizgi Tespiti**: Eğer ön ya da arka çizgi algılanırsa robot geri hareket eder ve yön değiştirir.
- **Rakip/Engel Tespiti**: Ön, sağ, sol veya arka yönlerden biri 20 cm altında bir cisme yaklaşırsa buna uygun hareket yapılır.
- **Hiçbir şey algılanmazsa**: Robot dönüş ve ileri hareketlerle arama moduna geçer.

## Notlar

- `THRESHOLD` değeri çizgi algılama hassasiyetini belirler (ışık ortamına göre ayarlanabilir).
- `DISTANCE_THRESHOLD` değeri rakip algılama mesafesini belirler (genellikle 20–25 cm idealdir).
- Robotun doğru çalışması için sensörlerin açılarının ve yüksekliklerinin dikkatli ayarlanması önerilir.

