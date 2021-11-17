#include "mbed.h"
#include "msg.h"

DigitalOut en(PC_10);

Serial pc(SERIAL_TX, SERIAL_RX);
Serial bt(PA_15, PB_7);

// 전역 변수를 통한 환경 초기화.
void init()
{
    if (en)
    {
        pc.baud(38400);
        bt.baud(38400);
    }
    else
    {
        pc.baud(9600);
        bt.baud(9600);
    }
}

void pcOut()
{
    if (en)
        cmdOut(&pc, &bt);
    else
        msgOut(&pc, &bt);
}

void pcIn()
{
    msgIn(&bt, &pc);
}

int main()
{
    pc.printf("start\n");
    
    // 전역 변수 초기화.
    en = 0;
    
    // 환경 초기화.
    init();
    
    // 실행 코드.
    pc.attach(&pcOut);
    bt.attach(&pcIn);
        
    return 0; 
}