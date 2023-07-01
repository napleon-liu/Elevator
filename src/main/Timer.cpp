//
// Created by 79893 on 2022-10-29.
//

#include "../include/Timer.h"

Timer *Timer::instancePtr = 0;

Timer::Timer() : time(0) {};

Timer::~Timer() {};

void Timer::showCurrTime() {
    std::cout << "Current time: " <<  time << std::endl;
}

void Timer::increaseTime() {
    time++;
}

// 返回实例
Timer* Timer::getInstance() {
    if (!instancePtr) {
        instancePtr = new Timer;
    }

    return instancePtr;
}

int Timer::getTime() const {
    return time;
}

void Timer::setTime(const int time) {
    this->time = time;
}
