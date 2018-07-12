#include <LC75823.h>

LC75823 lcd;

void setup() {

lcd.begin(10,130);

}

void loop() {

    //lcd.clear();

    //lcd.text ("ABCDEFGHIJKLMN");
    lcd.text ("AB######");
    lcd.sChart(1);
    //delay(50);


}
