// 기관명: 한국기술교육대학교
// 교과목: 마이크로프로세서및실습
// 프로젝트: 로봇 축구
// 소속: 미정
// 구성원: 김성녕 | 임재경 | 임창민 | 조경우

// 모터 헤더: 스테핑 모터 구동 정의.
// 의존성: -

#ifndef _MTR_H
#define _MTR_H

#include "mbed.h"

namespace mtr
{
    int get_move_dir(int raw_level)
    {
        int f_condition = 0 <= raw_level && raw_level <= 120;
        
        return f_condition ? 0 : 1;
    }
    
    double get_move_level(int raw_level)
    {
        int f_condition = 0 <= raw_level && raw_level <= 120;
        int b_condition = 140 <= raw_level && raw_level <= 255;
        
        return f_condition || b_condition ? 0.5 : 0.0;
    }
    
    void move(DigitalOut* motor_en, PwmOut* left, DigitalOut* left_rotate, PwmOut* right, DigitalOut* right_rotate, int raw_level)
    {
        int dir = get_move_dir(raw_level);
        float level = get_move_level(raw_level);
        
        if (level == 0)
        {
            *motor_en = 0;
        }
        else
        {
            *motor_en = 1;
        }
        
        // 전진.
        if (dir == 0)
        {
            *left_rotate = 1;
            *right_rotate = 0;
        }
        
        // 후진.
        else if (dir == 1)
        {
            *left_rotate = 0;
            *right_rotate = 1;
        }
        
        left->write(level);
        left->period_ms(10);
        right->write(level);
        right->period_ms(10);
    }
    
    int get_turn_dir(int raw_dir)
    {
        int left = 0 <= raw_dir && raw_dir < 120;
        
        return left ? 0 : 1;
    }
    
    void turn(DigitalOut* motor_en, PwmOut* left, DigitalOut* left_rotate, PwmOut* right, DigitalOut* right_rotate, int raw_dir)
    {
        int dir = get_turn_dir(raw_dir);
        
        *motor_en = 1;
        
        // 좌회전.
        if (dir == 0)
        {
            *left_rotate = 0;
            *right_rotate = 0;
        }
        
        // 우회전.
        else if (dir == 1)
        {
            *left_rotate =1;
            *right_rotate = 1;
        }
        
        left->write(0.5);
        left->period_ms(10);
        right->write(0.5);
        right->period_ms(10);
    }
}
    
#endif