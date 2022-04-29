#ifndef LAUNCH_H
#define LAUNCH_H

#include <iostream>
#include <string>
#include "User.h"
#include "Heap.h"

using namespace std;

class Launch{
    public:
        Launch(int target);
        ~Launch(){ delete users; }
        bool checkValidUser(string userID);
        void registerUser(string userID);
        bool vote(string userID, int votes);
        User* checkWinner();
        void printScoreboard(int k);
        int getProfit(){ return profit; }
    private:
        int profit, launch, launch_target;
        Heap<User>* users;
};

#endif