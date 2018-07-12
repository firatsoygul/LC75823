#include <LC75823.h>

LC75823 lcd;

char *f = "ÇÇSOYGÜL FIRAT";

void setup() {

lcd.begin(10,130);
Serial.begin(9600);
}

void loop() {

    //utf8ascii(f);
    lcd.speed(150);

    lcd.clear();
    lcd.sText(f);

}