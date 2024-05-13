#ifndef ELEVATOR_H
#define ELEVATOR_H

#include <iostream>
#include <chrono>
#include <thread>
#include <ctime>
#include <algorithm>

#define NUM_OF_FLOORS 1000

class Elevator
{
public:
    //Constructor
    Elevator(){};

    //MECHANICAL PART//
    void set_direction();
    void set_floor_number(int floor);
    int get_current_floor() const;
    void move_to_floor(int target_floor);//Will show the process of moving
    void set_dtime(int sec);

    //MEMORY PART//
    //Get data
    int Gtop();
    int Gbottom();
    int Gsize();
    //List manipulation
    void Append(int floor);//Add and sort.
    void Delete(int floor);//Delete
    //Check
    int check(int floor) const;//Check if the floor is in the list.
    int checktop(int floor) const;
    int checkbottom(int floor) const;
    //Mixed
    void InputTargetFloors();
    void MoveOn();
    //Previous version
    int InputTargetFloor();//Previous
    void MoveConti();//Previous

protected:

    //MECHANICAL VARIABLES//
    int current_floor=1;
    int direction=0;//0 for up, 1 for down.
    int dtime=1;//Time of movement.

    //MEMORY VARIABLES//
    int tarlist[NUM_OF_FLOORS]={0};
    int size=0;

    //Previous
    int tar_floor=0;
    int prev_sign=0;//1 for previous version

};

#endif // ELEVATOR_H
