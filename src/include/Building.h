//
// Created by Napleon on 2022-10-18.
//
#pragma once
#ifndef ELEVATOR_BUILDING_H
#define ELEVATOR_BUILDING_H
#include "Elevator.h"
#include<algorithm>
class Building {
private:
    int psgNums;    //模拟过程中生成的总乘客数量
    vector<Elevator*> Elevators;
    vector<Passenger*> Passengers;
    vector<unsigned short> runningElevators;   // 记录每一时间下正在运行的电梯数目
public:
    Building();

    ~Building();

    void b_simulation();

    int genePsgs();

    void showData();

    bool allocateElevatorForPassenger(Passenger *passenger);

    int getPassengerNums();

    static bool isSatisfied(Elevator *elevator, Passenger *passenger);

    static void printState(ElevatorState state);

    static void printPassengers(Elevator* elevator);

    void showStatistics() const;

    vector<unsigned short > getStatistics();

    vector<Passenger*> getPsgs() const;
};

#endif
