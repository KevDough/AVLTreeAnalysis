#include "Launch.h"

Launch::Launch(int target){
    launch_target = target;
    profit = 0;
    launch = 0;
    users = new Heap<User>();
}

bool Launch::checkValidUser(string userID){
    return users->has(userID);
}

void Launch::registerUser(string userID){
    users->insert(userID,new User(userID));
}

bool Launch::vote(string userID, int votes){
    if(!checkValidUser(userID)) return false;
    users->increaseBy(userID,votes);
    int toLaunch = votes/2;
    int toProfit = votes-toLaunch;
    profit+=toProfit;
    launch+=toLaunch;

    return true;
}

User* Launch::checkWinner(){
    if(launch>=launch_target){
        User* top = users->extractMax()->data;
        launch-=launch_target;
        return top;
    }
    return nullptr;
}

void Launch::printScoreboard(int k){
    if(k>users->size()) k=users->size();
    User** topK = users->topK(k);

    cout << "Displaying Scoreboard" << endl;
    for(int i = 0; i<k; i++){
        User* user = topK[i];
        cout << i + 1 << ". "<< user->getUserID() << " " << user->getVotes() << endl;
    }

    delete[] topK;
}