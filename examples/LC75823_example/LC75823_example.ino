#include <LC75823.h>

LC75823 lcd;

char txt[135] = "ABCDEF GHIJKLMNOPRSTUVS444487654321NRRTTTTTTTTTDJUUUUUUUDDDDDDDDDDSADHKBBBBBDHFHFHHHHHHHGGGGGGUUUUUUYYYYYYHHHHHHRRRRRRFFFFFFFTTTTTT12345";
char c[4];
int sa,sb;
char ss[6];


void setup() {


lcd.begin(10,130); //SlaveSelect pin, chip address.

}

void loop() {

  lcd.speed(300);

  lcd.clear();
  for (int i=0;i<20;i++){
    lcd.text("FIRAT SYG");
  }
    delay(1500);

  lcd.clear();
  for(int i=0 ; lcd.currentTextLoopCount() < 2 ; i++){
    lcd.sText("DENEME MESAJI 30 HAZIRAN 2018");
  }

  lcd.clear();
  for(int x=0 ; x <=110 ; x++){
    sprintf (c, "%03i", x);
    Serial.println(c);
    lcd.sText(c);
    //delay(500);
  }

  lcd.clear();
  for(int x=1 ; x <=10 ; x++){
    sa = random(10,99);
    sb = random(1,9);
    sprintf (ss, "%d+%d=%03i", sa,sb,sa+sb);
    lcd.text(ss);
    delay(500);
  }

  for(int i=0 ; lcd.currentTextLoopCount() < 1 ; i++){
    lcd.sText(txt);
  }
}
