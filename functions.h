#pragma once

#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdlib>
#include <ctime>

using namespace std;

class Elevator {
public:
    int id;
    int currentFloor;
    vector<int> requests;
    bool goingUp;
    int timeElapsed;

    Elevator(int id) : id(id), currentFloor(0), goingUp(true), timeElapsed(0) {}

    void addRequest(int floor) {
        if (find(requests.begin(), requests.end(), floor) == requests.end()) {
            requests.push_back(floor);
            sortRequests();
        }
    }

    void sortRequests() {
        if (goingUp) {
            sort(requests.begin(), requests.end());
        }
        else {
            sort(requests.begin(), requests.end(), greater<int>());
        }
    }

    bool shouldAccept(int floor) {

        if (requests.empty()) {
            return true; 
        }
 
        if (goingUp && floor >= currentFloor) {
            return true;
        }
        else if (!goingUp && floor <= currentFloor) {
            return true;
        }
        return false; 
    }

    bool move() {
        if (requests.empty()) return false;
        int nextFloor = requests.front();

        
        goingUp = nextFloor > currentFloor;

        int travelTime = abs(nextFloor - currentFloor) * 2;  
        int waitTime = nextFloor == currentFloor ? 10 : travelTime + 10;  

        if (nextFloor == currentFloor) {
            cout << "Elevator " << id << " already on requested floor " << currentFloor << ". Holding the elevator for " << waitTime << " additional seconds." << endl << endl;
        }
        else {
            cout << "Elevator " << id << " is moving from floor " << currentFloor << " to floor " << nextFloor << " (" << (goingUp ? "Up" : "Down") << "). ";
            cout << waitTime << " seconds to reach floor " << nextFloor << endl << endl;
        }

        timeElapsed += waitTime;
        currentFloor = nextFloor;
        requests.erase(requests.begin());
        return true;
    }

    bool isIdle() {
        return requests.empty();
    }
};

class ElevatorController {
private:
    Elevator elevator1, elevator2;

    void assignRequest(int floor) {
        bool e1ShouldAccept = elevator1.shouldAccept(floor);
        bool e2ShouldAccept = elevator2.shouldAccept(floor);

        if (e1ShouldAccept && (!e2ShouldAccept || abs(elevator1.currentFloor - floor) <= abs(elevator2.currentFloor - floor))) {
            elevator1.addRequest(floor);
        }
        else if (e2ShouldAccept) {
            elevator2.addRequest(floor);
        }
        else {
            if (abs(elevator1.currentFloor - floor) < abs(elevator2.currentFloor - floor)) {
                elevator1.addRequest(floor);
            }
            else {
                elevator2.addRequest(floor);
            }
        }
    }

public:
    ElevatorController() : elevator1(1), elevator2(2) {}

    void addRequest(int floor) {
        cout << "Request received for floor " << floor << "." << endl;
        assignRequest(floor);
        operateElevators();
    }

    void operateElevators() {
        bool moved = false;
        do {
            moved = elevator1.move() || elevator2.move();
        } while (moved);
    }
};

void simulateElevatorOperation(int numFloors) {
    ElevatorController controller;
    srand(time(NULL)); 

    for (int i = 0; i < 10; i++) {
        int randomFloor = rand() % numFloors;
        controller.addRequest(randomFloor);
    }
}