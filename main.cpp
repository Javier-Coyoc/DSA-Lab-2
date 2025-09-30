//lab 2: Imlpementing authorization within a singly-linked list
#include <iostream>
#include <string>
#include <vector>
using namespace std;

//Role-based access control  
struct User {
    string username;
    string password;

    vector<string> permissions;      // Authorization role:"admin", "editor", "viewer"
    User* next;

    User(const string& u, const string& p, const vector<string>& perms = {"view"}) {
        username = u;
        password = p;
        permissions = perms;
        next = nullptr;
    }
};

bool insertUser(User*& head, const string& username, const string& password, const vector<string>& perms);
User* findUser(User* head, const string& username);
bool authorize(User* head, const string& username, const string& action);

int main() {
    User* head = nullptr;

    insertUser(head, "Alice", "pass123", {"view"});
    insertUser(head, "Bob", "admin123", {"view", "edit", "delete"});


    cout << "Alice authorize view? " << authorize(head, "Alice", "view") << endl;
    cout << "Alice authorize edit? " << authorize(head, "Alice", "edit") << endl;
    cout << "Bob authorize delete? " << authorize(head, "Bob", "delete") << endl;


    

    return 0;
}

bool insertUser(User*& head, const string& username, const string& password, const vector<string>& perms) { 
    //Check if username already exists, first create a pointer of user class and set it equal to the head
    User* current = head;
    //while the current node is not equal to null check if the username already exists and if so return false
    while(current != nullptr) {
        if (current->username == username) {
            return false;
        }

        current = current->next;
    }
    //Since there were no duplicate usernames, create the new user
    User* newUser = new User(username, password, perms);

    //2 scenarios:the linked list is empty or it has nodes empty linked list:
    if(head == nullptr)
    {
        head = newUser;
        return true;
    } else {
    //linked list is not empty so loop through the linked list and add it to the end
        current = head;
        while (current->next != nullptr) {
            current = current->next;
        }
        current->next = newUser;
        return true;
    }

    return false;
}

User* findUser(User* head, const string& username) {
    // TODO: implement
    //create a current variable and assign to head, then loop through the linked list to find the matching username
    User* current = head;
    while (current != nullptr) {
        if (current->username == username) {
            return current;
        }
        current = current->next;
    }
    return nullptr;
}

//updated authorize function
bool authorize(User* head, const string& username, const string& action) {
    User* getUser = findUser(head, username);
    //if their is no user return false
    if (!getUser) {
        return false;
    } 

    //if permissions list is empty return false
    if (getUser->permissions.empty()) {
        return false;
    }
    //search if action matches the any of the actions in the user's permission list
    for (int i = 0; i < getUser->permissions.size(); i++) {
        if (action == getUser->permissions[i]) {
            return true;
        }
    }

    //action not in permissions list so return false
    return false;
}