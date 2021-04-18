/* Shows approx voltage from A0 pin (max. 5 v.)
 * Volume level icons will be adjusted according to the severity.
 *
 *                       *** ATTENTION!! ***
 * DO NOT APPLY A VOLTAGE HIGHER THAN 5 VOLT TO THE ARDUINO INPUTS.
 */

#include <LC75823.h>

LC75823 lcd;

char ss[2];
char sss[2];
int val = 0;
float volt;

void setup()
{
  lcd.begin(10, 130);
  lcd.volumeStartValue(0);
  lcd.volumeEndValue(1023);
}

void loop()
{
  lcd.speed(100);
  val = analogRead(0);
  volt = val * 0.00468;
  dtostrf(volt, 4, 2, ss);
  sprintf(sss, "%s V", ss);
  lcd.text(sss);
  lcd.volumeLeftLevel(val);
  lcd.volumeRightLevel(val);
  // delay(70);
}
