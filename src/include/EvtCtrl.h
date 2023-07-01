#pragma once
#include "Elevator.h"
using std::vector;
class EvtCtrl {
    friend class Passenger;
private:
    // 电梯对象数组
    vector<Elevator*>* evts;
    // 电梯中的乘客数目
    int psgNums;
public:
    // 电梯控制器的构造函数，传入电梯的数目，生成有对应数目电梯的对象数组
    EvtCtrl(int evtNums);
    // 电梯控制器的析构函数，销毁电梯对象数组
    ~EvtCtrl();
    // 维护电梯成员数目
    void setPsgNums();
    // 请求电梯成员数目
    int getPsgNums();
    // 维护乘客状态
    void setAllPsgs(vector<Passenger*>* psgs);
    // 维护所有电梯状态
    void setEvts();
    // 展示电梯信息
    void showAllEvtInfo(vector<Passenger*>* psgs);
    // 请求电梯对象数组
    vector<Elevator*>* getEvts();
};