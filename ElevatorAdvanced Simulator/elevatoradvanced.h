#ifndef ELEVATORADVANCED_H
#define ELEVATORADVANCED_H

#define NUM_OF_FLOORS 100
#include "elevator.h"

class ElevatorAdvanced : public Elevator {
public:
    void move_to_floor(int target_floor);
    std::string get_current_direction();
    int get_tarfloor_direction(int tar);

    void input_direction_from_floors();
    void Append(int floor, int direction=2);//Add and sort.Default direction=2, meaning no direction.
    void MoveOn_s();
    void test_show_tarlist();
    void test_show_tardirelist();
    void InputTargetFloors();


    void Delete(int floor);//Delete
private:
    int tardirelist[NUM_OF_FLOORS]={0};
};

#endif // ELEVATORADVANCED_H
