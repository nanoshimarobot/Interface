#pragma once
#include "mbed.h"
#include "TextLCD/TextLCD.h"

#define cmd_reset 0x003
#define cmd_coordinate 0x004

#define STR(ver) #ver
typedef enum
{
    Auto,
    Manual
} MovingState;

class libstest_lib
{
public:
    libstest_lib(int loop_rate);
    libstest_lib(libstest_lib &libs);
    void updateAllState(MovingState state);
    void accessLED(int16_t ld_num);

private:
    uint16_t updateSwitchState();
    float updateTrimState();
    void Callback_OriginReset();
    void Callback_Start();
    void _can_RX();
    //Serial
    Serial _pc;
    //CAN
    CAN _can;
    CANMessage _rxMsg;

    //LCD
    TextLCD _lcd;

    //for users
    DigitalOut _L1;
    DigitalOut _L2;
    DigitalOut _L3;
    DigitalOut _L4;
    DigitalOut _L5;
    DigitalOut _L6;
    DigitalOut _L7;
    DigitalOut _L8;
    DigitalOut _L9;
    DigitalOut _L10;
    DigitalIn _tg1;
    DigitalIn _tg2;
    DigitalIn _tg3;
    DigitalIn _tg4;
    DigitalIn _tg5;
    DigitalIn _tg6;
    DigitalIn _tg7;
    DigitalIn _tg8;
    DigitalIn _tg9;
    DigitalIn _tg10;

    //Defined LEDs
    DigitalOut _Manual;
    DigitalOut _Auto;

    //Defined Switch
    DigitalIn _FieldDicision;
    DigitalIn _OutputDicision;
    InterruptIn _OriginReset;
    InterruptIn _Start;

    //Trim
    AnalogIn _trim;

    //other
    int _loop_rate;
    float _trim_val;
    float x, y;
    union
};