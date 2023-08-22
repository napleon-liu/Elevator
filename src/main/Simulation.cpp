#include "../include/Building.h"
#include<windows.h>
#include "../include/Timer.h"
#include<memory>
#include<algorithm>
#include <ctime>
void systemRun(Building *building);

int main() {
    // 设置随机数
    srand(time(0));
    //生成建筑、电梯和乘客
    auto* building = new Building();
    systemRun(building);
    return 0;
}

// 程序的主过程
void systemRun(Building* building) {
    Timer* timer = Timer::getInstance();
    vector<Passenger*> passengers = building->getPsgs();
    while (std::any_of(passengers.begin(), passengers.end(), [](Passenger *p){ return p->getState() != AfterSimulation;})) {
        timer->showCurrTime();
        building->b_simulation();
        Sleep(500);
        system("cls");
        timer->increaseTime();
    }
    building->showStatistics();
    system("pause");
}