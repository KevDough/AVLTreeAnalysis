#include <string>
#include <iostream>

#include "User.h"

using namespace std;

// Constructors 
User::User() {
    this->userID = "NoID";
    this->votes = 0;
}

User::User(string userID) {
    this->userID = userID;
    this->votes = 0;
}

User::User(const User& userToCopy) {
    this->userID = userToCopy.getUserID();
    this->votes = userToCopy.getVotes();
}

User& User::operator=(const User& userToCopy) {
    if (this != &userToCopy) {
        this->userID = userToCopy.getUserID();
        this->votes = userToCopy.getVotes();
    }
    return *this;
}

// Destructor
User::~User() {

}

// Overloaded Operators
bool operator==(const User& user1, const User& user2) {
    return user1.getVotes() == user2.getVotes();
}

ostream& operator<< (ostream& os, const User& user) {
    os << user.userID << " " << user.votes;
    return os;
}

bool User::operator<(const User& other){
    return this->getVotes()<other.getVotes();
}
void User::operator+=(const int n){
    votes+=n;
}

// Member Functions
void User::addVotes(int votesToAdd) {
    this->votes += votesToAdd;
}

// Accessors
string User::getUserID() const {
    return this->userID;
}

int User::getVotes() const {
    return this->votes;
}

// Mutators
void User::setUserID(string userID) {
    this->userID = userID;
}

void User::setVotes(int votes) {
    this->votes = votes;
}