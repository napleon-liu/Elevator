#include "../include/Elevator.h"

Elevator::Elevator() {
    this->passengers = new vector<Passenger*>;
    this->currFloor = 1;
    this->passengerNums = 0;
    this->direction = 1;
    this->status = 1;
    this->requests = 0;
}

Elevator::~Elevator() {
    delete this->passengers;
}

void Elevator::setPassengers(int floor, vector<Passenger*>* psgs) {
    // delete psg that arrive destination
    for (auto ite = this->passengers->begin(); ite != this->passengers->end();) {
        Passenger* psg = *ite;
        if (psg->getDestination() == floor) {
            cout << psg->getID() << " arrive " << psg->getDestination() << endl;
            this->passengers->erase(ite);
            this->setPassengerNums();
            delete psg;
        } else {
            ite++;
        }
    }
    // add new psg
    for (auto ite = psgs->begin(); ite < psgs->end();) {
        Passenger* psg = *ite;
        if (psg->getEvtID() == this->id && psg->getstartFloor() == this->currFloor) {
            cout << "Passenger" << psg->getID() << " enters elevator" << psg->getEvtID() << endl;
            this->passengers->push_back(psg);
            psgs->erase(ite);
            this->setReq(-1);
            this->setPassengerNums();
        } else {
            ite++;
        }
    }
}

void Elevator::setCurrFloor() {
    int dir = this->direction;
    if (dir == 1)   this->currFloor++;
    if (dir == -1)   this->currFloor--;
}

void Elevator::setPassengerNums() {
    this->passengerNums = this->passengers->size();
}

void Elevator::setStatus() {
    int psgNums = this->passengerNums;
    if (psgNums)   this->status = 1;
    if (!psgNums && this->currFloor != 1 && this->direction == -1)
        this->status = 0;
}

void Elevator::setDirection() {
    //get the highest floor
    int maxFloor = INT_MIN;
    for (auto psg : *this->passengers) {
        int destination = psg->getDestination();
        maxFloor = maxFloor > destination ? maxFloor : destination;
    }
    // if elevator has arrived the highest floor that passengers expect, then the elevator could down
    if (this->currFloor == maxFloor && this->requests == 0 || this->currFloor == 40)
        this->direction = -1;
}

void Elevator::setReq(int op) {
    this->requests += op;
}

void Elevator::showInfo() {
    cout << "Elevator " << id << " arrives the " << currFloor << " floor.\t";
    int psgNum = this->getPassengerNums();
    if (this->direction == 1)
        cout << "It is going up\t";
    else
        cout << "It is going down\t";
    cout << "It has " << psgNum << " passengers" << endl;
    cout << endl;
}

void Elevator::setID(int id) {
    this->id = id;
}

int Elevator::getCurrFloor() {
    return this->currFloor;
}

int Elevator::getPassengerNums() {
    return this->passengerNums;
}

int Elevator::getStatus() {
    return this->status;
}

int Elevator::getDirection() {
    return this->direction;
}

int Elevator::getID() {
    return this->id;
}

int Elevator::getReq() {
    return this->requests;
}

