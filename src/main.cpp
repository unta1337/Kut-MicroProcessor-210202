// 기관명: 한국기술교육대학교
// 교과목: 마이크로프로세서및실습
// 프로젝트: 로봇 축구
// 소속: 미정
// 구성원: 김성녕 | 임재경 | 임창민 | 조경우

// 메인 함수: 환경 초기화, 주요 포트 및 로직 정의.
// 의존성: msg.h, cmd.h

#include "mbed.h"
#include "msg.h"
#include "cmd.h"
#include "ctrl.h"
#include "mtr.h"

#define MAX_MSG_LEN 40

// 명령 모드 설정, 0: 통신, 1: 명령.
// 소프트웨적 제어 불가능, 하드웨어적으로 제어해야 함.
DigitalOut en(PC_10);

// 시리얼 통신.
Serial pc(SERIAL_TX, SERIAL_RX);
Serial bt(PA_15, PB_7);

// 조이스틱.
AnalogIn x_raw(PC_2);
AnalogIn y_raw(PC_3);

// 스테핑 모터.
DigitalOut motor_en(PA_4);

PwmOut left(PA_0);
DigitalOut left_rotate(PC_2);

PwmOut right(PA_1);
DigitalOut right_rotate(PC_3);

// 기타.
Ticker ticker_ctrl_out;

// 해당 모듈이 수행하는 역할:
// MASTER: 컨트롤러.
// SLAVE: 모터 구동.
// MSG: 메시지 모드.
// CMD: 블루투스 모듈 설정.
enum Mode {
    MASTER,
    SLAVE,
    MSG,
    CMD
};
Mode mode;

void init(Mode mode_);

void ctrl_out();
void ctrl_in();

void msg_in();
void msg_out();

void cmd_in();
void cmd_out();

int main()
{
    init(SLAVE);
    
    pc.printf("Initial Configuration Completed. ");
    switch(mode)
    {
        case MASTER:
            pc.printf("[MASTER]\n");
            break;
        case SLAVE:
            pc.printf("[SLAVE]\n");
            break;
        case MSG:
            pc.printf("[MSG]\n");
            break;
        case CMD:
            pc.printf("[CMD]\n");
            break;
    }
    
    switch(mode)
    {
        case MASTER:
            ticker_ctrl_out.attach(&ctrl_out, 0.1);
            break;
        case SLAVE:
            bt.attach(&ctrl_in);
            break;
        case MSG:
            pc.attach(&msg_out);
            bt.attach(&msg_in);
            break;
        case CMD:
            pc.attach(&cmd_out);
            bt.attach(&cmd_in);
    }
        
    return 0; 
}

void init(Mode mode_)
{
    en = mode_ == CMD;
    mode = mode_;
    
    if (en)
    {
		pc.printf("[Baud Rate: 38400]\n");
        pc.baud(38400);
        bt.baud(38400);
    }
    else
    {
		pc.printf("[Baud Rate: 9600]\n");
        pc.baud(9600);
        bt.baud(9600);
    }
}

void ctrl_debug(int x, int y)
{
    pc.printf("CTRL IN: %d %d\n", x, y);
}

void ctrl_out()
{
    ctrl::out(&x_raw, &y_raw, &bt, &pc);
}

void ctrl_in()
{
    int x, y;
    ctrl::in(&bt, &x, &y);
    ctrl_debug(x, y);

    pc.printf("MOTOR SETUP\n");
    
    // 회전 우선.
    if (!(120 <= x && x <= 140))
        mtr::turn(&motor_en, &left, &left_rotate, &right, &right_rotate, x);
    else
        mtr::move(&motor_en, &left, &left_rotate, &right, &right_rotate, y);
    
    pc.printf("MOTOR DONE\n");
}

void msg_in()
{   
    char input[MAX_MSG_LEN];
    msg::in(&bt, input);
    pc.printf("MSG IN: %s\n", input);
}

void msg_out()
{
    char output[MAX_MSG_LEN];
    msg::get_string(&pc, output);
    pc.printf("MSG OUT: %s\n", output);
    msg::out(&bt, output);
}

void cmd_in()
{
    cmd::in(&bt, &pc);
}

void cmd_out()
{
    char output[MAX_MSG_LEN];
    msg::get_string(&pc, output);
    pc.printf("CMD OUT: %s\n", output);
    cmd::out(&pc, &bt, output);
}
