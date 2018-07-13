#include <LC75823.h>

LC75823 lcd;

char txt[28] = "LC75823 LIBRARY FOR ARDUINO";
char b[33];
char c[4];
int sa, sb;
char ss[9];

void setup()
{
  lcd.begin(10, 130); //SlaveSelect pin, chip address.
}

void loop()
{

  lcd.speed(300);

  lcd.clear();
  lcd.text("ARDUINO");
  delay(1000);
  lcd.text("LC75823");
  delay(1000);
  lcd.text("LIBRARY");
  delay(1000);

  lcd.clear();
  for (int i = 0; lcd.textLoopCount() < 2; i++)
  {
    sprintf(b, "THIS TEXT WILL SCROLL TWICE. - %d", 2 - lcd.textLoopCount());
    lcd.sText(b);
  }

  lcd.clear();
  lcd.speed(100);
  for (int x = 20; x <= 120; x++)
  {
    sprintf(c, "%03i", x);
    lcd.text(c);
    //delay(500);
  }

  lcd.clear();
  lcd.speed(300);
  for (int x = 1; x <= 10; x++)
  {
    sa = random(10, 99);
    sb = random(1, 9);
    sprintf(ss, "%d+%d=%03i", sa, sb, sa + sb);
    lcd.text(ss);
    delay(500);
  }

  lcd.clear();
  lcd.speed(150);
  for (int i = 0; lcd.textLoopCount() < 1; i++)
  {
    lcd.sText(txt);
  }
}
