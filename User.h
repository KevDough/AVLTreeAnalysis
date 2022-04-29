#ifndef USER_H
#define USER_H

using namespace std;

class User {
    private:
        string userID;
        int votes;

    public:
        // Constructors
        User();
        User(string userID);
        User(const User& userToCopy);
        User& operator=(const User& userToCopy);
        
        // Destructors
        ~User();

        // Oerloaded Operators
        friend bool operator==(const User& user1, const User& user2);
        friend ostream& operator<<(ostream& os, const User& user);
        bool operator<(const User& other);
        void operator+=(const int n);
        
        // Member Functions
        void addVotes(int votesToAdd);

        // Accessors
        string getUserID() const;
        int getVotes() const;

        // Mutators
        void setUserID(string userID);
        void setVotes(int votes);

};

#endif