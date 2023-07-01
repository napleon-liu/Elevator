#pragma once
#include "Passenger.h"

using std::string;
using std::vector;

//using std::priority_queue;
class Elevator {
private:
//    static vector<Floor*> floors;
    ElevatorState state;    // 电梯的状态
    Direction direction;    // 电梯的方向
    int passTime;   // 电梯在两层之间已经运行的时间
    int gapTime;    // 电梯在两层之间的运行时间
    int currFloor;          // 电梯当前的楼层
//    int passengerNums;      // 电梯中的乘客数量
    int id;                 // 电梯的编号
    int destination;    // 电梯的目的地
    vector<Passenger*> passengers;  // 电梯中的乘客数量
    vector<int> requests;        // 电梯接收到的请求的楼层
public:

    Elevator(int _id);                     // 电梯的构造函数

    ~Elevator();

    void e_Simulation();    // 电梯的模拟过程

    int getID() const;                   // 返回电梯的ID

    int getCurrFloor() const;            // 返回电梯的当前楼层

    ElevatorState getstate();               // 返回电梯的状态

    void addPsg(Passenger *pPassenger); // 添加新的乘客

    int getDestination() const;

    void goUpSimulation();

    void goDownSimulation();

    void StaySimulation();

    void StopSimulation();

    void setRequest(int floorNumber);

    bool existReq();

    bool isDestination();

    int getPsgNums();

    vector<Passenger *> getPassengers();
};

