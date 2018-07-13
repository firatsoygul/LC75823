#include <LC75823.h>

LC75823 lcd;

void setup()
{
    lcd.begin(10, 130);
}

void loop()
{
    lcd.reset();
    lcd.clear();
    lcd.text("SYMBOLS");
    boolean sts = true;
    lcd.symbol(ST, sts);
    lcd.symbol(POP, sts);
    lcd.symbol(CLAS, sts);
    lcd.symbol(X_BASS, sts);
    lcd.symbol(ROCK, sts);
    lcd.symbol(MONO, sts);
    lcd.symbol(LOC, sts);
    lcd.symbol(CD_ICON, sts);
    lcd.symbol(TEYP_ICON, sts);
    lcd.volumeLeftLevel(8);
    lcd.volumeRightLevel(8);
    lcd.volumeChart(16, sts);
    lcd.volumeChart(17, sts);
    lcd.volumeChart(18, sts);
    delay(2000);

    lcd.speed(20);
    for (int i = 0; i <= 8; i++)
    {
        for (int j = 0; j <= 8; j++)
        {
            lcd.volumeLeftLevel(j);
            lcd.volumeRightLevel(j);
            lcd.sChart(1);
        }
    }
}
