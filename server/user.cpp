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

string getUsernameUserById(const string& id) {
    ifstream file(USER_FILE);
    string line;

    while (getline(file, line)) {
        istringstream iss(line);
        string idFromFile, username, password, session;

        if (getline(iss, idFromFile, ',') &&
            getline(iss, username, ',') &&
            getline(iss, password, ',') &&
            getline(iss, session, ',')) {
            
            if (idFromFile == id) {
                return username;
            }
        }
    }

    return "";
}
