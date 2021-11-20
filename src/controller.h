#ifndef _CNTL_H
#define _CNTL_H

#include "mbed.h"
#include "msg.h"

float ctrlRawIn(AnalogIn* src)
{
    return src->read();
}

int ctrlGetGrade(AnalogIn* src)
{
    float rawIn = src->read();
    
    int sign = 1;
    int ret = 0;
    
    if (rawIn < 0.45f)
    {
        sign = -1;
        rawIn = 1.0f - rawIn;
    }
    
    if (0.55f < rawIn && rawIn <= 0.65f)
    {
        ret = 1;
    }
    else if (0.65f < rawIn && rawIn <= 0.75f)
    {
        ret = 2;
    }
    else if (0.75f < rawIn && rawIn <= 0.85f)
    {
        ret = 3;
    }
    else if (0.85f < rawIn && rawIn <= 0.95f)
    {
        ret = 4;
    }
    else if (0.95f < rawIn && rawIn <= 1.0f)
    {
        ret = 5;
    }
    
    return sign * ret;
}

void sendCtrl(AnalogIn* src1, AnalogIn* src2, Serial* dest)
{
    int x = ctrlGetGrade(src1);
    int y = -ctrlGetGrade(src2);

    if (x != 0)
    {
        switch(x)
        {
            case -5:
                dest->printf("tnl5\n");
                break;
            case -4:
                dest->printf("tnl4\n");
                break;
            case -3:
                dest->printf("tnl3\n");
                break;
            case -2:
                dest->printf("tnl2\n");
                break;
            case -1:
                dest->printf("tnl1\n");
                break;
            case 0:
                dest->printf("tst\n");
                break;
            case 1:
                dest->printf("tnr1\n");
                break;
            case 2:
                dest->printf("tnr2\n");
                break;
            case 3:
                dest->printf("tnr3\n");
                break;
            case 4:
                dest->printf("tnr4\n");
                break;
            case 5:
                dest->printf("tnr5\n");
                break;
        }
    }

    if (x == 0)
    {
        switch(y)
        {
            case -5:
                dest->printf("mvb5\n");
                break;
            case -4:
                dest->printf("mvb4\n");
                break;
            case -3:
                dest->printf("mvb3\n");
                break;
            case -2:
                dest->printf("mvb2\n");
                break;
            case -1:
                dest->printf("mvb1\n");
                break;
            case 0:
                dest->printf("mst\n");
                break;
            case 1:
                dest->printf("mvf1\n");
                break;
            case 2:
                dest->printf("mvf2\n");
                break;
            case 3:
                dest->printf("mvf3\n");
                break;
            case 4:
                dest->printf("mvf4\n");
                break;
            case 5:
                dest->printf("mvf5\n");
                break;
        }
    }
}

#endif