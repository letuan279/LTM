#include<iostream>
#include "config.hpp"

using namespace std;

// App function
string getIdUserBySession(const string& session) {
    ifstream file(USER_FILE);
    string line;

    while (getline(file, line)) {
        istringstream iss(line);
        string id, username, password, sessionFromFile;

        if (getline(iss, id, ',') &&
            getline(iss, username, ',') &&
            getline(iss, password, ',') &&
            getline(iss, sessionFromFile, ',')) {
            
            if (sessionFromFile == session) {
                return id;
            }
        }
    }

    return "";
}

string getUserById(const string& user_id) {
    ifstream file(USER_FILE);
    string line;

    while (getline(file, line)) {
        istringstream iss(line);
        string id, username, password, sessionFromFile;

        if (getline(iss, id, ',') &&
            getline(iss, username, ',') &&
            getline(iss, password, ',') &&
            getline(iss, sessionFromFile, ',')) {
            
            if (id == user_id) {
                return "{\"id\":\"" + id + "\",\"username\":\"" + username + "\"}";;
            }
        }
    }

    return "";
}