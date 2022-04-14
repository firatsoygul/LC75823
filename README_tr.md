# LC75823 lcd sürücü için Arduino kütüphanesi.

[English.](README.md)

Bu kütüphaneyi aynı zamanda CT6523, PT6523, LC75823, SC6523, RSM6523, LF6523, HXJ6523, LP75823, SL4816, SWE75823, ZL75823, TM75823, SJ75823, CS1685, ADS75823, AX75823, CS75823, LS75823, PM1725, PS75823, SC75823 sürücülerinde de kullanabilirsiniz.

> Bu kütüphaneyi oluştururken, eski bir kaset çaların ön paneli üzerinde bulunan ekranı kullandım. Büyük ihtimalle benim çalıştığım panelin aynısına sahip olmayacaksınız. Sizin sahibi olduğunuz lcd paneli, tamamen kendine özel alanlar içerecektir. Ancak yukarıdaki sürücülerin herhangi birini içerdiği sürece, segment ve sembol datalarını kendi kartınıza göre düzenleyerek, diğer lcd paneller için de kullanılabilirsiniz. Örnek olarak PT6523 sürücüsü kullanan başka bir lcd panel için düzenlenmiş halini, [bu sayfada](https://github.com/firatsoygul/PT6523) inceleyebilirsiniz. 

![image_1](https://raw.githubusercontent.com/firatsyg/LC75823/master/img/alphabet.jpg?raw=true)  

![image_1a](https://raw.githubusercontent.com/firatsyg/LC75823/master/img/2.jpg?raw=true)

## KURULUM

- Arduino taslak klasörünüzde bulunan `libraries/` klasörünün altında `LC75823` adında yeni bir klasör oluşturun(libraries klasörü henüz mevcut değilse siz oluşturun).
- Kütüphane dosyaları içinde bulunan `src/` ve `example/` klasörlerini, yeni oluşturduğunuz `LC75823/` klasörüne yerleştirin.

Arduino taslak klasörü, işletim sisteminize bağlı olarak aşağıdaki konumlarda bulunur(eğer değiştirmediyseniz).

- Linux için: `/home/<username>/Arduino/` veya `/home/<username>/sketchbook/`
- Windows için: `C:\Users\<username>\My Documents\arduino\`
- Mac için: `/Users/<username>/Documents/Arduino/`

Ayrıca Arduino IDE menüsünden `Dosya > Tercihler` penceresini açtığınızda, "Taslak Defteri Konumu" alanından da öğrenebilir-değiştirebilirsiniz.

Dosyaları yerleştirdikten sonra, açık olan bütün Arduino IDE'leri kapatın. Tekrar açtığınızda, IDE otomatik olarak kütüphanelerinizi tekrar tarayacak ve yeni eklediğiniz kütüphaneyi de listesine ekleyecektir. Bunu kontrol etmek için, Arduino IDE'nizi açın ve `Dosya > Örnekler` menüsü altında `LC75823` satırını arayın. Bu satır üzerine geldiğinizde, kullanıma hazır bazı örnekler göreceksiniz.

## BAĞLANTI

Bu kütüphane SPI bağlantısı için standart Arduino SPI kütüphanesini kullanır. Bu nedenle;

- Data hattını Arduino 11 nolu pine (veya ICSP soketi üzerindeki 4 nolu MOSI pinine),
- CLK'yı ise Arduino 13 nolu pine (veya ICSP soketi üzerindeki 3 nolu SCK pinine),
- FCE (ChipEnabled, SlaveSelect) girişini Arduino 10 nolu pine bağlamak gerekiyor.

Bu pinler Arduino Uno modeli için geçerli. Diğer Arduino modelleri için [bu sayfadaki tabloya](https://www.arduino.cc/en/Reference/SPI) bakabilirsiniz. FCE (ChipEnabled, SlaveSelect) girişini ise bütün modellerde Arduino 10 nolu pine bağlıyoruz. Veya `begin(<SlaveSelect pin>, <adres>)` fonksiyonundaki parametreyi başka bir pine ayarlayabilirsiniz. Bağlantı şeması görseldeki gibi olmalıdır.

![image_2](https://raw.githubusercontent.com/firatsyg/LC75823/master/img/baglanti.jpg?raw=true)

## KULLANIMI

Kütüphaneyi kendi projenizde kullanabilmek için, Arduino IDE menüsünde `Taslak > library ekle > LC75823` yolunu takip edebilirsiniz. Veya kendiniz `.ino` dosyanızın en üstüne aşağıdaki kodu ekleyin.

```C++
#include <LC75823.h>
```

Kütüphaneyi bu şekilde çalışmaya dahil ettikten sonra, kütüphanedeki `LC75823` sınıfından yeni bir nesne üretmeniz gerekiyor.

```C++
LC75823 lcd;
```

Artık oluşturduğunuz bu yeni `lcd` nesnesi ile, aşağıdaki fonksiyonları kullanabilirsiniz.

### void begin(int chipEnabledPin, int address)

Bu fonksiyon lcd'yi başlatır. Chip enable `(slaveSelect)` pin  numarasının ve sürücünün SPI adresinin parametre olarak girilmesi gerekiyor. Ayrıca `SPISettings()` ve `SPI.begin()` gibi standart Arduino SPI fonksiyonlarını içerir ve chip enable pinini `OUT` durumuna getirir. Bu işlemlerin ekrana yazdırma yapılmadan önce başlatılması gerektiği için, Arduino `setup()` fonksiyonu içinde tanımlanması gerekiyor.

```C++
void setup()
{
  lcd.begin(10, 130);
}
```

### void text(char text[])

Girilen metni sabit biçimde ekrana yazdırır. Yazdırılacak metin `char` türünde bir dizi değişkeni olarak girilebilir  veya doğrudan `""` karakterleri arasında yazılarak parametre olarak girilmelidir. Ekran aynı anda 8 karakteri gösterebildiği için, girilen metnin ilk 8 karakteri ekranda görünür.

> Kütüphane yalnızca [ASCII karakter tablosundaki](https://www.arduino.cc/en/Reference/ASCIIchart) 32 - 127 arası karakterleri destekler. Bunun dışındaki karakterler ekranda iki karakterlik boşluk olarak görünür.

```C++
void loop()
{
  char a[14]="MERHABA DUNYA";
  lcd.text(a);

  //veya

  lcd.text("MERHABA DUNYA");
}
```

### void sText(char text[])

Girilen metni ekran üzerinde sağdan sola doğru kaydırarak yazdırır. Yazdırılacak metin `char` tipinde bir dizi değişkeni olarak girilebilir  veya doğrudan `""` karakterleri arasında yazılarak parametre olarak girilmelidir. Bu yazım şeklinde ekranda gösterilen metnin bir karakter sayı sınırı bulunmaz.

> Kütüphane yalnızca [ASCII karakter tablosundaki](https://www.arduino.cc/en/Reference/ASCIIchart) 32 - 127 arası karakterleri destekler. Bunun dışındaki karakterler ekranda iki karakterlik boşluk olarak görünür.

```C++
void loop()
{
  char a[44]="ARDUINO LC75823 KUTUPHANESI. 01 TEMMUZ 2018";
  lcd.sText(a);

  //veya

  lcd.sText("ARDUINO LC75823 KUTUPHANESI. 01 TEMMUZ 2018");
}
```

> Metni taşıyan `char` dizisi tanımlanırken, dizisinin eleman sayısı metnin karakter sayısından 1 fazla olmalıdır. Eğer 12 harfli bir metin giriyorsanız, diziyi 13 elemanlı oluşturmalısınız. Böylece dizinin son elemanına `/0` karakteri otomatik olarak yerleştirilir. Aksi halde, sonlandırma elemanı olmayan bir dizi ekrana yazdırılırken, kendisinden sonra tanımlanmış ya da bellekte kendisinden sonraki adreslerde bulunan alakasız veriler de ekrana yazdırılır.

Bazı durumlarda, `char`, `int` gibi farklı veri tiplerinden oluşan birden fazla veriyi, aynı anda ekrana yazdırmanız gerekebilir. Böylesi durumlarda, `C++` fonksiyonlarından [sprintf()](http://www.cplusplus.com/reference/cstdio/sprintf/)'i kullanabilirsiniz. Aşağıdaki örnekte, bir `int` değişkenin değeri ile bazı `char` karakterler birleştirilerek, lcd nesnesinin `sText()` fonksiyonuna parametre olarak giriliyor.

```C++
void loop()
{
  int a = 4;
  int b = 8;
  char buffer[14];
  sprintf (buffer, "%d ARTI %d = %d", a, b, a+b);
  lcd.sText(buffer);
}
```

`Sprintf()` fonksiyonu `int` veri tipini desteklerken, `float` tipindeki değişkenleri desteklemiyor. Bu durumu aşmak için `dtostrf()` fonksiyonunu kullanabilirsiniz. Aşağıda, bir `float` değişkenin değeri, `dtostrf()` fonksiyonu ile başka bir `char` dizisine aktarılıyor. Bir sonraki adımda ise `sprintf()` fonksiyonunda başka bir `char` dizisiyle birleştiriliyor. Ve son olarak `sText()` fonksiyonu ile ekrana yazdırılıyor.

```C++
void loop()
{
  char ss[2];
  char scr[2];
  int val = 0;
  float volt;

  val = analogRead(0);
  volt = val * 0.00468;
  dtostrf(volt, 4, 2, ss);
  sprintf(scr, "%s V", ss);
  lcd.text(scr);
}
```

> Yukarıdaki örnek kodu içeren .ino dosyası: [`LC75823/examples/LC75823_voltage_level/LC75823_voltage_level.ino`](examples/LC75823_voltage_level/LC75823_voltage_level.ino)

### int textLoopCount()

`sText()` fonksiyonu ile soldan sağa kaydırılarak ekrana yazdırılan metnin, ekranda kaç defa döndüğü bilgisini `int` tipinde dışa  döndürür. Bir metnin görünürlüğünü, ekranda belirli sayıda tekrarladıktan sonra sonlandırmak istiyorsanız, bu fonksiyondan dönen değere göre işlem yapabilirsiniz. Aşağıdaki örnekte, girilen metin 3 defa ekranda döndükten sonra döngüden çıkılır ve bir sonraki
işleme geçilir.

```C++
void loop()
{
  for (int i = 0; lcd.textLoopCount() < 3; i++)
   {
    lcd.sText("BU METIN EKRANDA 3 DEFA DONECEK.);
   }
}
```

> Yukarıdaki örnek kodu içeren .ino dosyası: [`LC75823/examples/LC58823_text/LC75823_text.ino`](examples/LC75823_text/LC75823_text.ino)

### void symbol(enum Symbol symbolName, boolean status)

Bu fonksiyon ile ekran üzerinde bulunan sembolleri gösterebilir ve gizleyebilirsiniz. Lcd panel üzerindeki tüm sembollere karşılık gelen birer `enum` sabiti tanımlanmıştır. `Symbol` isimli bu `enum` sabitlerinden birini ve içereceği durumu (*`true` veya `1` = göster,  `false` veya `0` = gizle*) bu fonksiyona parametre olarak girerek, ilgili sembolün görünürlüğünü değiştirebilirsiniz.

```C++
void loop()
{
  // Sembol durum bilgisi true gönderilerek semboller gösteriliyor.
  boolean sts = true;
  lcd.symbol(POP, sts);
  lcd.symbol(X_BASS, sts);
  lcd.symbol(TEYP_ICON, sts);
  delay(1500);
  
  // Sembol durum bilgisi 0 gönderilerek semboller gizleniyor.
  byte bsts = 0;
  lcd.symbol(POP, bsts);
  lcd.symbol(X_BASS, bsts);
  lcd.symbol(TEYP_ICON, bsts);
}
```

> Yukarıdaki örnek kodu içeren .ino dosyası: [`LC75823/examples/LC75823_symbols/LC75823_symbols.ino`](examples/LC75823_symbols/LC75823_symbols.ino)

Tüm sembol sabitleri aşağıda verilmiştir.

```C++
  ST,
  MONO,
  LOC,
  CLAS,
  POP,
  ROCK,
  TEYP_ICON,
  CD_ICON,
  X_BASS,
  CHART_1,
  CHART_2,
  CHART_3,
  VOLUME_1,
  VOLUME_LEFT_2,
  VOLUME_LEFT_3,
  VOLUME_LEFT_4,
  VOLUME_LEFT_5,
  VOLUME_LEFT_6,
  VOLUME_LEFT_7,
  VOLUME_LEFT_8,
  VOLUME_RIGHT_2,
  VOLUME_RIGHT_3,
  VOLUME_RIGHT_4,
  VOLUME_RIGHT_5,
  VOLUME_RIGHT_6,
  VOLUME_RIGHT_7,
  VOLUME_RIGHT_8
```

### void volumeChart(int volumeChartNo, boolean status)

'Volume seviyesi' ve 'chart' gösterimi gibi, sıralı ve birbiri ile bağlantılı bazı sembollerin kontrolü için kullanılır. `symbol()` fonksiyonuyla da müdahale edilebilen `VOLUME_*` ve `CHART_*` sembollerinin durumu, bu fonksiyon ile sıralı `int` değerler girilerek değiştirilebilir. Böylece bu sembolleri bir döngü içinde sıralı işlemlerde kullanabilirsiniz.

```C++
void loop()
{
  // VOLUME_1 sembolünü göster.
  lcd.volumeChart(1, true);

  // VOLUME_LEFT_2 sembolünü göster.
  lcd.volumeChart(2, true);

  // VOLUME_LEFT_3 sembolünü göster.
  lcd.volumeChart(3, true);
}
```

Volume sembollerinin fonksiyon içindeki sıralaması aşağıda verilmiştir.

```C++
   1: VOLUME_1

   2: VOLUME_LEFT_2
   3: VOLUME_LEFT_3
   4: VOLUME_LEFT_4
   5: VOLUME_LEFT_5
   6: VOLUME_LEFT_6
   7: VOLUME_LEFT_7
   8: VOLUME_LEFT_8

   9: VOLUME_RIGHT_2
  10: VOLUME_RIGHT_3
  11: VOLUME_RIGHT_4
  12: VOLUME_RIGHT_5
  13: VOLUME_RIGHT_6
  14: VOLUME_RIGHT_7
  15: VOLUME_RIGHT_8

  16: CHART_1
  17: CHART_2
  18: CHART_3
```

### void volumeLeftLevel(int levelValue), void volumeRightLevel(int levelValue)

Volume seviyesini istenen konuma getirir. 1 nolu sembol ortak olmak üzere, birbirinden ayrı sol ve sağ yedişer, toplamda 15 bağımsız volume sembolü bulunuyor. Bu seviye sembollerini döngüye girmeden bir anda istenilen seviyeye getirmek için kullanılır. Örneğin sol seviyeyi 5. düzeye getirmek için `volumeLeftLevel(5)`, sağ seviyeyi 3. düzeye getirmek için de `volumeRightLevel(3)` komutunu kullanmak yeterli.

```C++
void loop()
{
  lcd.volumeLeftLevel(5);
  lcd.volumeRightLevel(3);
}
```

Seviye basamakları toplam 8 farklı segmentten oluşuyor. Varsayılan olarak en düşük seviye `0`, en yüksek seviye ise `8` kabul edilmiştir. Ancak bu değerleri `volumeStartValue()`, ve `volumeEndValue()` fonksiyonları ile düzenleyebilirsiniz.

### void volumeStartValue(int startValue), void volumeEndValue(int endValue)

Seviye aralığı olarak 8 birimin yetmediği durumlarda, bu fonksiyonlar ile başlangıç ve bitiş değerleri ayarlanabilir. Örneğin aşağıdaki örnekte, Arduino `A0` nolu analog pinine uygulanan voltajın (max. 5 v.) yaklaşık değeri, seviye simgeleri üzerinde gösterilmiştir. Arduino analog girişten gelen voltaj değerini 0 - 1023 arası bir değere çevirmektedir. Ancak bu değer standart seviye sınırı olan sekizi aştığı için, sekizin üzerindeki her veri, seviyeyi en sona taşır. Bu durumu düzeltmek için, alt ve üst seviye sınırlarını bu iki fonksiyonla bildirebilirsiniz.

Program boyunca bu ayarı değiştirme ihtiyacı duyulmuyorsa, `setup()` fonksiyonu içinde tanımlayınız.

```C++
void setup()
{
  lcd.begin(10, 130);
  lcd.volumeStartValue(0);
  lcd.volumeEndValue(1023);
  int val = 0;
}

void loop()
{
  val = analogRead(0);

  lcd.volumeLeftLevel(val);
  lcd.volumeRightLevel(val);
}
```

![image_3](https://raw.githubusercontent.com/firatsyg/LC75823/master/img/volt.jpg?raw=true)

> Yukarıdaki örnek kodu içeren .ino dosyası: [`LC75823/examples/LC75823_voltage_level/LC75823_voltage_level.ino`](examples/LC75823_voltage_level/LC75823_voltage_level.ino)

### void sChart(boolean chartValue)

Chart sembollerinin, dönme animasyonu için kullanılır. Fonksiyona `true` veya `1` değeri girildiği sürece, chart sembolleri üzerinde dönüş animasyonu oluşturur.

```C++
void loop()
{
  for (int j = 0; j <= 8; j++)
    {
        lcd.sChart(1);
    }
}
```

> Yukarıdaki örnek kodu içeren .ino dosyası: [`LC75823/examples/LC75823_symbols/LC75823_symbols.ino`](examples/LC75823_symbols/LC75823_symbols.ino)

### void speed(int textSpeed)

Ekrandaki animasyonların (metin kaydırma, seviye geçişleri, chart animasyonu vb.) hızını belirlemek için kullanılır. Uygulamanın herhangi bir noktasında kullanılabilir. `int` tipindeki parametre milisaniye cinsinden olmalıdır. Belirtilen süre animasyonun geçiş hızını belirler. Dolayısıyla süre ne kadar az ise, animasyonlar o kadar hızlı gösterilir. Hiç bir değer belirtilmemişse, varsayılan değer 300 milisaniye olarak uygulanır.

### void clear()

Ekranda o anda yazılı olan karakterleri siler. Metinler arası geçişlerde kullanıldığında, metinlerin iç içe geçme riskini engeller. Her yeni metni ekrana yazdırmadan önce kullanmanız gerekiyor.

### void reset()

`clear()` fonksiyonuna ek olarak, `textLoopCount()` ile tutulan metin döngü sayısını, ekrandaki tüm sembolleri, sol ve sağ seviye bilgilerini sıfırlar. Animasyon hızını başlangıç değeri olan 300 milisaniyeye ayarlar. Ekran güç tasarrufu (power saving) modunda ise açılacaktır. Ancak `volumeStartValue()` ve `volumeEndValue()` ile belirlenen seviye aralıklarını **değiştirmez**.

### void noDisplay()

Sürücü güç tasarrufu (power saving) moduna geçer. Sürücü içindeki osilatör duracağı ve segment hatlarındaki voltaj Vss değerine çekileceği için, ekran lcd bölümü kapanır. Ekranın batarya ile çalıştırılacağı durumlarda, belirli bir süre sonunda bu moda geçilebilir.

### void display()

Güç tasarrufu (power saving) modunda bulunan sürücüyü normal çalışma moduna geçirir.

![image_4](https://raw.githubusercontent.com/firatsyg/LC75823/master/img/full.JPG?raw=true)

![image_5](https://raw.githubusercontent.com/firatsyg/LC75823/master/img/IMG_0104.JPG?raw=true)

<a href="https://www.buymeacoffee.com/firatsoygul" target="_blank"><img src="https://cdn.buymeacoffee.com/buttons/v2/default-yellow.png" alt="Buy Me A Coffee" style="height: 60px !important;width: 217px !important;" ></a>
