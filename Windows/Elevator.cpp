
#include "Elevator.h"

//MECHANICAL PART//
void Elevator::set_direction()
{
    std::string dir;
    re_enter:
    std::cout << "Set direction (up/down): ";
    std::cin >> dir;

    if (dir=="up")
        direction=0;
    else if (dir=="down")
        direction=1;
    else
    {
        std::cout << "Invalid direction. Please enter 'up' or 'down'." << std::endl;
        goto re_enter;
    }
}

void Elevator::set_floor_number(int floor)
{
    current_floor = floor;
}

int Elevator::get_current_floor() const
{
    return current_floor;
}

void Elevator::move_to_floor(int target_floor)
{
    if (target_floor > current_floor)
    {
        std::cout << "Moving up from floor " << current_floor << " to floor " << target_floor << "..." << std::endl;
        for (int floor = current_floor + 1; floor <= target_floor; floor++)
        {
            std::this_thread::sleep_for(std::chrono::seconds(1)); // Simulate delay
            std::cout << "Arrived at floor " << floor << std::endl;
        }
        if (check(target_floor)==1||prev_sign==1)//Previous version capable
            std::cout << "Elevator reached destination floor: " << target_floor << std::endl;
        current_floor = target_floor;
    }
    else if (target_floor < current_floor)
    {
        std::cout << "Moving down from floor " << current_floor << " to floor " << target_floor << "..." << std::endl;
        for (int floor = current_floor - 1; floor >= target_floor; floor--)
        {
            std::this_thread::sleep_for(std::chrono::seconds(dtime)); // Simulate delay
            std::cout << "Arrived at floor " << floor << std::endl;
        }
        if (check(target_floor)==1||prev_sign==1)//Previous version capable
            std::cout << "Elevator reached destination floor: " << target_floor << std::endl;
        current_floor = target_floor;
    }
    else//May be deleted
    {
        std::cout << "Elevator is already at the destination floor" << std::endl;
    }
}

void Elevator::set_dtime(int sec)
{
    dtime=sec;
}

//MEMORY PART//
//Get data
int Elevator::Gtop()
{
    return tarlist[size-1];
}

int Elevator::Gsize()
{
    return size;
}

//List manipulation
void Elevator::Append(int floor)
{
    if (this->check(floor)==0)
    {
        //Add
        tarlist[size] = floor;
        size++;
        //Sort
        std::sort(tarlist, tarlist + size);
    }
}

void Elevator::Delete(int floor)
{
    int index=0;
    for (int i=0;i<size;i++)
    {
        if (tarlist[i]==floor)
        {
            index = i;
            break;
        }
    }
    for (int i=index;i<size-1;i++)
    {
        tarlist[i]=tarlist[i+1];
    }
    size--;
}

//Check
int Elevator::check(int floor) const
{
    int f=0;
    for (int i=0;i<size;i++)
    {
        if (tarlist[i]==floor)
        {
            f=1;
            break;
        }
    }
    return f;
}

int Elevator::checktop(int floor) const
{
    if (floor>=tarlist[size-1])
        return 1;
    else
        return 0;
}

int Elevator::checkbottom(int floor) const
{
    if (floor<=tarlist[0])
        return 1;
    else
        return 0;
}

//Mixed
void Elevator::InputTargetFloors()
{
    int target_floor;
    std::cout << "Add floor number (End with 0): ";
    while (true)
    {
        std::cin >> target_floor;
        if (target_floor == 0) break;
        Append(target_floor);
    }
}

void Elevator::MoveOn()
{
    if (checktop(get_current_floor())==1) {direction=1;}
    if (checkbottom(get_current_floor())==1) {direction=0;}
    if (Gsize()!=0)
    {
        if (direction == 0) { move_to_floor(get_current_floor() + 1); }
        else if (direction == 1) { move_to_floor(get_current_floor() - 1); }
    }
    else
    {
        std::cout<<"No target floor."<<std::endl;
    }
    if (check(get_current_floor())==1)
    {
        Delete(get_current_floor());
    }
}

//Previous version
int Elevator::InputTargetFloor()
{
    std::cout<<"Set floor number: ";
    std::cin>>tar_floor;
    if ((direction == 0 && tar_floor < get_current_floor()) ||
        (direction == 1 && tar_floor > get_current_floor()))
    {
        std::cout << "Invalid floor selection. Cannot move in specified direction." << std::endl;
        return 1;
    }
    return 0;
}

void Elevator::MoveConti()
{
    prev_sign=1;//Enable previous capability
    move_to_floor(tar_floor);
    prev_sign=0;
}
