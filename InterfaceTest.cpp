#include "mbed.h"
#include "TextLCD.h"
#include "ID_SpringProgress.h"

//can
/*-----Defined-----*/
//Serial
Serial pc(USBTX, USBRX, 921600);
// void pc_RX(void);

//CAN
// CAN can(PA_11, PA_12, 1000000);
// CANMessage rxMsg;
// void can_RX(void);

//LCD
TextLCD LCD(PC_0, PC_1, PB_0, PA_4, PA_1, PA_0, TextLCD::LCD20x4);

//LED
DigitalOut led_Manual(PC_13, PullDown);
DigitalOut led_Auto(PB_7, PullDown);

//Trimmer
AnalogIn Adjust_MaxSpeed(PC_3);

//Switches
/*Toggle*/
DigitalIn Dsw_FieldDicision(PC_12, PullDown);
DigitalIn Dsw_OutputDicision(PA_15, PullDown);
/*Tact*/
InterruptIn Isw_OriginReset(PH_1, PullDown);
/*Other*/
InterruptIn Isw_Start(PC_10, PullDown);
/*-----------------*/

/*-----Users-----*/
//LED
typedef struct
{
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
    DigitalOut *begin() { return &this->L1; }
    DigitalOut *end() { return &this->L10 + 1; }
} LED;

//Switches
/*Toggle*/
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
/*Tact*/
// InterruptIn tc1(PA_9, PullDown);
// InterruptIn tc2(PA_8, PullDown);
// InterruptIn tc3(PA_7, PullDown);
// InterruptIn tc4(PA_6, PullDown);
// InterruptIn tc5(PA_5, PullDown);
/*---------------*/

int16_t VerifyUserToggleSwitch(void);

int main(void)
{

    led_Auto = 0;
    led_Manual = 0;
    int16_t ToggleSwitch = 0;
    pc.printf("System Started\r\n");
    // LCD.cls();
    // LCD.locate(0, 0);
    // LCD.printf("System Started\n");
    // pc.attach(&pc_RX, Serial::RxIrq);
    // can.attach(&can_RX);
    wait(0.5);
    while (1)
    {
        LCD.cls();
        LCD.locate(0, 0);
        LCD.printf("Maxspeed     :%0.2f\n", Adjust_MaxSpeed.read());
        ToggleSwitch = VerifyUserToggleSwitch();
        if (ToggleSwitch & 1024)
        {
            LCD.printf("Field        :Red\n");
            ToggleSwitch -= 1024;
        }
        else
        {
            LCD.printf("Field        :Blue\n");
        }
        if (ToggleSwitch & 2048)
        {
            LCD.printf("Output       :Drive\n");
            ToggleSwitch -= 2048;
        }
        else
        {
            LCD.printf("Output       :Stop\n");
        }

        LCD.printf("Switch state :%d\n", ToggleSwitch);
        wait_ms(35);
    }
}

void core(void)
{
}

/*void can_RX(void)
{
    can.read(rxMsg);
    switch (rxMsg.data[0])
    {
    case cmd_reset:
        NVIC_SystemReset();
        break;

        // case
    }
}*/

void pc_RX(void)
{
    //??
}

int16_t VerifyUserToggleSwitch(void)
{
    int16_t ToggleSwitch = 0;
    /*L1 = 0;
    L2 = 0;
    L3 = 0;
    L4 = 0;
    L5 = 0;
    L6 = 0;
    L7 = 0;
    L8 = 0;
    L9 = 0;
    L10 = 0;
    if (!tg1)
    {
        ToggleSwitch += 0b0000000000000001;
        L1 = 1;
    }
    else if (!tg2)
    {
        ToggleSwitch += 0b0000000000000010;
        L2 = 1;
    }
    else if (!tg3)
    {
        ToggleSwitch += 0b0000000000000100;
        L3 = 1;
    }
    else if (!tg4)
    {
        ToggleSwitch += 0b0000000000001000;
        L4 = 1;
    }
    else if (!tg5)
    {
        ToggleSwitch += 0b0000000000010000;
        L5 = 0;
    }
    else if (!tg6)
    {
        ToggleSwitch += 0b0000000000100000;
        L6 = 0;
    }
    else if (!tg7)
    {
        ToggleSwitch += 0b0000000001000000;
        L1 = 0;
    }
    else if (!tg8)
    {
        ToggleSwitch += 0b0000000010000000;
    }
    else if (!tg9)
    {
        ToggleSwitch += 0b0000000100000000;
    }
    else if (!tg10)
    {
        ToggleSwitch += 0b0000001000000000;
    }
    else if (!Dsw_FieldDicision){
        ToggleSwitch += 0b0000010000000000;
    }
    else if (!Dsw_OutputDicision){
        ToggleSwitch += 0b0000100000000000;
    }*/
    ToggleSwitch += ((!tg1) ? 0b0000000000000001 : 0);
    ToggleSwitch += ((!tg2) ? 0b0000000000000010 : 0);
    ToggleSwitch += ((!tg3) ? 0b0000000000000100 : 0);
    ToggleSwitch += ((!tg4) ? 0b0000000000001000 : 0);
    ToggleSwitch += ((!tg5) ? 0b0000000000010000 : 0);
    ToggleSwitch += ((!tg6) ? 0b0000000000100000 : 0);
    ToggleSwitch += ((!tg7) ? 0b0000000001000000 : 0);
    ToggleSwitch += ((!tg8) ? 0b0000000010000000 : 0);
    ToggleSwitch += ((!tg9) ? 0b0000000100000000 : 0);
    ToggleSwitch += ((!tg10) ? 0b0000001000000000 : 0);
    ToggleSwitch += ((!Dsw_FieldDicision) ? 0b0000010000000000 : 0);
    ToggleSwitch += ((!Dsw_OutputDicision) ? 0b0000100000000000 : 0);

    L1 = (int)(ToggleSwitch & 1);
    L2 = (int)(ToggleSwitch & 2);
    L3 = (int)(ToggleSwitch & 4);
    L4 = (int)(ToggleSwitch & 8);
    L5 = (int)(ToggleSwitch & 16);
    L6 = (int)(ToggleSwitch & 32);
    L7 = (int)(ToggleSwitch & 64);
    L8 = (int)(ToggleSwitch & 128);
    L9 = (int)(ToggleSwitch & 256);
    L10 = (int)(ToggleSwitch & 512);

    return ToggleSwitch;
}