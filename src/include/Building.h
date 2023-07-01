//
// Created by Napleon on 2022-10-18.
//

#ifndef ELEVATOR_BUILDING_H
#include "EvtCtrl.h"
#define ELEVATOR_BUILDING_H

class Building {
private:
    EvtCtrl* evtCtrl;
    vector<Passenger*>* psgs;
public:
    Building(int evtNums, int maxPsgNums, int floorNums);
    ~Building();
    vector<Passenger*>* genePsgs(EvtCtrl* evtCtrl, int evtNums, int maxPsgNums, int floorNums);
    EvtCtrl* getEvtCtrl();
    vector<Passenger*>* getPsgs();
};

#endif //ELEVATOR_BUILDING_H
