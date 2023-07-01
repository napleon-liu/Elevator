//
// Created by Napleon on 2022-10-18.
//
#include "../include/Building.h"
Building::Building(int evtNums, int maxPsgNums, int floorNums) {
   this->evtCtrl = new EvtCtrl(evtNums);
   this->psgs =  genePsgs(evtCtrl, evtNums, maxPsgNums, floorNums);
}


Building::~Building() {
    delete this->evtCtrl;
    delete this->psgs;
}

vector<Passenger*>* Building::genePsgs(EvtCtrl* evtCtrl, int evtNums, int maxPsgNums, int floorNums) {
    int psgNums = rand() % maxPsgNums;
    auto* psgs = new vector<Passenger*>(psgNums);
    cout << "Generate" << " " << psgNums << " passengers successfully" << endl;
    for (int i = 0; i < psgNums; i++) {
        auto* passenger = new Passenger(evtNums, floorNums, i + 1);
        // relate psg and his evt
        int evtID = passenger->getEvtID();
        for (Elevator* evt : *this->evtCtrl->getEvts()) {
            int id = evt->getID();
            if (id == evtID) {
                evt->setReq(1);
            }
        }
        psgs->at(i) = passenger;
    }
    return psgs;
}

EvtCtrl* Building::getEvtCtrl() {
    return this->evtCtrl;
}

vector<Passenger*>* Building::getPsgs() {
    return this->psgs;
}
