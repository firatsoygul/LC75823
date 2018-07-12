#include <LC75823.h>

LC75823 lcd;

  char ss[2];
  char sss[2];
  int val = 0;
  float val2;
  
void setup() {

Serial.begin(9600);
lcd.begin(10,130);
lcd.volumeStartValue(0);
lcd.volumeEndValue(1023);
}

void loop() {
  
    lcd.speed(100);
    //lcd.clear();
    val = analogRead(0);
    val2 = val*0.00468;
    dtostrf(val2, 4, 2, ss);
    sprintf(sss, "%s V",ss);
    //lcd.text (sss);
    lcd.sText ("FIRAT SOYGUL");
    lcd.volumeLeftLevel(val);
    //delay(70);

}
