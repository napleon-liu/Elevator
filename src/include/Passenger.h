#pragma once
#include<random>
#include<iostream>
#include "ConstValues.h"
using std::cout;
using std::cin;
using std::endl;
class Passenger {
private:
    int waitTime;   // 乘客发起请求后等待电梯的时间

    int destination;    // 乘客的目的楼层

    int currFloor;     // 乘客的当前所在的楼层

    int id;             // 乘客的ID

    int evtID;          // 为乘客分配的电梯的ID

    PassengerState state;   // 乘客在模拟过程中的状态

    int stayingTime;    // 乘客在某层的停留时间

    int currSmuTimes;   // 乘客当前的仿真次数

    int maxSmuTimes;    // 乘客的总仿真次数
public:

    void p_Simulation();    // 乘客的模拟过程

    int getDestination();   // 返回乘客的目的楼层信息

    int getcurrFloor();    // 返回乘客的当前楼层信息

    int getEvtID();         // 返回乘客乘坐的电梯的ID

    int getID();            // 返回乘客的ID

    Passenger(int _id); // 乘客的构造函数

    ~Passenger();

    void staySimulation();

    void waitSimulation();

    void runSimulation();

    void setDestination();

    PassengerState getState();

    void setElevator(int _evtID);

    void setState(PassengerState _state);

    void setCurrFloor(int _currFloor);

    int getStayingTime();

    int getCurrSmuTimes();

    int getMaxSmuTimes();

    int getWaitingTime() const;
};


