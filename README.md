Madeline Brothers & Abby Botts Project Report

Introduction
This report presents an analysis of an elevator simulation system implemented in C++. The
system is encapsulated within the Elevator class, which governs the movement, request
management, and directional control of the elevator based on queued requests.

Assumptions
1. This system simulates an elevator system.
2. The elevator(s) starts on the ground floor (0) and is set to move upwards.
3. No duplicate floor requests are processed. A floor will not be added to the queue if it is
already in the request queue.
4. The elevator continuously receives and processes requests until there are none left to
process.

UML Diagram
+-------------------------------------+
| Elevator |
+-------------------------------------+
| - currentFloor: int |
| - requests: vector<int> |
| - goingUp: bool |
+-------------------------------------+
| + Elevator() |
| + addRequest(int): void |
| - sortRequests(): void |
| + moveElevator(): void |
| - switchDirection(): void |
| + displayStatus(): void |
+-------------------------------------+
+-------------------------------------+
| ElevatorController |
+-------------------------------------+
| - elevator1: Elevator |
| - elevator2: Elevator |
+-------------------------------------+
| - assignRequest(int): void |
+-------------------------------------+

Efficiency of Algorithms
n = number of requests
1. addRequest(int floor):
a. Complexity:
i. Find: O(n)
ii. Push_back: O(1)
iii. sortRequests: O(n log n)
iv. Total: O(n log n) this could be better but is typical because of the sorting
2. sortRequests():
a. Complexity is O(n log n)
3. moveElevator():
a. Complexity:
i. Iteration over requests: O(n)
ii. Erase: O(n) vector elements may need to be shifted
iii. Total: O(n)
4. switchDirection():

a. Complexity: O(n log n) because sorting algorithm is called

Individual Contribution
Abby Botts and Madeline Brothers split the work even between each other and worked on the
project together in a cohesive manner.

Conclusion
The use of a vector to store floor requests results in O(n log n) complexity for adding requests
and switching directions due to sorting. The is efficient for a moderate number of floor requests
but may not scale well with a very high number of requests. Moving the elevator operates in
O(n) time, processing one request at a time, which is efficient for real-time operations.
