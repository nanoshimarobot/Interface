#include "Interface.h"

Interface::Interface() : can(PA_11, PA_12, 1000000), pc(USBTX, USBRX, 921600), lcd(PC_0, PC_1, PB_0, PA_4, PA_1, PA_0, TextLCD::LCD20x4)
{
    this->InitLCD();
    _OriginReset.rise(&this, Interface::CallbackOriginReset);
    _Start.rise(&this, Interface::CallbackStart);
}

void Interface::test()
{
}

void Interface::core()
{
}

void Interface::InitLCD()
{
    this->lcd.cls();
    this->lcd.locate(0, 0);
    this->lcd.printf("System Start\n");
}

void Interface::Init()
{
}

int16_t Interface::VerifyToggleSwitch()
{
}

void Interface::CallbackOriginReset()
{
}

void Interface::CallbackStart()
{
}

void Interface::can_RX()
{
}

void Interface::pc_RX()
{
}