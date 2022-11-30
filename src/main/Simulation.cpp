#include "../include/Building.h"
#include<windows.h>
#include "../include/Timer.h"
#include<memory>
#include<algorithm>
#include<fstream>
void systemRun(Building *building);
void write(vector<unsigned short> statistics);

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
        system("cls");
        timer->increaseTime();
    }
    vector<unsigned short > statistics = building->getStatistics();
    building->showStatistics();
//    system("cls");
//    system("pause");
//    write(statistics); 记录数据
    system("pause");
}

//void write(vector<unsigned short> statistics) {
//    std::ofstream ofs("statistics.txt", std::ios::out);
//    std::cout.clear();
//    if (!ofs.is_open()) {
//        cout << "ERROR" << endl;
//    }
//    for (int i = 0; i < statistics.size() - 1; i++) {
//        ofs << statistics[i] << ",";
//    }
//    ofs << statistics[statistics.size() - 1] << endl;
//    ofs.close();
//}