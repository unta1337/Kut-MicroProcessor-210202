// 기관명: 한국기술교육대학교
// 교과목: 마이크로프로세서및실습
// 프로젝트: 로봇 축구
// 소속: 미정
// 구성원: 김성녕 | 임재경 | 임창민 | 조경우

// 메지시 헤더: 문자열 기반 통신 정의.
// 의존성: -

#ifndef _MSG_H
#define _MSG_H

#ifndef MAX_MSG_LEN
#define MAX_MSG_LEN 40
#endif

#include "mbed.h"

namespace msg
{
    void get_string(Serial* src, char dest[], char terminator = ';')
    {
        char buffer = src->getc();
        
        for (int i = 0; i < MAX_MSG_LEN; i++)
            dest[i] = 0;
    
        int index = 0;
        while (index < MAX_MSG_LEN && buffer != terminator)
        {
            dest[index++] = buffer;
            buffer = src->getc();
        }
    }

    void in(Serial* src, char dest[])
    {
        get_string(src, dest);
    }

    void out(Serial* dest, char msg[])
    {
        int index = 0;
        while (msg[index] != '\0')
            dest->putc(msg[index++]);
        dest->putc(';');
    }
}
    
#endif