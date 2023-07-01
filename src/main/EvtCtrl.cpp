#include "../include/EvtCtrl.h"

EvtCtrl::EvtCtrl(int evtNums) {
    this->psgNums = 0;
    this->evts = new vector<Elevator*>(evtNums); // init ElevatorController instance
    for (int i = 0; i < this->evts->size(); i++) {
        this->evts->at(i) = new Elevator;
    }
    for (int i = 0; i < this->evts->size(); i++) {
        this->evts->at(i)->setID(i + 1);
    }
}

EvtCtrl::~EvtCtrl() {
    delete this->evts;
}

void EvtCtrl::setAllPsgs(vector<Passenger*>* psgs) {
    for(auto evt : *this->evts) {
        int floor = evt->getCurrFloor();
        int id = evt->getID();
        evt->setPassengers(floor, psgs);
    }
}

void EvtCtrl::setPsgNums() {
    int result = 0;
    for (auto evt : *this->evts) {
        result += evt->getPassengerNums();
    }
    this->psgNums = result;
}

int EvtCtrl::getPsgNums() {
    return this->psgNums;
}

void EvtCtrl::setEvts() {
    for (auto evt : *this->evts) {
        evt->setCurrFloor();
        evt->setDirection();
        evt->setPassengerNums();
        evt->setStatus();
    }
}

void EvtCtrl::showAllEvtInfo(vector<Passenger*>* psgs) {
    vector<Elevator*>* evts = this->evts;
    // show info of every evt by iterator
    for (auto iterator = evts->begin(); iterator < evts->end();) {
        Elevator* evt = *iterator;
        if (evt->getStatus() == 0) {
            cout << "Elevator " << evt->getID() << " ends" << endl;
            evts->erase(iterator);
        } else {
            int floor = evt->getCurrFloor();
            evt->setPassengers(floor, psgs);
            evt->showInfo();
            iterator++;
        }
    }
}

vector<Elevator*>* EvtCtrl::getEvts() {
    return this->evts;
}