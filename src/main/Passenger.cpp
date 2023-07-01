#include "../include/Passenger.h"

// 所有乘客初始时均在一层
Passenger::Passenger(int _id) : currFloor(1), currSmuTimes(0), state(BeforeSimulation), id(_id) {
    maxSmuTimes = rand() % maxSimulationTimes + 1;  //  每位乘客的仿真次数在 1-10次之间
    // 为乘客随机分配电梯
    evtID = rand() % evtNums + 1;
    destination = rand() % floorNums + 1;
}

int Passenger::getDestination() {
    return this->destination;
}
int Passenger::getcurrFloor() {
    return this->currFloor;
}

Passenger::~Passenger() {}

int Passenger::getEvtID() {
    return this->evtID;
}

int Passenger::getID() {
    return this->id;
}

// 乘客的模拟过程
void Passenger::p_Simulation() {
    // 根据乘客现在不同的状态进行不同的模拟
    switch (state) {
            // 如果状态为开始模拟之前的话， 将状态转换为等待电梯到来
        case BeforeSimulation:
            state = WaitForElevatorArrive;
            break;
            //如果状态为随机停留的话，进行随机停留模拟
        case StayForRandomTime:
            staySimulation();
            break;
            // 进行等待电梯的模拟
        case WaitForElevatorArrive:
            waitSimulation();
            break;
            // 进行跟随电梯运行的模拟
        case RunWithElevator:
            runSimulation();
            break;
        case AfterSimulation:
            break;
        default:
            cout << "Unexpect Error." << endl;
            break;
    }
}

// 乘客在某层停留时的模拟
void Passenger::staySimulation() {
    // 如果结束了停留，则将状态改变为等待电梯，并为乘客重新分配目的地
    if (stayingTime > 0) {
        stayingTime--;
    }
}

// 乘客等待电梯时的模拟
void Passenger::waitSimulation() {
    ;
}

// 乘客跟随电梯运动时的模拟，实时更新乘客的楼层信息
void Passenger::runSimulation() {
//    Elevator* elevator = elevators[evtID-1];    // 乘客当前乘坐的电梯
//    this->currFloor = elevator->getCurrFloor(); //  乘客所处的楼层与其乘坐的电梯所处的楼层相同
    ;
}

// 为乘客分配目的地
void Passenger::setDestination() {
    // 如果已经达到最大仿真次数，直接结束仿真过程
    if (currSmuTimes == maxSmuTimes) {
        destination = 1;
        return ;
    }
    // 否则分配新的目的地
    do {
        destination = rand() % floorNums + 1;
    } while (destination != currFloor);
}

PassengerState Passenger::getState() {
    return state;
}

void Passenger::setElevator(int _evtID) {
    this->evtID = _evtID;
}

void Passenger::setState(PassengerState _state) {
    this->state = _state;
    // 如果乘客的状态更改为随机停留，则重新设置乘客的停留时间，乘客的模拟次数加一
    if (state == StayForRandomTime) {
        stayingTime = rand() % maxStayingTime + 1;
        currSmuTimes++;
    }
}

void Passenger::setCurrFloor(int _currFloor) {
    currFloor = _currFloor;
}

int Passenger::getStayingTime() {
    return stayingTime;
}

int Passenger::getCurrSmuTimes() {
    return currSmuTimes;
}

int Passenger::getMaxSmuTimes() {
    return maxSmuTimes;
}
