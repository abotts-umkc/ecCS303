#pragma once

#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdlib>
#include <ctime>

using namespace std;

class Elevator {
private:
    int currentFloor;
    vector<int> requests;
    bool goingUp;

public:
    Elevator() : currentFloor(0), goingUp(true) {}

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

    void moveElevator() {
        if (requests.empty()) return;

        bool requestServed = false;
        if (goingUp) {
            for (auto it = requests.begin(); it != requests.end(); ) {
                if (*it >= currentFloor) {
                    cout << "Moving to floor " << *it << "." << endl << endl;  // Print the moving notification
                    currentFloor = *it;
                    it = requests.erase(it); // Erase the request after serving it
                    requestServed = true;
                    break;
                }
                else {
                    ++it;
                }
            }
        }
        else {
            for (auto it = requests.rbegin(); it != requests.rend(); ++it) {
                if (*it <= currentFloor) {
                    cout << "Moving to floor " << *it << "." << endl << endl;  // Print the moving notification
                    currentFloor = *it;
                    requests.erase((it + 1).base()); // Proper erase from reverse iterator
                    requestServed = true;
                    break;
                }
            }
        }

        if (!requestServed) {
            switchDirection();
        }
    }


    void switchDirection() {
        if (requests.empty()) return;

        cout << "No requests pending to go " << (goingUp ? "up" : "down") << ", switching direction to " << (!goingUp ? "up" : "down") << "." << endl << endl;

        goingUp = !goingUp;  // Toggle the direction
        sortRequests();  // Re-sort the requests based on new direction
    }

    void displayStatus() {
        cout << "Current floor: " << currentFloor << endl << endl;
        cout << "Direction: " << (goingUp ? "Up" : "Down") << endl << endl;
        cout << "Pending requests: ";
        for (int floor : requests) {
            cout << floor << " ";
        }
        cout << endl << endl;
    }
};


void simulateElevatorOperation(int numRequests, int numFloors) {
    Elevator elevator;
    srand(time(NULL)); // Seed for random number generation

    for (int i = 0; i < numRequests; i++) {
        int randomFloor = rand() % numFloors;
        elevator.addRequest(randomFloor);
        elevator.moveElevator();
        elevator.displayStatus();
    }
}