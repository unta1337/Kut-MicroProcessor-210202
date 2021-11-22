// 기관명: 한국기술교육대학교
// 교과목: 마이크로프로세서및실습
// 프로젝트: 로봇 축구
// 소속: 미정
// 구성원: 김성녕 | 임재경 | 임창민 | 조경우

// 컨트롤 헤더: 컨트롤러 입출력 정의.
// 의존성: msg.h, tool.h

#ifndef _CTRL_H
#define _CTRL_H

#ifndef MAX_MSG_LEN
#define MAX_MSG_LEN 40
#endif

#include "mbed.h"
#include "msg.h"
#include "tool.h"

namespace ctrl
{
    float raw_in(AnalogIn* src)
    {
        return src->read();
    }
    
    int graded_in(AnalogIn* src)
    {
        float raw = raw_in(src);
        int ret = (int)(raw * 255);
        
        return ret;
    }
    
    void in(Serial* src, int* x, int* y)
    {
        char x_buffer[MAX_MSG_LEN];
        char y_buffer[MAX_MSG_LEN];
        
        msg::in(src, x_buffer);
        msg::in(src, y_buffer);
        
        *x = tool::string_to_int(x_buffer);
        *y = tool::string_to_int(y_buffer);
    }
    
    void out(AnalogIn* src1, AnalogIn* src2, Serial* dest, Serial* debug)
    {        
        int x = graded_in(src1);
        int y = graded_in(src2);
        
        char x_str[MAX_MSG_LEN];
        char y_str[MAX_MSG_LEN];
        
        tool::int_to_string(x, x_str);
        strcat(x_str, ";");
        tool::int_to_string(y, y_str);
        
        char output[MAX_MSG_LEN] = "";
        strcat(output, x_str);
        strcat(output, y_str);
        
        msg::out(dest, output);
        
        debug->printf("[%s]\n", output);
    }
}
    
#endif