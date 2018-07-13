/*
  LC75823 Library for Arduino.
  Created by Fırat SOYGÜL, 20 Aralık 2017
  GNU General Public License v3.0
  (https://github.com/firatsoygul/LC75823/blob/master/LICENSE)
*/

#include "LC75823.h"
#include <SPI.h>
#include "character.h"

LC75823::LC75823() {

}

/*
* Function Name: begin
 * Description : Sürücünün adres ve slaveSelect pin bilgilerini alır, SPI ayarını yapar ve başlatır.
 * Input : int chipEnabledPin(sürücünün slaveSelect pininin bağlı olduğu pin no), 
 *         int address(sürücünün adresi).
 * Output : None
 */
void LC75823::begin(int chipEnabledPin, int address) {
  _chipEnabledPin = chipEnabledPin;
  _address = address;
  pinMode(_chipEnabledPin, OUTPUT);
  SPISettings(38000, MSBFIRST, SPI_MODE0);
  SPI.begin();
  //_setSymbol();
}

/*
* Function Name: textSize
 * Description : Lcd'ye gönderilen metnin karakter uzunluğunu hesaplar ve _textLenght global değişkenine girer. 
 * Input : char array
 * Output : None
 */
void LC75823::_textSize(char text[]) {
  _textLenght = 0;
  while (text[_textLenght] != '\0') {
    _textLenght++;
  }
}

/*
* Function Name: speed
 * Description : Kullanıcının lcd animasyon hızını girebilmesini sağlar.  
 * Input : int
 * Output : None
 */
void LC75823::speed(int textSpeed) { _textSpeed = textSpeed; }

/*
* Function Name: clear
 * Description : Karakter datalarını taşıyan _container dizisini, metnin ekrandaki dönüş sayısını tutan _loopNumber int değişkenini ve 
 *               animasyon sayısını tutan _sScroll int değişkenlerini sıfırlar ve ekrana boş bir container basar.
 *               (Sadece karakterleri ekrandan siler, semboller silinmez.)
 * Input : None
 * Output : None
 */
void LC75823::clear() {
  memset(_container, 0, _containerSize);
  memset(_screen, 0, 15);
  // memset(_symbol, 0, 4); // Sembolleri silmek için.
  _sScroll = 0;
  _loopNumber = 0;
  _print(_address, _screen, _symbols);
}

/*
* Function Name: reset
 * Description : Ekrana gönderilen dataları taşıyan tüm değişkenler ve döngü değişkenleri sıfırlanır.
 *               (Karakterler ve semboller dahil.)
 * Input : None
 * Output : None
 */
void LC75823::reset() {
  memset(_screen, 0, 15);
  memset(_container, 0, _containerSize);
  memset(_symbols, 0, 5);
  _iconSt = false;
  _iconRock = false;
  _sScroll = 0;
  _tScroll = 0;
  _loopNumber = 0;
  _textLenght = 0;
  _textSpeed = 300;
  _volumeLeftLevel = 0;
  _volumeRightLevel = 0;
  _print(_address, _screen, _symbols);
}

/*
* Function Name: display
 * Description : LCD POWER SAVING(BU DATA) mode is turn on with 0. 
 * Input : None
 * Output : None
 */
void LC75823::display() {
  bitWrite(_symbols[4], 1, 0);
  _print(_address, _screen, _symbols);
}

/*
* Function Name: noDisplay
 * Description : LCD POWER SAVING(BU DATA) mode is turn on with 1. 
 * Input : None
 * Output : None
 */
void LC75823::noDisplay() {
  bitWrite(_symbols[4], 1, 1);
  _print(_address, _screen, _symbols);
}

/*
* Function Name: volumeStartValue
 * Description : Lcd volume göstergelerine yapılacak girişin, başlangıç değerini belirler (Default = 0)
 * Input : int startValue
 * Output : None
 */
void LC75823::volumeStartValue(int startValue){
  _volumeStartValue = startValue;
}

/*
* Function Name: volumeEndValue
 * Description : Lcd volume göstergelerine yapılacak girişin, bitiş değerini belirler. (Default = 8)
 * Input : int endValue
 * Output : None
 */
void LC75823::volumeEndValue(int endValue){
  _volumeEndValue = endValue;
}

/*
* Function Name: volumeLeftLevel
 * Description : Lcd sol volume göstergelerinin değerini belirler. Değer aralığı volumeStartValue ve volumeEndValue metodları ile belirlenebilir.
 * Input : int levelValue (Sol volume seviye değeri).
 * Output : None
 */
void LC75823::volumeLeftLevel(int levelValue) {
  int convertedLevelValue = ((levelValue - _volumeStartValue) /
                             ((_volumeEndValue - _volumeStartValue) / 8));

  _symbols[1] = B11111111;
  _symbols[1] >>= 8 - convertedLevelValue;
  bitWrite(_symbols[1], 7, _iconRock);
  _volumeLeftLevel = convertedLevelValue;
  if (_volumeLeftLevel == 0 && _volumeRightLevel == 0) {
    bitWrite(_symbols[2], 0, 0);
  } else {
    bitWrite(_symbols[2], 0, 1);
  }
  _print(_address, _screen, _symbols);
}

/*
* Function Name: volumeRightLevel
 * Description : Lcd sağ volume göstergelerinin değerini belirler. Değer aralığı volumeStartValue ve volumeEndValue metodları ile belirlenebilir.
 * Input : int levelValue (Sağ volume seviye değeri).
 * Output : None
 */
void LC75823::volumeRightLevel(int levelValue) {
  int convertedLevelValue = ((levelValue - _volumeStartValue) /
                             ((_volumeEndValue - _volumeStartValue) / 8));
  _symbols[3] = B11111111;
  _symbols[3] >>= 8 - convertedLevelValue;
  bitWrite(_symbols[3], 7, _iconRock);
  _volumeLeftLevel = convertedLevelValue;
  if (_volumeLeftLevel == 0 && _volumeRightLevel == 0) {
    bitWrite(_symbols[2], 0, 0);
  } else {
    bitWrite(_symbols[2], 0, 1);
  }
  _print(_address, _screen, _symbols);
}

/*
* Function Name: sChart (Scroll Chart)
 * Description : Lcd chart sembollerini animasyonlu olarak yakar.
 * Input : boolean chartValue (0 = Animasyon kapalı, 1 = Animasyon açık).
 * Output : None
 */
void LC75823::sChart(boolean chartValue) {
  if (chartValue) {
    for (int i = 2; i < 5; i++) {
      bitWrite(_symbols[0], 2, 0);
      bitWrite(_symbols[0], 3, 0);
      bitWrite(_symbols[0], 4, 0);
      bitWrite(_symbols[0], i, chartValue);
      _print(_address, _screen, _symbols);
    }
  }
}

/*
* Function Name: textLoopCount
 * Description : Girilen metnin ekrandaki tekrar sayısını döndürür.
 * Input : None
 * Output : int
 */
int LC75823::textLoopCount() { return _loopNumber; }

/*
* Function Name: _textLoop
 * Description : Gösterilen metnin, tekrar sayısını işler.
 * Input : None
 * Output : None
 */
void LC75823::_textLoop() {
  if (_sScroll > _textLenght) {
    _sScroll = 0;
    _loopNumber++;
  }
}

/*
* Function Name: text
 * Description : Metni yazdırır.
 * Input : char text[] - Yazdırılacak metni taşıyan char dizisi.
 * Output : None
 */
void LC75823::text(char text[]) {
  _textSize(text);
    char _screenText[8];
  for (int i = 0; i < 8; i++) {
    _screenText[i] = text[i];
    if (i >= _textLenght) {
      _screenText[i] = ' ';
    }
  }
  _letters(_screenText);
  _setLetters();
  _setSymbols();
  _print(_address, _screen, _symbols);
}

/*
 * Function Name: sText (Scroll Text)
 * Description : Metni soldan sağa doğru kaydırarak yazdırır.
 * Input : char text[] - Yazdırılacak metni taşıyan char dizisi.
 * Output : None
 */
void LC75823::sText(char text[]) {
  _textSize(text);
  char _screenText[8];
  for (int i = 0; i < 8; i++) {
    //int c = text[i + _tScroll] - 32;
    _screenText[i] = text[i + _tScroll];
    if ((i + _tScroll) >= _textLenght) {
      _screenText[i] = ' ';
    }
  }
  if (_tScroll == _textLenght) {
    _tScroll = 0;
  } else {
    _tScroll++;
  }
  _letters(_screenText);
  _setLetters();
  _textLoop();
  _setSymbols();
  _print(_address, _screen, _symbols);
}

/*
 * Function Name: _setSymbols
 * Description : Sembol durumlarını, _screen byte dizisine işler.
 * Input : None
 * Output : None
 */
void LC75823::_setSymbols() { bitWrite(_screen[0], 7, _iconSt); }

/*
 * Function Name: _setLetters
 * Description : Girilen metnin lcd boarduna özgü çevrilmiş datalarını, SPI byte data paketlerine uygun hale getirmek için,
 *               gerekli bit kaydırma işlemlerini yapar. Sonuç _screen byte dizisine atanır.
 * Input : None
 * Output : None
 */
void LC75823::_setLetters() {
  byte j = 1;
  _n = 0;
  for (int i = 0; i <= 14; i += 2) {
    _screen[i] = (_container[_n] << j) | (_container[_n + 1] >> (8 - j));
    if (i < 2) {
      _screen[i + 1] = _container[_n + 1] << j;
    } else if (i >= _containerSize) {
      _screen[i] = _container[_n + 1];
      _screen[i + 1] = 0;
    } else {
      _screen[i + 1] =
          (_container[_n + 1] << j) | (_container[_n + 2] >> (7 - j));
    }
    if ((_n + 2) > _containerSize) {
      _n = 0;
      _screen[i + 1] =
          _container[_containerSize] << j | _container[0] >> (7 - j);
    } else {
      _n += 2;
    }
    j++;
  }
  _sScroll++;
}

/*
 * Function Name: _print
 * Description : Hazırlanan _address int değişkenini, _screen ve _symbols byte
 *               dizilerini Arduino SPI kütüphanesini kullanarak sürücüye gönderir. 
 * Input : byte pScreen[] 
 * Output : None
 */
void LC75823::_print(int pAddress, byte pScreen[], byte pSymbols[]) {
  digitalWrite(_chipEnabledPin, LOW);
  // Address Data (A1- A8)
  SPI.transfer(pAddress);
  digitalWrite(_chipEnabledPin, HIGH);

  // Character Segment Data (D1- D120) 15 Byte
  for (int i = 0; i <= 14; i++) {
    SPI.transfer(pScreen[i]);
  }

  // Symbol Segment Data (D121 - D168) 5 Byte
  for (int i = 0; i <= 4; i++) {
    SPI.transfer(pSymbols[i]);
  }
  digitalWrite(_chipEnabledPin, LOW);
  delay(_textSpeed);
}

/*
 * Function Name: symbol
 * Description : Kullanıcının istediği sembolleri yakar.
 * Input : enum Symbol symbolName(sembol tanımı), 
 *         boolean status(sembolün görünürlüğü, 0 = Kapalı, 1 = Açık)
 * Output : None
 */
void LC75823::symbol(enum Symbol symbolName, boolean status) {
  switch (symbolName) {
  case ST:
    _iconSt = status;
    bitWrite(_screen[0], 7, status);
    break; // open or close ST icon.

  case POP:
    bitWrite(_symbols[0], 0, status);
    break;
  case CLAS:
    bitWrite(_symbols[0], 1, status);
    break;
  case CHART_1:
    bitWrite(_symbols[0], 2, status);
    break;
  case CHART_2:
    bitWrite(_symbols[0], 3, status);
    break;
  case CHART_3:
    bitWrite(_symbols[0], 4, status);
    break;
  case X_BASS:
    bitWrite(_symbols[0], 5, status);
    break;
  case TEYP_ICON:
    bitWrite(_symbols[0], 7, status);
    break;

  case VOLUME_LEFT_2:
    bitWrite(_symbols[1], 0, status);
    break;
  case VOLUME_LEFT_3:
    bitWrite(_symbols[1], 1, status);
    break;
  case VOLUME_LEFT_4:
    bitWrite(_symbols[1], 2, status);
    break;
  case VOLUME_LEFT_5:
    bitWrite(_symbols[1], 3, status);
    break;
  case VOLUME_LEFT_6:
    bitWrite(_symbols[1], 4, status);
    break;
  case VOLUME_LEFT_7:
    bitWrite(_symbols[1], 5, status);
    break;
  case VOLUME_LEFT_8:
    bitWrite(_symbols[1], 6, status);
    break;
  case ROCK:
    bitWrite(_symbols[1], 7, status);
    _iconRock = status;
    break;

  case VOLUME_1:
    bitWrite(_symbols[2], 0, status);
    break;

  case VOLUME_RIGHT_2:
    bitWrite(_symbols[3], 0, status);
    break;
  case VOLUME_RIGHT_3:
    bitWrite(_symbols[3], 1, status);
    break;
  case VOLUME_RIGHT_4:
    bitWrite(_symbols[3], 2, status);
    break;
  case VOLUME_RIGHT_5:
    bitWrite(_symbols[3], 3, status);
    break;
  case VOLUME_RIGHT_6:
    bitWrite(_symbols[3], 4, status);
    break;
  case VOLUME_RIGHT_7:
    bitWrite(_symbols[3], 5, status);
    break;
  case VOLUME_RIGHT_8:
    bitWrite(_symbols[3], 6, status);
    break;

  case MONO:
    bitWrite(_symbols[4], 4, status);
    break;
  case LOC:
    bitWrite(_symbols[4], 5, status);
    break;
  case CD_ICON:
    bitWrite(_symbols[4], 7, status);
    break;
  default:;
    break;
  }
  _print(_address, _screen, _symbols);
}

/*
 * Function Name: volumeChart
 * Description : Volume sembollerinin integer değerlerle yanıp-sönmesini sağlar.
 * Input : int volumeChartNo(volume sembol numarası), 
 *         boolean status(sembolün görünürlüğü, 0 = Kapalı, 1 = Açık)
 * Output : None
 */
void LC75823::volumeChart(int volumeChartNo, boolean status) {
  switch (volumeChartNo) {
  case 16:
    bitWrite(_symbols[0], 2, status);
    break; // CHART_1
  case 17:
    bitWrite(_symbols[0], 3, status);
    break; // CHART_2
  case 18:
    bitWrite(_symbols[0], 4, status);
    break; // CHART_3

  case 2:
    bitWrite(_symbols[1], 0, status);
    break; // VOLUME_LEFT_2
  case 3:
    bitWrite(_symbols[1], 1, status);
    break; // VOLUME_LEFT_3
  case 4:
    bitWrite(_symbols[1], 2, status);
    break; // VOLUME_LEFT_4
  case 5:
    bitWrite(_symbols[1], 3, status);
    break; // VOLUME_LEFT_5
  case 6:
    bitWrite(_symbols[1], 4, status);
    break; // VOLUME_LEFT_6
  case 7:
    bitWrite(_symbols[1], 5, status);
    break; // VOLUME_LEFT_7
  case 8:
    bitWrite(_symbols[1], 6, status);
    break; // VOLUME_LEFT_8

  case 1:
    bitWrite(_symbols[2], 0, status);
    break; // VOLUME_1

  case 9:
    bitWrite(_symbols[3], 0, status);
    break; // VOLUME_RIGHT_2
  case 10:
    bitWrite(_symbols[3], 1, status);
    break; // VOLUME_RIGHT_3
  case 11:
    bitWrite(_symbols[3], 2, status);
    break; // VOLUME_RIGHT_4
  case 12:
    bitWrite(_symbols[3], 3, status);
    break; // VOLUME_RIGHT_5
  case 13:
    bitWrite(_symbols[3], 4, status);
    break; // VOLUME_RIGHT_6
  case 14:
    bitWrite(_symbols[3], 5, status);
    break; // VOLUME_RIGHT_7
  case 15:
    bitWrite(_symbols[3], 6, status);
    break; // VOLUME_RIGHT_8
  default:;
    break;
  }
  _print(_address, _screen, _symbols);
}

/*
 * Function Name: _letters
 * Description : Girilen metindeki karakterlerin ascii karşılıkları ile character.h dosyasında bulunan character14SEG iki boyutlu dizisini 
 *               karşılaştırır ve aldığı değerleri _container byte dizisine aktarır. 
 * Input : char gk[](Girilen metnin ilk 8 karakteri)
 * Output : None
 */
void LC75823::_letters(char gk[]) {
  int d = 0;
  for (int i = 0; i < 8; i++) {
    int c = gk[i] - 32;
    if (c >= 0 && c <= 94) {
      _container[d] = pgm_read_byte(&character14SEG[c][0]);
      _container[d + 1] = pgm_read_byte(&character14SEG[c][1]);
    } else {
      _container[d] = 0;
      _container[d + 1] = 0;
    }
    d += 2;
  }
}
