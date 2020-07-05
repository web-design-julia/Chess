#ifndef MIX_PAR_H
#define MIX_PAR_H
#include <iostream>
#include <stdlib.h>

using namespace std;

class Mix_Par
{
public:
    const int BYE = -1;

    // сдвиг
    void RotateArray(int* teams, int num_teams);

    //нечетное кол-во
    int** GenerateRoundRobinOdd(const int num_teams);
    int** GenerateRoundRobinEven(int num_teams);
    int** GenerateRoundRobin(int num_teams);
    int* List_player(int num_teams);
    ~Mix_Par();
     void Sort_pairs(int num_teams);

public:
     int** results{nullptr};
     int** results2{nullptr};
     int num_teams{0};
     int* teams{nullptr};
     int** arr_pairs{nullptr};
     int capacity_tour{0};
     int* arr_players{nullptr};
};

#endif // MIX_PAR_H
