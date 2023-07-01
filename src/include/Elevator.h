#pragma once
#include<string>
#include<vector>
//#include<queue>
#include "Passenger.h"
using std::string;
using std::vector;
//using std::priority_queue;
class Elevator {
private:
    friend class Passenger;
    // status of elevator 0 present empty, 1 present occupy
    int status;
    // 1 present up, -1 present down
    int direction;
    int currFloor;
    int passengerNums;
    int id;
    vector<Passenger*>* passengers;
    // generate request nums at the start of program
    int requests;
public:
     void setCurrFloor();           // 维护电梯当前所在楼层状态
     void setPassengerNums();       // 维护电梯中的乘客数目
     void setStatus();              // 维护电梯状态(是否空闲)
     void setDirection();           // 维护电梯的方向
     void setPassengers(int floor, vector<Passenger*>* psgs);   // 维护电梯中的乘客状态
     void setID(int id);            // 设置电梯的ID
     void setReq(int op);
     int getID();                   // 返回电梯的ID
     int getCurrFloor();            // 返回电梯的当前楼层
     int getPassengerNums();        // 返回乘客的数目
     int getStatus();               // 返回电梯的状态
     int getDirection();
     int getReq();
     void showInfo();               // 展示电梯中的信息
    Elevator();                     // 电梯的构造函数
    ~Elevator();
};