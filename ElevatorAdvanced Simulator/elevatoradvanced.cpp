#include "elevatoradvanced.h"

int ElevatorAdvanced::get_tarfloor_direction(int tar)
{
    for (int i=0;i<size;i++)
    {
        if (tarlist[i]==tar)
            return tardirelist[i];
    }
    return 0;//Useless
}

void ElevatorAdvanced::InputTargetFloors()
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

void ElevatorAdvanced::Delete(int floor)
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
        tardirelist[i]=tardirelist[i+1];
    }
    size--;
}

void ElevatorAdvanced::move_to_floor(int target_floor)
{
    if (target_floor > current_floor)
    {
        std::cout << "Moving up from floor " << current_floor << " to floor " << target_floor << "..." << std::endl;
        for (int floor = current_floor + 1; floor <= target_floor; floor++)
        {
            //std::this_thread::sleep_for(std::chrono::seconds(dtime)); // Simulate delay
            std::cout << "Arrived at floor " << floor << std::endl;
        }
        if (
            (check(target_floor)==1 && ((get_tarfloor_direction(target_floor)==direction)||get_tarfloor_direction(target_floor)==2))||
            prev_sign==1)//Previous version capable
            std::cout << "Elevator reached destination floor: " << target_floor << std::endl;
        current_floor = target_floor;
    }
    else if (target_floor < current_floor)
    {
        std::cout << "Moving down from floor " << current_floor << " to floor " << target_floor << "..." << std::endl;
        for (int floor = current_floor - 1; floor >= target_floor; floor--)
        {
            //std::this_thread::sleep_for(std::chrono::seconds(dtime)); // Simulate delay
            std::cout << "Arrived at floor " << floor << std::endl;
        }
        if (
            (check(target_floor)==1 && ((get_tarfloor_direction(target_floor)==direction)||get_tarfloor_direction(target_floor)==2))||
            prev_sign==1)//Previous version capable
            std::cout << "Elevator reached destination floor: " << target_floor << std::endl;
        current_floor = target_floor;
    }
    else//May be deleted
    {
        std::cout << "Elevator is already at the destination floor" << std::endl;
    }
}

void ElevatorAdvanced::MoveOn_s()
{
    /*/
    if (checktop(get_current_floor())==1) {direction=1;}
    else if (checkbottom(get_current_floor())==1) {direction=0;}
    if (Gsize()!=0)
    {
        if (direction == 0) { move_to_floor(get_current_floor() + 1); }
        else if (direction == 1) { move_to_floor(get_current_floor() - 1); }
    }
    else
    {
        std::cout<<"No target floor."<<std::endl;
    }
    if(
        (check(get_current_floor())==1 && ((get_tarfloor_direction(get_current_floor())==direction)||get_tarfloor_direction(get_current_floor())==2)) ||
        (Gsize()==1&&check(get_current_floor()))
        )
    {
        Delete(get_current_floor());
    }/*/

    //
    if (Gsize()==0)
    {
        std::cout<<"No target floor."<<std::endl;
        return;
    }

    if (get_current_floor()<Gtop() && direction==0)//extra target floors above
    {
        move_to_floor(get_current_floor() + 1);
    }
    else if (get_current_floor()>Gbottom() && direction==1)
    {
        move_to_floor(get_current_floor() - 1);
    }
    else if (get_current_floor()<Gtop() && direction==1)
    {
        if (Gbottom()>get_current_floor()) direction=0;
    }
    else if (get_current_floor()>Gbottom() && direction==0)
    {
        if (Gtop()<get_current_floor()) direction=1;
    }

    if
    (
        (
            check(get_current_floor())==1 &&
            (
                (get_tarfloor_direction(get_current_floor())==direction) ||
                get_tarfloor_direction(get_current_floor())==2 ||
                (6==get_current_floor()) ||
                (1==get_current_floor())
            )
        )
        ||
        (
            Gsize()==1 &&
            check(get_current_floor())
        )
    )

    {
        Delete(get_current_floor());
    }//
}

std::string ElevatorAdvanced::get_current_direction()
{
    if (direction==0)
    {
        return "up";
    }
    else return "down";
}

void ElevatorAdvanced::input_direction_from_floors()//get up or down request from different floors
{
    int floor, dire;
    std::string direction;
    std::cout << "Outside direction input(floor_n direction end with 0): ";
    while (true)
    {
        std::cin >> floor;
        if (floor==0) break;
        std::cin >> direction;
        if (direction == "up") dire=0;
        else if (direction == "down") dire=1;
        Append(floor, dire);
    }
}

void ElevatorAdvanced::Append(int floor, int direction)
{
    //std::cout<<"Check floor="<<check(floor)<<std::endl;
    if (check(floor)==0)
    {
        //Add
        tarlist[size] = floor;
        tardirelist[size] = direction;
        size++;
        //Sort
        //std::sort(tarlist, tarlist + size);
        //Replace the former line
        for (int i=size-1;i>0;i--)
        {
            for (int j=0;j<i;j++)
            {
                if (tarlist[j]>tarlist[j+1])
                {
                    int temp=tarlist[j];
                    tarlist[j]=tarlist[j+1];
                    tarlist[j+1]=temp;
                    temp=tardirelist[j];
                    tardirelist[j]=tardirelist[j+1];
                    tardirelist[j+1]=temp;
                }
            }
        }
        //
    }
}

void ElevatorAdvanced::test_show_tarlist()
{
    std::cout<<"test-tarlist: ";
    for (int i=0;i<size;i++)
    {
        std::cout<<tarlist[i]<<" ";
    }
    std::cout<<std::endl;
}
void ElevatorAdvanced::test_show_tardirelist()
{
    std::cout<<"test-tarlist: ";
    for (int i=0;i<size;i++)
    {
        std::cout<<tardirelist[i]<<" ";
    }
    std::cout<<std::endl;
}
