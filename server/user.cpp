#include<iostream>
#include "config.hpp"
#include <unordered_set>

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
            getline(iss, password, ',')) {
            
            if (id == user_id) {
                return "{\"id\":\"" + id + "\",\"username\":\"" + username + "\"}";
            }
        }
    }

    return "";
}

struct UserData {
    string id;
    string username;
};

string getAllUsers(const string& user_id) {

    vector<UserData> users;
    
    ifstream file(USER_FILE);
    string line;

    json response;
    response["success"] = 1;
    response["message"] = "OK";
    response["data"] = json::array();

    while (getline(file, line)) {
        istringstream iss(line);
        string id, username, password, sessionFromFile;

        if (getline(iss, id, ',') &&
            getline(iss, username, ',') &&
            getline(iss, password, ',')) {
            
            if (id != user_id && id != "id") {
                users.push_back({id, username});
            }
        }
    }

    for (const UserData& user : users) {
        json userData;
        userData["id"] = user.id;
        userData["username"] = user.username;
        response["data"].push_back(userData);
    }

    return response.dump();
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

string getUserToAddMember(const string& id_user, const string& id_project) {
    vector<UserData> users;
    ifstream usersFile(USER_FILE);
    if (usersFile.is_open()) {
        string line;
        getline(usersFile, line);
        while (getline(usersFile, line)) {
            stringstream ss(line);
            string id, username, password, session;
            getline(ss, id, ',');
            getline(ss, username, ',');
            getline(ss, password, ',');
            getline(ss, session, ',');
            users.push_back({id, username});
        }
        usersFile.close();
    }

    unordered_set<string> projectMembers;
    ifstream membersFile(MEMBER_FILE);
    if (membersFile.is_open()) {
        string line;
        getline(membersFile, line);
        while (getline(membersFile, line)) {
            stringstream ss(line);
            string id, id_user, id_projectFile;
            getline(ss, id, ',');
            getline(ss, id_user, ',');
            getline(ss, id_projectFile, ',');
            if (id_projectFile == id_project) {
                projectMembers.insert(id_user);
            }
        }
        membersFile.close();
    }

    json response;
    response["success"] = 1;
    response["message"] = "OK";
    response["data"] = json::array();

    for (const UserData& user : users) {
        if(user.id != id_user && projectMembers.find(user.id) == projectMembers.end()) {
            json userData;
            userData["id"] = user.id;
            userData["username"] = user.username;
            response["data"].push_back(userData);
        }
    }

    return response.dump();
}

string getUserToAddTask(const string& id_user, const string& id_project) {
    vector<UserData> users;
    ifstream usersFile(USER_FILE);
    if (usersFile.is_open()) {
        string line;
        getline(usersFile, line);
        while (getline(usersFile, line)) {
            stringstream ss(line);
            string id, username, password, session;
            getline(ss, id, ',');
            getline(ss, username, ',');
            getline(ss, password, ',');
            getline(ss, session, ',');
            users.push_back({id, username});
        }
        usersFile.close();
    }

    unordered_set<string> projectMembers;
    ifstream membersFile(MEMBER_FILE);
    if (membersFile.is_open()) {
        string line;
        getline(membersFile, line);
        while (getline(membersFile, line)) {
            stringstream ss(line);
            string id, id_user, id_projectFile;
            getline(ss, id, ',');
            getline(ss, id_user, ',');
            getline(ss, id_projectFile, ',');
            if (id_projectFile == id_project) {
                projectMembers.insert(id_user);
            }
        }
        membersFile.close();
    }

    json response;
    response["success"] = 1;
    response["message"] = "OK";
    response["data"] = json::array();

    for (const UserData& user : users) {
        if(user.id != id_user && projectMembers.find(user.id) != projectMembers.end()) {
            json userData;
            userData["id"] = user.id;
            userData["username"] = user.username;
            response["data"].push_back(userData);
        }
    }

    return response.dump();
}

int deleteSession(const string& id_user) {
    ifstream file(USER_FILE);
    if (!file) {
        return 0;
    }

    vector<string> lines;
    string line;
    while (getline(file, line)) {
        lines.push_back(line);
    }

    for (string& line : lines) {
        istringstream iss(line);
        string id, username, password, session;
        getline(iss, id, ',');
        getline(iss, username, ',');
        getline(iss, password, ',');
        getline(iss, session, ',');

        if (id == id_user) {
            session = "";
            ostringstream oss;
            oss << id << "," << username << "," << password << "," << session;
            line = oss.str();
            break;
        }
    }

    ofstream outFile(USER_FILE);
    if (!outFile) {
        return 0;
    }

    copy(lines.begin(), lines.end(), ostream_iterator<string>(outFile, "\n"));

    return 1;
}