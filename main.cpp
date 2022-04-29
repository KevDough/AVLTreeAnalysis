#include <iostream>
#include <stdio.h>
#include <sstream>

#include "Launch.h"
#include "User.h"

using namespace std;

int countSpaces(string s) {
  int count = 0;

  for (int i = 0; i < s.size(); i++)
    if (s[i] == ' ') count++;

  return count;
}


void usage(char* programName) {
    cout << programName << " expects 1 parameter." << endl;
    cout << "Usage: " << programName << " <flight-cost>" << endl;
}


int main(int argc, char** argv) {

    if (argc != 2) {
        usage(argv[0]);
        return 1;
    }
    int flightCost;
    sscanf(argv[1], "%d", &flightCost);

    Launch company(flightCost);

    string commandInput;
    int space = 0;
    cout << "Please type a command. The commands are:\n" << "'register <userid>' to regiser a user\n" <<
        "'vote <num-votes> <userid>' to give a user votes\n" << "'scoreboard <k>' to see the users with the most votes\n" << 
        "'profit' to see how much money the company has earned to date\n" << "'quit' to end the program\n" << "'help' to see avaliable commands" << endl;
    // handleInput();
    while(1){
       
        getline(cin, commandInput);
        if(commandInput == "quit"){
            cout << "Program ended" << endl;
            return 0;
        }
        else if(commandInput.substr(0,8) == "register"){
            if(countSpaces(commandInput) != 1) cout << "Invalid arguments please use all arguments required" << endl;
            else{
                string addUser = commandInput.substr(9);
                if(!company.checkValidUser(addUser)) company.registerUser(addUser);
                else{cout << "User already registered. Please try again" << endl;}
            }
        }  
        else if(commandInput.substr(0,4) == "vote"){
            if(countSpaces(commandInput) != 2) cout << "Invalid arguments please use all arguments required" << endl;
            else{
                string temp = commandInput.substr(5);
                space = temp.find(" ");
                int numVotes;
                stringstream ss(temp.substr(0,space));
                ss >> numVotes;
                string userID = temp.substr(space+1);
                if(company.vote(userID,numVotes)){
                    User* checkedWinner = company.checkWinner();
                    if(checkedWinner!=nullptr){
                        cout<<"LAUNCHED "+checkedWinner->getUserID()<<endl;
                    }
                }
                //Checks to make sure 2 argument is a number
                else if(!(commandInput.at(5) >= 48 && commandInput.at(5) <= 57)){
                    cout << "Please ensure order of arguments are correct and try again" << endl;
                }
                //Output for non-exisitant user
                else{
                    cout << "User not registered. Please register user and try again" << endl;
                }
            }
        }  
        else if(commandInput.substr(0,10) == "scoreboard"){
            if(countSpaces(commandInput) != 1) cout << "Invalid arguments please use all arguments required" << endl;
            else{    
                int scoreboardUsers;
                stringstream ss(commandInput.substr(11));
                ss >> scoreboardUsers;
                company.printScoreboard(scoreboardUsers);
            }
        }
        else if(commandInput == "profit"){
            cout<<"$"<<company.getProfit()<<endl;
        }
        else if(commandInput == "help"){
            cout << "Please type a command. The commands are:\n" << "'register <userid>' to regiser a user\n" <<
            "'vote <num-votes> <userid>' to give a user votes\n" << "'scoreboard <k>' to see the users with the most votes\n" << 
            "'profit' to see how much money the company has earned to date\n" << "'quit' to end the program\n" << "'help' to see avaliable commands" << endl;
        }
        else{
            cout << "Please enter a valid input" << endl;
        }
    }
    return 0;
}