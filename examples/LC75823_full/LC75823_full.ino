#include <LC75823.h>

LC75823 lcd;

char full[9] = "########";
char alphabet[27] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
char number[11] = "0123456789";

void setup() { lcd.begin(10, 130); }

void loop()
{
  lcd.reset();
  lcd.clear();
  boolean sts = true;
  lcd.symbol(ST, sts);
  lcd.symbol(POP, sts);
  lcd.symbol(CLAS, sts);
  lcd.symbol(TEYP_ICON, sts);
  lcd.symbol(X_BASS, sts);
  lcd.symbol(ROCK, sts);
  lcd.symbol(MONO, sts);
  lcd.symbol(LOC, sts);
  lcd.symbol(CD_ICON, sts);
  lcd.symbol(TEYP_ICON, sts);
  lcd.volumeLeftLevel(8);
  lcd.volumeRightLevel(8);
  lcd.volumeChart(16, 1);
  lcd.volumeChart(17, 1);
  lcd.volumeChart(18, 1);

  lcd.text(full);
  delay(1500);

  lcd.clear();
  lcd.speed(100);
  for (int i = 0; lcd.textLoopCount() < 1; i++)
  {
    lcd.sChart(1);
    lcd.sText(alphabet);
  }

  lcd.clear();
  lcd.speed(150);
  for (int i = 0; lcd.textLoopCount() < 1; i++)
  {
    lcd.sChart(1);
    lcd.sText(number);
  }
}
