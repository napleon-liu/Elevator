//
// Created by Napleon on 2022-10-18.
//

#ifndef ELEVATOR_BUILDING_H
#define ELEVATOR_BUILDING_H
#include "Elevator.h"
class Building {
private:
    int psgNums;    //模拟过程中生成的总乘客数量
    vector<Elevator*> Elevators;
    vector<Passenger*> Passengers;
public:
    void b_simulation();
    Building();
    ~Building();
    int genePsgs();
    int getPsgs();

    void showData();

    bool allocateEvtForPsg(Passenger *passenger);

    static bool isSatisfied(Elevator *elevator, Passenger *passenger);

    int getPsgNums();

    static void printState(ElevatorState state);

    static void printPassengers(Elevator* elevator);
};

#endif
