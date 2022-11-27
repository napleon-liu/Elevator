#include "../include/Elevator.h"

int Elevator::gapTime = maxGapTime;

bool Elevator::arrivedTable[10][40] = {
        {
            true,true,true,true,true,true,true,true,true,true,
            true,true,true,true,true,true,true,true,true,true,
            true,true,true,true,true,true,true,true,true,true,
            true,true,true,true,true,true,true,true,true,true,},
        {
            true,true,true,true,true,true,true,true,true,true,
            true,true,true,true,true,true,true,true,true,true,
            true,true,true,true,true,true,true,true,true,true,
            true,true,true,true,true,true,true,true,true,true,
            },
        {
                true,false,false,false,false,false,false,false,false,false,
                false,false,false,false,false,false,false,false,false,false,
                false,false,false,false,true,true,true,true,true,true,
                true,true,true,true,true,true,true,true,true,true,
            },
        {
                true,false,false,false,false,false,false,false,false,false,
                false,false,false,false,false,false,false,false,false,false,
                false,false,false,false,true,true,true,true,true,true,
                true,true,true,true,true,true,true,true,true,true,
            },
        {
                true,true,true,true,true,true,true,true,true,true,
                true,true,true,true,true,true,true,true,true,true,
                true,true,true,true,true,false,false,false,false,false,
                false,false,false,false,false,false,false,false,false,false,
            },
        {
                true,true,true,true,true,true,true,true,true,true,
                true,true,true,true,true,true,true,true,true,true,
                true,true,true,true,true,false,false,false,false,false,
                false,false,false,false,false,false,false,false,false,false,
            },
        {
                true,true,false,true,false,true,false,true,false,true,
                false,true,false,true,false,true,false,true,false,true,
                false,true,false,true,false,true,false,true,false,true,
                false,true,false,true,false,true,false,true,false,true,
            },
        {
                true,true,false,true,false,true,false,true,false,true,
                false,true,false,true,false,true,false,true,false,true,
                false,true,false,true,false,true,false,true,false,true,
                false,true,false,true,false,true,false,true,false,true,
            },
        {
                true,false,true,false,true,false,true,false,true,
                false,true,false,true,false,true,false,true,false,true,
                false,true,false,true,false,true,false,true,false,true,
                false,true,false,true,false,true,false,true,false,true,false,
            },
        {
                true,false,true,false,true,false,true,false,true,
                false,true,false,true,false,true,false,true,false,true,
                false,true,false,true,false,true,false,true,false,true,
                false,true,false,true,false,true,false,true,false,true,false,
            },
};

Elevator::Elevator(int _id) : id(_id), currFloor(1), direction(DirectionStay), state(Stop),
                              passTime(0), destination(1),
                              runTime(0), stopTime(0){
    // 一楼对电梯有请求
    requests.push_back(1);
}

Elevator::~Elevator() {
    cout << "电梯" << id << " 已经结束运行";
}

int Elevator::getCurrFloor() const {
    return this->currFloor;
}


ElevatorState Elevator::getstate() {
    return this->state;
}

int Elevator::getID() const {
    return this->id;
}


// 向电梯中添加新的乘客
void Elevator::addPsg(Passenger *pPassenger) {
    passengers.push_back(pPassenger);
}

int Elevator::getDestination() const {
    return destination;
}

// 电梯的模拟过程，根据电梯的状态模拟
void Elevator::e_Simulation() {
    switch (state) {
        case GoUp:
            goUpSimulation();
            break;
        case GoDown:
            goDownSimulation();
            break;
        case Stop:
            StopSimulation();
            break;
        case Stay:
            StaySimulation();
            break;
        default:
            cout << "Unexpected Error." << endl;
    }
}

// 电梯处于向上状态时的模拟
void Elevator::goUpSimulation() {
    runTime++;
    if (this->passengers.size() == 0 && this->requests.size() == 0) {
        state = Stop;
    }
    // 如果电梯在两层之间已经运行的时间小于需要的时间
    if (passTime < gapTime) {
        passTime++; //继续运行
    } else{
        currFloor++;
        passTime = 0;
        // 如果到达了某位乘客的目的地或者该楼层中有人发起请求，则停下来
        if (existReq() || isDestination()) {
            this->state = Stay;
        }
    }
    // 更新所有乘客的当前所在楼层信息
    for (auto passenger: passengers) {
        passenger->setCurrFloor(currFloor);
    }
    if (currFloor == 40 && state == GoUp) {
        state = GoDown;
    }
}

void Elevator::goDownSimulation() {
    runTime++;
    if (this->passengers.size() == 0 && this->requests.size() == 0) {
        state = Stop;
    }
//    if (currFloor <= 0) {
//        state = Stop;
//        return ;
//    }
    // 如果电梯在两层之间已经运行的时间小于需要的时间
    if (passTime < gapTime) {
        passTime++; //继续运行
    }
        // 等于
    else {
        currFloor--;
        passTime = 0;
        // 如果到达了某位乘客的目的地或者该楼层中有人发起请求，则停下来
        if (existReq() || isDestination()) {
            this->state = Stay;
        }
    }
    // 更新所有乘客的当前所在楼层信息
    for (auto passenger: passengers) {
        passenger->setCurrFloor(currFloor);
    }
    if (currFloor == 1 && state == GoDown) {
        state = GoUp;
    }
}

// 电梯在某层停留时的模拟
void Elevator::StaySimulation() {
    runTime++;
//    Floor floor = *floors[currFloor - 1];
    // 如果有乘客到达了目的地
    for (auto iterator = passengers.begin(); iterator != passengers.end(); iterator++) {
        Passenger *passenger = *iterator;
        if (passenger->getDestination() == currFloor) {
//            floor.addPsgtoSC(passenger);    // 将该乘客加入该楼层中
            passengers.erase(iterator); // 将该乘客从电梯中删除
            passenger->setState(StayForRandomTime); // 重新设置乘客的状态
            if (passenger->getCurrSmuTimes() > passenger->getMaxSmuTimes()) {
                passenger->setState(AfterSimulation);
            }
            iterator--;
        }
    }
    // 如果该楼层中有人发起请求，删除请求
    for (auto iterator = requests.begin(); iterator != requests.end(); iterator++) {
        if (*iterator == currFloor) {
            requests.erase(iterator);
            break;
        }
    }
    // 停留之后，根据电梯是否到达了目的地调整电梯的状态
    if (currFloor == destination) {
        //检查乘客是否为空
        // 所有乘客均已经到达目的地电梯设置为停止
        if (passengers.empty()) {
            state = Stop;
            direction = DirectionStay;
        }
            // 电梯中仍然有乘客，根据乘客的目的地选择新的目的地
        else {
            if (passengers[passengers.size()-1]->getDestination() > currFloor) {
                destination = passengers[passengers.size()-1]->getDestination();
                state = GoUp;
                direction = DirectionUp;
            }
            if (passengers[passengers.size()-1]->getDestination() < currFloor) {
                destination = passengers[passengers.size()-1]->getDestination();
                state = GoDown;
                direction = DirectionDown;
            }
        }
    }
        //未到达目的地，不改变方向，继续前进
    else if (destination > currFloor) state = GoUp;
    else state = GoDown;
}

// 电梯停止运行时的模拟
void Elevator::StopSimulation() {
    stopTime++;
    passTime = 0;
    // 检查是否有请求，有请求则前往请求地点
    if (!requests.empty()) {
        if (requests[requests.size()-1] == currFloor) {
            state = Stay;
            direction = DirectionStay;
        } else if (requests[requests.size()-1] > currFloor) {
            state = GoUp;
            direction = DirectionUp;
        } else {
            state = GoDown;
            direction = DirectionDown;
        }
    }
}

void Elevator::setRequest(int floorNumber) {
    for (auto item: requests) {
        if (item == floorNumber)
            return;
    }
    requests.push_back(floorNumber);
}

// 判断当前楼层是否有人发起请求
bool Elevator::existReq() {
    for (auto request: requests)
        if (request == currFloor)
            return true;
    return false;
}

// 判断当前楼层是否为某位乘客的目的地
bool Elevator::isDestination() {
    for (auto passenger: passengers) {
        if (passenger->getDestination() == currFloor) {
            return true;
        }
    }
    return false;
}

vector<Passenger *> Elevator::getPassengers() {
    return passengers;
}

int Elevator::getRunningTime() const {
    return runTime;
}

int Elevator::getStoppingTime() const {
    return stopTime;
}

int Elevator::distance(Passenger *pPassenger) {
    return abs(currFloor - pPassenger->getcurrFloor());
}

