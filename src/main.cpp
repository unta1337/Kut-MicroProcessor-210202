#include "mbed.h"
#include "msg.h"
#include "controller.h"

DigitalOut en(PC_10);

DigitalOut led(LED1);

AnalogIn xRaw(PC_2);
AnalogIn yRaw(PC_3);

Serial pc(SERIAL_TX, SERIAL_RX);
Serial bt(PA_15, PB_7);

Ticker temp;

enum Role {
    MASTER,
    SLAVE,
    MSG
};
Role role;

// 컨트롤러 포트 설정 필요.

// 전역 변수를 통한 환경 초기화.
void init()
{
    pc.baud(9600);
    bt.baud(9600);
}

void pcOut()
{
    char str[100];
    getString(&pc, str, 100);
    msgOut(&pc, &bt, str);
    
    // 컨트롤러 신호 전송 로직 필요.
}

void pcIn()
{   
    char input[100];
    msgIn(&bt, input);
    
    // led 제어 구문.
    if (!strcmp(input, "ledOn"))
    {
        pc.printf("cmd in: ledOn\n");
        led = 1;
    }
    else if (!strcmp(input, "ledOff"))
    {
        pc.printf("cmd in: ledOff\n");
        led = 0;
    }
    
    // 모터 제어 구문.
    else if (!strcmp(input, "moveF"))
    {
        pc.printf("moveFoward: not yet implemented.\n");
    }
    else if (!strcmp(input, "moveB"))
    {
        pc.printf("moveBackward: not yet implemented.\n");
    }
    else if (!strcmp(input, "turnL"))
    {
        pc.printf("turnLeft: not yet implemented.\n");
    }
    else if (!strcmp(input, "turnR"))
    {
        pc.printf("moveRight: not yet implemented.\n");
    }
    
    // 기타.
    else
    {
        pc.printf("%s\n", input);
    }
}

void ctrlOut()
{
    sendCtrl(&xRaw, &yRaw, &bt);
}

int main()
{
    pc.printf("start\n");
    
    // 전역 변수 초기화.
    en = 0;
    role = MASTER;
    
    // 환경 초기화.
    init();
    
    // 실행 코드.
    switch(role)
    {
        case MASTER:
            pc.attach(&ctrlOut);
            break;
        case SLAVE:
            bt.attach(&pcIn);
            break;
        case MSG:
            pc.attach(&pcOut);
            bt.attach(&pcIn);
            break;
    }
        
    return 0; 
}