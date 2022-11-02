//
// Created by 79893 on 2022-10-29.
//
#pragma once
#include<iostream>

#ifndef ELEVATOR_TIMER_H
#define ELEVATOR_TIMER_H
class Timer {
private:
    int time;
    static Timer* instancePtr;  // 指向自身的实例(单例模式)
public:
    Timer();
    ~Timer();
    void showCurrTime();
    void setTime(const int time);
    static Timer* getInstance();
    int getTime() const;
    void increaseTime();
};
#endif //ELEVATOR_TIMER_H
