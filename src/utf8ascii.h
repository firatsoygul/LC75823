/*
  UTF8-Decoder: convert UTF8-string to extended ASCII 
  Original code at http://playground.arduino.cc/Main/Utf8ascii
*/

#ifndef utf8ascii_h
#define utf8ascii_h

#include <Arduino.h>

static byte c1; // Last character buffer

class UTF8ASCII
{
public:
  UTF8ASCII();
  String utf8ascii(String s);
  void utf8ascii(char *s);
  byte utf8ascii(byte ascii);
};

#endif