#include "../include/Building.h"
#include<cstdlib>
#include<windows.h>
#define floorNums 40
#define evtNums 10
#define maxPsgNums 100
vector<Passenger*>* genePsgs(EvtCtrl* evtCtrl);
void systemRun(EvtCtrl* evtCtrl, vector<Passenger*>* psgs);
string getTime()
{
    time_t timep;
    time (&timep); //获取time_t类型的当前时间
    char tmp[64];
    strftime(tmp, sizeof(tmp), "%Y-%m-%d %H:%M:%S",localtime(&timep) );//对日期和时间进行格式化
    return tmp;
}

int main() {
    // 设置随机数
    srand(time(0));
    //生成建筑、电梯和乘客
    Building* building = new Building(evtNums, maxPsgNums, floorNums);
    EvtCtrl* evtCtrl = building->getEvtCtrl();
    vector<Passenger*>* psgs = building->getPsgs();
    systemRun(evtCtrl, psgs);
    return 0;
}

// 程序的主过程
void systemRun(EvtCtrl* evtCtrl, vector<Passenger*>* psgs) {
    while (!psgs->empty() || evtCtrl->getPsgNums()) {
        string time = getTime();
        cout << time << endl;
        evtCtrl->showAllEvtInfo(psgs);
        evtCtrl->setEvts();
        evtCtrl->setPsgNums();
        Sleep(2000);
        system("cls");
    }
}