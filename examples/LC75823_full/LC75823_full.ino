#include <LC75823.h>

LC75823 lcd;

  char ss1[50] ="########";
  char ss2[50] ="ABCDEFGHIJKLMNOPRSTUVYZ";
  char ss3[50] ="0123456789";
  
void setup() {

Serial.begin(9600);
lcd.begin(10,130);
}

void loop() {
  


    boolean sts = true;

    lcd.symbol(ST,sts);
    lcd.symbol(POP,sts);
    lcd.symbol(CLAS,sts);
    lcd.symbol(TEYP_ICON,sts);
    lcd.symbol(X_BASS,sts);
    lcd.symbol(ROCK,sts);
    lcd.symbol(MONO,sts);
    lcd.symbol(LOC,sts);
    lcd.symbol(CD_ICON,sts);
    lcd.symbol(TEYP_ICON,sts);


}
