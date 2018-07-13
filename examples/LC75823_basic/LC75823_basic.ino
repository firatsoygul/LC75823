#include <LC75823.h>

LC75823 lcd;

void setup()
{
    lcd.begin(10, 130); //SlaveSelect pin, chip address.
    lcd.speed(250); // Animation speed.
}

void loop()
{
    lcd.sText("LC75823 LIBRARY FOR ARDUINO."); // Text scrolling.
}