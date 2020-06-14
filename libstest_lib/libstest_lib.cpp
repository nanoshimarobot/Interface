#include "libstest_lib.h"

libstest_lib::libstest_lib(int loop_rate)
    : _pc(USBTX, USBRX, 921600),
      _can(PA_11, PA_12, 1000000),
      _lcd(PC_0, PC_1, PB_0, PA_4, PA_1, PA_0, TextLCD::LCD20x4),
      _L1(PC_4),
      _L2(PB_13),
      _L3(PB_14),
      _L4(PB_15),
      _L5(PB_1),
      _L6(PB_2),
      _L7(PB_12),
      _L8(PC_5),
      _L9(PC_6),
      _L10(PC_8),
      _tg1(PB_4, PullDown),
      _tg2(PB_10, PullDown),
      _tg3(PC_7, PullDown),
      _tg4(PB_6, PullDown),
      _tg5(PC_9, PullDown),
      _tg6(PD_2, PullDown),
      _tg7(PC_11, PullDown),
      _tg8(PA_10, PullDown),
      _tg9(PB_3, PullDown),
      _tg10(PB_5, PullDown),
      _Manual(PC_13, PullDown),
      _Auto(PB_7, PullDown),
      _FieldDicision(PC_12, PullDown),
      _OutputDicision(PA_15, PullDown),
      _OriginReset(PH_1, PullDown),
      _Start(PC_10, PullDown),
      _trim(PC_3)
{
    _OriginReset.rise(this, &libstest_lib::Callback_OriginReset);
    _Start.rise(this, &libstest_lib::Callback_Start);
    _can.attach(this, &libstest_lib::_can_RX);
    _can.filter(0x001, 0x001, CANStandard);
    _loop_rate = loop_rate;
    _L1 = 0;
    _L2 = 0;
    _L3 = 0;
    _L4 = 0;
    _L5 = 0;
    _L6 = 0;
    _L7 = 0;
    _L8 = 0;
    _L9 = 0;
    _L10 = 0;
    _Manual = 0;
    _Auto = 0;
    _lcd.cls();
    _lcd.locate(1, 4);
    _lcd.printf("system start\n");
}

void libstest_lib::updateAllState(MovingState state)
{
    _pc.printf("verify all state(oo uso)\r\n");
    uint16_t Toggle = updateSwitchState();
    _lcd.cls();
    _lcd.locate(0, 0);
    _lcd.printf("System UGOUGO\n");
    if (state == Auto)
    {
        _Auto = 1;
        _Manual = 0;
    }
    else
    {
        _Auto = 0;
        _Manual = 1;
    }

    if (Toggle & (1 << 10))
    {
        _lcd.printf("Red\n");
    }
    else
    {
        _lcd.printf("Blue\n");
    }
    if (Toggle & (1 << 11))
    {
        _lcd.printf("Drive\n");
    }
    else
    {
        _lcd.printf("Stop\n");
    }

    _lcd.printf("%s\n", STR(MovingState.state));
    wait_ms(_loop_rate);
}

uint16_t libstest_lib::updateSwitchState()
{
    uint16_t Toggle = 0;
    uint16_t _mask = 1;
    Toggle |= _tg1;
    Toggle |= (_tg2 << 1);
    Toggle |= (_tg3 << 2);
    Toggle |= (_tg4 << 3);
    Toggle |= (_tg5 << 4);
    Toggle |= (_tg6 << 5);
    Toggle |= (_tg7 << 6);
    Toggle |= (_tg8 << 7);
    Toggle |= (_tg9 << 8);
    Toggle |= (_tg10 << 9);

    Toggle |= (_FieldDicision << 10);
    Toggle |= (_OutputDicision << 11);

    Toggle = ~Toggle;
    _L1 = (Toggle & _mask);
    _L2 = (Toggle & (_mask << 1));
    _L3 = (Toggle & (_mask << 2));
    _L4 = (Toggle & (_mask << 3));
    _L5 = (Toggle & (_mask << 4));
    _L6 = (Toggle & (_mask << 5));
    _L7 = (Toggle & (_mask << 6));
    _L8 = (Toggle & (_mask << 7));
    _L9 = (Toggle & (_mask << 8));
    _L10 = (Toggle & (_mask << 9));

    return Toggle;
}

float libstest_lib::updateTrimState()
{
    _trim_val = _trim.read();
}

void libstest_lib::Callback_OriginReset()
{
    wait_ms(10);
}

void libstest_lib::Callback_Start()
{
    wait_ms(10);
}

void libstest_lib::_can_RX()
{
    _can.read(_rxMsg);

    switch (_rxMsg.data[0])
    {
    case cmd_reset:
        NVIC_SystemReset();
        break;
    case cmd_coordinate:
    }
}