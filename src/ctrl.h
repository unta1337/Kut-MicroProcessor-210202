// 기관명: 한국기술교육대학교
// 교과목: 마이크로프로세서및실습
// 프로젝트: 로봇 축구
// 소속: 미정
// 구성원: 김성녕 | 임재경 | 임창민 | 조경우

// 컨트롤 헤더: 컨트롤러 입출력 정의.
// 의존성: msg.h

#ifndef _CTRL_H
#define _CTRL_H

#ifndef MAX_MSG_LEN
#define MAX_MSG_LEN 40
#endif

#include "mbed.h"
#include "msg.h"

namespace ctrl
{
    float raw_in(AnalogIn* src)
    {
        return src->read();
    }
    
    int graded_in(AnalogIn* src)
    {
        float raw = raw_in(src);
        int ret = (int)(raw * 9);
        
        return ret;
    }
    
    void in(Serial* src, int* x, int* y)
    {
        char buffer[MAX_MSG_LEN];
        msg::in(src, buffer);
        
        *x = buffer[0] - '0';
        *y = buffer[1] - '0';
    }
    
    void out(AnalogIn* src1, AnalogIn* src2, Serial* dest)
    {
        char x = graded_in(src1) + '0';
        char y = graded_in(src2) + '0';
        
        dest->putc(x);
        dest->putc(y);
        dest->putc(';');
    }
}
    
#endif