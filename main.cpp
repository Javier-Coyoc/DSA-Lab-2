//lab 2: Imlpementing authorization within a singly-linked list
#include <iostream>
#include <string>
using namespace std;

//Role-based access control  
struct User {
    string username;
    string password;
    string role;      // Authorization role:"admin", "editor", "viewer"
    User* next;

    User(const string& u, const string& p, const string& r = "viewer") {
        username = u;
        password = p;
        role = r;
        next = nullptr;
    }
};

bool insertUser(User*& head, const string& username, const string& password, const string& role);
bool authorize(User* head, const string& username, const string& action);
User* findUser(User* head, const string& username);

int main() {

    return 0;
}

bool insertUser(User*& head, const string& username, const string& password, const string& role = "viewer") {
    // Check if username already exists
    User* current = head;
    while (current != nullptr) {
        if (current->username == username) {
            return false;
        }
        current = current->next;
    }
    
    // Create new user and insert at head (more efficient)
    User* newUser = new User(username, password, role);
    newUser->next = head;
    head = newUser;
    return true;
}

User* findUser(User* head, const string& username) {
    // TODO: implement
    //create a current variable and assign to head, then loop through the linked list to find the matching username
    User* current = head;

    while (head != nullptr) {
        if(current->username == username) {
            //We return current because current is the pointer currently pointing to the node
            return current;
        } 
        current = current->next;
    }
    
    return nullptr;
}

bool authorize(User* head, const string& username, const string& action) {
    User* getUser = findUser(head, username);
    //if their is no user return false
    if (!getUser) {
        return false;
    } 

    if (getUser->role == "admin") {
        return true;
    } 
    else if (getUser->role == "editor") {
        string permissionList[] = {"view", "edit", "create"};
        for (size_t i = 0; i < 3; i++)
        {
            if (action == permissionList[i]) {
                return true;
            }
        }

        return false;
    } 
    else if (getUser->role == "viewer") {
        if (action == "view") {
            return true;
        } else {
            return false;
        }
    } 
    return false;

}