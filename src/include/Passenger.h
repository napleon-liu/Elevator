#pragma once
#include<random>
#include<ctime>
#include<iostream>
using std::cout;
using std::cin;
using std::endl;
class Passenger {
private:
    int destination;    // 乘客的目的楼层
    int startFloor;     // 乘客的初始楼层
    int id;             // 乘客的ID
    int evtID;          // 为乘客分配的电梯的ID
public:
    int getDestination();   // 返回乘客的目的楼层信息
    int getstartFloor();    // 返回乘客的初始楼层信息
    int getEvtID();         // 返回为乘客分配的电梯的ID
    int getID();            // 返回乘客的ID

    Passenger(int evtNums, int floorNums, int id); // 乘客的构造函数
    ~Passenger();
};

