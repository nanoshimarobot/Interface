#include "mbed.h"
#include "TextLCD/TextLCD.h"
#pragma once

class Interface
{
public:
    Interface();
    test();
    core();

private:
    void InitLCD(void);
    int16_t VerifyToggleSwitch(void);
    void CallbackOriginReset(void);
    void CallbackStart(void);
    void can_RX(void);
    void pc_Rx(void);
    CAN can;
    Serial pc;
    TextLCD lcd;
    int16_t toggle_switch = 0;
    float MaxSpeed_val = 0;
    AnalogIn MaxSpeed(PC_3);

    //User LEDs
    DigitalOut L1(PC_4, PullDown);
    DigitalOut L2(PB_13, PullDown);
    DigitalOut L3(PB_14, PullDown);
    DigitalOut L4(PB_15, PullDown);
    DigitalOut L5(PB_1, PullDown);
    DigitalOut L6(PB_2, PullDown);
    DigitalOut L7(PB_12, PullDown);
    DigitalOut L8(PC_5, PullDown);
    DigitalOut L9(PC_6, PullDown);
    DigitalOut L10(PC_8, PullDown);

    //User Toggle Switch
    DigitalIn tg1(PB_4, PullDown);
    DigitalIn tg2(PB_10, PullDown);
    DigitalIn tg3(PC_7, PullDown);
    DigitalIn tg4(PB_6, PullDown);
    DigitalIn tg5(PC_9, PullDown);
    DigitalIn tg6(PD_2, PullDown);
    DigitalIn tg7(PC_11, PullDown);
    DigitalIn tg8(PA_10, PullDown);
    DigitalIn tg9(PB_3, PullDown);
    DigitalIn tg10(PB_5, PullDown);

    //Defined Switch
    DigitalIn FieldDicision(PC_12, PullDown);
    DigitalIn OutputDicision(PA_15, PullDown);
    InterruptIn _OriginReset(PH_1, PullDown);
    InterruptIn _Start(PC_10, PullDown);

    //Defined LED
    DigitalOut Manual(PC_13, PullDown);
    DigitalOut Auto(PB_7, PullDown);
};