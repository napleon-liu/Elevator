////
//// Created by 79893 on 2022-10-29.
////
//#pragma once
//#include<vector>
//#include "Passenger.h"
//#include "Elevator.h"
//using std::vector;
//#ifndef ELEVATOR_FLOOR_H
//#define ELEVATOR_FLOOR_H
//class Floor {
//    // 乘客是楼层类的友元类
//    friend class Passenger;
//    friend class Elevator;
//private:
//    // 每层楼层都能了解正在运行的电梯的情况
//    static vector<Elevator*> elevators;
//    int floorNumber;    // 楼层号
//    vector<Passenger*> waitingPsgCtn;   // 存放等待电梯的乘客的容器
//    vector<Passenger*> stayingPsgCtn;   // 存放停留的乘客的容器
//    int waitingPsgNums; // 本层中等待电梯的乘客的数量
//    int stayingPsgNums; // 本层中停留的乘客的数量
//public:
//    Floor(int _floorNumber); // 构造函数，传入楼层的编号
//    ~Floor();   // 析构函数
//    void addPsgtoWC(Passenger* psg);    // 向存放等待电梯的乘客的容器中添加乘客
//    void addPsgtoSC(Passenger* psg);    // 向存放停留的乘客的容器中添加乘客
//    void f_simulation();
//
//    bool assignElevatorForPsg(Passenger *passenger) const;
//
//    static bool isSatisfied(Elevator *elevator, Passenger *passenger);
//
//    bool handleArrivedEvt(int evtID);
//};
//#endif //ELEVATOR_FLOOR_H