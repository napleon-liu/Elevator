#include "../include/Passenger.h"

Passenger::Passenger(int evtNums, int floorNums, int  id) {
    this->startFloor = rand() % floorNums + 1;
    this->destination = rand() % floorNums + 1;
    // avoid startFloor == destination
    while (this->destination == this->startFloor) {
        this->destination = rand() % floorNums + 1;
    }
    this->id = id;
    this->evtID = rand() % evtNums + 1;
}

int Passenger::getDestination() {
    return this->destination;
}
int Passenger::getstartFloor() {
    return this->startFloor;
}

Passenger::~Passenger() {
    ;
}

int Passenger::getEvtID() {
    return this->evtID;
}

int Passenger::getID() {
    return this->id;
}
