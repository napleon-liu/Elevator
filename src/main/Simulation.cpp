#include "../include/Building.h"
#include<windows.h>
#include<ctime>
#include "../include/Timer.h"
#include<memory>
void systemRun(Building* building);

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
    while (building->getPassengerNums()) {
        timer->showCurrTime();
        building->b_simulation();
        Sleep(1000);
        system("cls");
        timer->increaseTime();
    }
}