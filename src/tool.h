// 기관명: 한국기술교육대학교
// 교과목: 마이크로프로세서및실습
// 프로젝트: 로봇 축구
// 소속: 미정
// 구성원: 김성녕 | 임재경 | 임창민 | 조경우

// 도구 헤더: 편의 기능 정의.
// 의존성: -

#ifndef _TOOL_H
#define _TOOL_H

#ifndef MAX_MSG_LEN
#define MAX_MSG_LEN 40
#endif

#include "mbed.h"

namespace tool
{
    int get_int_length(int value)
    {
        int count = 0;
        for (int i = value; i > 0; i /= 10) count++;
        
        return count;
    }
    
    int string_to_int(char str[])
    {
        int value = 0;
        
        int index = 0;
        while (index < MAX_MSG_LEN && str[index])
        {
            value += str[index] - '0';
            value *= 10;
            
            index++;
        }
        
        return value / 10;
    }
    
    void int_to_string(int value, char dest[])
    {
        if (value == 0)
        {
            dest[0] = '0';
            dest[1] = '\0';
        }
        
        int digits = get_int_length(value);
        if (digits > MAX_MSG_LEN)
            return;
        
        dest[digits] = '\0';
        for (int i = digits - 1; i >= 0; i--)
        {
            dest[i] = value % 10 + '0';
            value /= 10;
        }
    }
}

#endif