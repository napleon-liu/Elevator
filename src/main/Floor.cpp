//
// Created by 79893 on 2022-10-29.
//
#include "../include/Floor.h"

Floor::Floor(int _floorNumber) :
   floorNumber(_floorNumber),
   waitingPsgNums(0),
   stayingPsgNums(0) {
   waitingPsgCtn.clear();
   stayingPsgCtn.clear();
}  // Floor的构造函数，初始时两种容器都为空

Floor::~Floor() {
   cout << "结束" << endl;
}

// 向存放等待电梯的乘客的容器中添加乘客
void Floor::addPsgtoWC(Passenger* psg) {
   waitingPsgCtn.push_back(psg);
}
// 向存放停留的乘客的容器中添加乘客
void Floor::addPsgtoSC(Passenger* psg) {
   stayingPsgCtn.push_back(psg);
}

// 楼层类的模拟，维护两个容器中的乘客
void Floor::f_simulation() {
//    // 对等待电梯的所有乘客进行模拟
//    for (auto ite : waitingPsgCtn) {
//
//    }
   // 对停留的所有乘客进行模拟
   for (auto ite = stayingPsgCtn.begin(); ite != stayingPsgCtn.end(); ite++) {
       Passenger* passenger = *ite;
       //乘客的状态
       PassengerState state = passenger->getState();
       // 如果乘客已经结束停留，则将其转移到等待电梯的容器，并为其分配合适的电梯
       if (state == WaitForElevatorArrive) {
           if(assignElevatorForPsg(passenger)) {
               addPsgtoWC(passenger);    // 将乘客转移至等待电梯的容器中
               stayingPsgCtn.erase(ite);   //将乘客从当前容器中删除
               ite--;
           }   // 为乘客分配合适的电梯
       }
   }
}

// 为结束停留的乘客重新分配电梯搭载
bool Floor::assignElevatorForPsg(Passenger *passenger) const {
   //  遍历10部电梯，寻找适合的电梯
   /*
   * 有三种情况的电梯符合要求:
   * 1. 电梯的当前位置低于本楼层，电梯的目的地高于本楼层
   * 2. 电梯的当前位置高于本楼层，电梯的目的地低于本楼层
   * 3. 电梯为空
   */
   for (Elevator* elevator : elevators) {
       // 如果存在合适的电梯，则将该电梯的ID传给乘客
       if (isSatisfied(elevator, passenger)) {
           passenger->setElevator(elevator->getID());
           elevator->setRequest(floorNumber);   // 向指定的电梯发出请求
           return true;
       }
   }
   // 如果十部电梯都不符合要求，返回false
   return false;
}

bool Floor::isSatisfied(Elevator *elevator, Passenger *passenger) {
   int evtFloor = elevator->getCurrFloor();    // 电梯的楼层
   int psgFloor = passenger->getcurrFloor();   // 乘客的楼层
   int evtDestination = elevator->getDestination();    //电梯的目的地
   int psgDestiantion = passenger->getDestination();   // 乘客的目的地
   if (evtFloor <= psgFloor && evtDestination >= psgDestiantion)
       return true;
   if (evtFloor >= psgFloor && evtDestination <= psgDestiantion)
       return true;
   if (elevator->getstate() == Stop)
       return true;
   return false;
}

// 处理在此层停留的电梯
bool Floor::handleArrivedEvt(int evtID) {
   bool response = false;
   Elevator* elevator = elevators[evtID-1];    // 到达的电梯
   for (auto iterator = waitingPsgCtn.begin(); iterator != waitingPsgCtn.end(); iterator++) {
       Passenger* passenger = *iterator;
       // 如果为该乘客分配的电梯ID与到达的电梯ID相同
       if (passenger->getEvtID() == evtID) {
           elevator->addPsg(passenger);    // 将该乘客加入电梯中
           passenger->setState(RunWithElevator);   //重新设置乘客的状态
           waitingPsgCtn.erase(iterator);  // 将该乘客从容器中删除
           iterator--;
           response = true;
       }
   }
   return response;
}
