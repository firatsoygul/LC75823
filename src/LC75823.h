/*
  LC75823 Library for Arduino.
  Created by Fırat SOYGÜL, 20 Aralık 2017
  GNU General Public License v3.0
  (https://github.com/firatsoygul/LC75823/blob/master/LICENSE)
*/

#ifndef LC75823_h
#define LC75823_h
#include "Arduino.h"

enum Symbol {
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
};

class LC75823 {
public:
  LC75823();
  void begin(int chipEnabledPin, int address);
  void text(char text[]);
  void sChart(boolean chartValue);
  void sText(char text[]);
  int textLoopCount();
  void symbol(enum Symbol symbolName, boolean status);
  void volumeChart(int volumeChartNo, boolean status);
  void volumeStartValue(int startValue);
  void volumeEndValue(int endValue);
  void volumeLeftLevel(int levelValue);
  void volumeRightLevel(int levelValue);
  void speed(int textSpeed);
  void display();
  void noDisplay();
  void clear();
  void reset();

private:
  int _volumeLeftLevel = 0;
  int _volumeRightLevel = 0;
  int _loopNumber = 0;
  int _tScroll = 0;
  byte _sScroll = 0;
  byte _container[16];
  int _containerSize = 16;
  int _n = 0;
  int _textLenght = 0;
  int _chipEnabledPin = 10;
  int _address = 130;
  int _textSpeed = 300; // Default speed
  void _textLoop();
  void _textSize(char text[]);
  void _letters(char gk[]);
  void _letters_ORJ(uint8_t gk[]);
  void _setLetters();
  void _setSymbols();
  void _print(int pAddress, byte pScreen[], byte pSymbols[]);
  int _volumeStartValue = 0;
  int _volumeEndValue = 8;
  boolean _iconSt = false;
  boolean _iconRock = false;
  // boolean _iconMono = false;
  // boolean _iconLoc = false;
  // boolean _iconClas = false;
  // boolean _iconPop = false;
  // boolean _iconTeyp = false;
  // boolean _iconCd = false;
  // boolean _iconXBass = false;
  // boolean _iconChart1 = false;
  // boolean _iconChart2 = false;
  // boolean _iconChart3 = false;
  // boolean _iconVolume1 = false;
  // boolean _iconVolumeLeft2 = false;
  // boolean _iconVolumeLeft3 = false;
  // boolean _iconVolumeLeft4 = false;
  // boolean _iconVolumeLeft5 = false;
  // boolean _iconVolumeLeft6 = false;
  // boolean _iconVolumeLeft7 = false;
  // boolean _iconVolumeLeft8 = false;
  // boolean _iconVolumeRight2 = false;
  // boolean _iconVolumeRight3 = false;
  // boolean _iconVolumeRight4 = false;
  // boolean _iconVolumeRight5 = false;
  // boolean _iconVolumeRight6 = false;
  // boolean _iconVolumeRight7 = false;
  // boolean _iconVolumeRight8 = false;
  byte _symbols[6];         // 5 SPI byte package for symbol data
  byte _screen[16];         // 15 SPI byte package for character data
};

#endif
