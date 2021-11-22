// 기관명: 한국기술교육대학교
// 교과목: 마이크로프로세서및실습
// 프로젝트: 로봇 축구
// 소속: 미정
// 구성원: 김성녕 | 임재경 | 임창민 | 조경우

// 명령줄 헤더: 블루투스 모듈 설정 명령줄 정의.
// 의존성: -

#ifndef _CMD_H
#define _CMD_H

#include "mbed.h"

namespace cmd
{
    void in(Serial* src, Serial* dest)
    {
        dest->putc(src->getc());
    }

    void out(Serial* src, Serial* dest, char cmd[])
    {
        dest->printf("%s\r\n", cmd);
    }
}

#endif