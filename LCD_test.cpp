#include "mbed.h"
#include "TextPanel.h"

TextPanel lcd(D2, D3, D4, D5, D6, D7);

int main(void)
{
    lcd.clearScreen();
    lcd.positionSet(0, 0);

    lcd.printf("U N K O");
}