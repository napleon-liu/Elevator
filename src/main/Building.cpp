//
// Created by Napleon on 2022-10-18.
//
#include "../include/Building.h"

Building::Building() {
    // 逐一生成编号为 0 - evtNums - 1 的所有电梯
    for (int index = 0; index < evtNums; index++) {
        auto elevator = new Elevator(index + 1);
        Elevators.push_back(elevator);
    }
    int psgNums = genePsgs(); // 生成乘客
}

// 建筑的析构函数，释放构造函数中分配的内存
Building::~Building() {
    while (!Elevators.empty()) {
        delete *Elevators.begin();
    }
}

// 生成一定数目的乘客
// 当前情况为： 乘客一次性到达建筑的第一层，并为其分配电梯
int Building::genePsgs() {
    // 生成随机数目的乘客
    int psgNums = rand() % maxPsgNums + 1;
    cout << "generate " << " " << psgNums << " passengers successfully" << endl;
    // 生成编号为 1 - maxPsgNums 的乘客
    for (int i = 0; i < psgNums; i++) {
        auto *passenger = new Passenger(i + 1);
        Passengers.push_back(passenger);
    }
    return psgNums;
}


// 建筑的模拟过程
void Building::b_simulation() {
    // 对所有elevator都模拟
    for (auto elevator: Elevators) {
        elevator->e_Simulation();   // 更新所有电梯的状态
    }
    // 对所有的乘客进行模拟
    for (auto iterator = Passengers.begin(); iterator != Passengers.end(); iterator++) {
        Passenger *passenger = *iterator;
        passenger->p_Simulation();  // 更新乘客的状态
        PassengerState psgstate = passenger->getState();    //获取到乘客的状态
        int stayingTime = passenger->getStayingTime();    // 获取乘客的停留时间
        int evtID = passenger->getEvtID();  //获取乘客希望乘坐的电梯的ID
        int evtCurrFloor = Elevators[evtID-1]->getCurrFloor();  // 获取到电梯的当前楼层
        int psgCurrFloor = passenger->getcurrFloor();   //获取乘客的当前楼层
        // 乘客已经结束停留
        if (psgstate == StayForRandomTime && stayingTime == 0) {
            if (allocateElevatorForPassenger(passenger))  // 为乘客分配合适的电梯，如果成功分配，则重新设置乘客的状态
                passenger->setState(WaitForElevatorArrive); // 重新设置乘客的状态
        }
        // 如果乘客的电梯已经到达，将乘客加入电梯内
        else if (psgstate == WaitForElevatorArrive && evtCurrFloor == psgCurrFloor) {
            passenger->setState(RunWithElevator);   // 重新设置乘客的状态
            Elevators[evtID - 1]->addPsg(passenger);  // 将乘客加入到电梯中
        }

        // 如果乘客的状态为已经结束模拟
        else if (psgstate == AfterSimulation) {
            ;
        }

    }
    // 展示模拟信息面板
    showData();
    // 统计正在运行的电梯数目;
    unsigned short amount = std::count_if(Elevators.begin(), Elevators.end(),[](const Elevator* elevator){return elevator->getState() != Stop;});
    runningElevators.push_back(amount);
}

// 为乘客分配合适的电梯， 并向电梯发送请求
bool Building::allocateElevatorForPassenger(Passenger *passenger) {
    //  遍历10部电梯，寻找适合的电梯
    /*
    * 有三种情况的电梯符合要求:
    * 1. 电梯的当前位置低于本楼层，电梯的目的地高于本楼层
    * 2. 电梯的当前位置高于本楼层，电梯的目的地低于本楼层
    * 3. 电梯为停止状态
    */
    // 如果存在合适的电梯，则将该电梯的ID传给乘客
    vector<Elevator*> qualified;
    for (Elevator *elevator: Elevators) {
        if (isSatisfied(elevator, passenger)) {
            qualified.push_back(elevator);
        }
    }
    if (qualified.size() != 0) {
        std::sort(qualified.begin(), qualified.end(),
                  [passenger](Elevator *ele1, Elevator *ele2) {
                      return ele1->distance(passenger) < ele2->distance(passenger);
                  });
        Elevator* elevator = qualified[0];
        passenger->setElevator(elevator->getID());
        int floorNumber = passenger->getcurrFloor();
        elevator->setRequest(floorNumber);   // 向指定的电梯发出请求
        return true;
    }
    return false;
}


// 判断电梯是否满足
// 上机要求三：不同的电梯所能到达的楼层不同
bool Building::isSatisfied(Elevator *elevator, Passenger *passenger) {
    int evtID = elevator->getID();  //  电梯的ID
    int evtFloor = elevator->getCurrFloor();    // 电梯的楼层
    int psgFloor = passenger->getcurrFloor();   // 乘客的楼层
    int evtDestination = elevator->getDestination();    //电梯的目的地
    int psgDestiantion = passenger->getDestination();   // 乘客的目的地
    // 如果乘客的目的地电梯能够到达
    if (Elevator::arrivedTable[evtID - 1][psgDestiantion - 1]) {
        if (evtFloor <= psgFloor && evtDestination >= psgDestiantion)
            return true;
        if (evtFloor >= psgFloor && evtDestination <= psgDestiantion)
            return true;
        if (elevator->getstate() == Stop)
            return true;
    }
    return false;
}

int Building::getPassengerNums() {
    return std::count_if(Passengers.begin(), Passengers.end(), [](Passenger* p){return p->getState() != AfterSimulation;});
}


void Building::showData() {
    cout << "/*************************ElevatorSimulation*************************/" << endl;
    cout << "passenger numbers in simulation: " << this->getPassengerNums() << endl;
    cout << "Elevator ID\t" << "Elevator state" << "\t" << "passengers" << "\t" << "current floor number"
         << endl;
    for (auto elevator: Elevators) {
        ElevatorState state = elevator->getstate();
        cout << elevator->getID() << "\t\t\t";
        printState(state);
        cout << "\t\t" ;
        printPassengers(elevator);
        cout << "\t\t\t"
             << elevator->getCurrFloor() << endl;

        cout << "-------------------------------------------------------------------" << endl;
    }

    cout << "/*************************ElevatorSimulation*************************/" << endl;
}

void Building::printState(ElevatorState state) {
    switch (state) {
        case GoUp:  cout << "GoUp";
            break;
        case GoDown: cout << "GoDown";
            break;
        case Stay: cout << "Stay";
            break;
        case Stop: cout << "Stop";
            break;
        default: cout << "Other State";
            break;
    }
}

void Building::printPassengers(Elevator* elevator) {
    for (auto passenger : elevator->getPassengers()) {
        cout << passenger->getID() << ' ';
    }
}

vector<Passenger*> Building::getPsgs() const {
    return this->Passengers;
}

void Building::showStatistics() const {
    cout << "/*************************Elevators Statistics*************************/" << endl;
    cout << "\t" <<"Running Time" << "\t\t" << "Stopping Time" "\t\t\n";
    for (auto elevator : this->Elevators) {
        cout << "Elevator" << elevator->getID();
        cout << "\t" << elevator->getRunningTime() << "\t\t" << elevator->getStoppingTime() << "\t\t" << endl;
    }
    cout << "/*************************Elevators Statistics*************************/" << endl;
    cout << endl << endl;
    cout << "/*************************Passengers Statistics*************************/" << endl;
    cout << "\t" << "Waiting Time" << "\t\t" << endl;
    for (auto passenger : this->Passengers) {
        cout << "Passenger" << passenger->getID();
        cout << "\t\t" << passenger->getWaitingTime() << "\t\t" <<  endl;
    }
    cout << "/*************************Passengers Statistics*************************/" << endl;

}

vector<unsigned short> Building::getStatistics() {
    return runningElevators;
}
