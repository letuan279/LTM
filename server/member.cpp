#include <nlohmann/json.hpp>
#include <iostream>
#include "config.hpp"

using json = nlohmann::json;
using namespace std;

struct MemberData {
    string id;
    string username;
    bool is_leader;
};

struct Member {
    string id;
    string id_user;
    string id_project;
};

vector<MemberData> getAllMembers(const string& idProject) {
    vector<MemberData> members;

    ifstream file(MEMBER_FILE);
    string line;

    while (getline(file, line)) {
        istringstream iss(line);
        string id, idUser, idProjectFromFile;

        if (getline(iss, id, ',') &&
            getline(iss, idUser, ',') &&
            getline(iss, idProjectFromFile, ',')) {

            if (idProjectFromFile == idProject) {
                ifstream userFile(USER_FILE);
                string userLine;

                while (getline(userFile, userLine)) {
                    istringstream userIss(userLine);
                    string userId, username, password, session;

                    if (getline(userIss, userId, ',') &&
                        getline(userIss, username, ',') &&
                        getline(userIss, password, ',')) {

                        if (idUser == userId) {
                            members.push_back({ userId, username });
                            break;
                        }
                    }
                }

                userFile.close();
            }
        }
    }

    file.close();

    return members;
}

bool isOwnerProject(const string& idUser, const string& idProject) {
    ifstream prj_file(PROJECT_FILE);
    if (!prj_file) {
        return false;
    }

    string line;
    vector<string> lines;

    while (getline(prj_file, line)) {
        stringstream ss(line);
        string id, name, id_owner;
        getline(ss, id, ',');
        getline(ss, name, ',');
        getline(ss, id_owner, ',');

        if (idUser == id_owner && idProject == id) {
            prj_file.close();
            return true;
        }
    }

    prj_file.close();
    return false;
}

bool isOwnerTask(const string& idUser, const string& idTask) {
    ifstream prj_file(TASK_FILE);
    if (!prj_file) {
        return false;
    }

    string line;
    vector<string> lines;

    while (getline(prj_file, line)) {
        stringstream iss(line);
        string id, id_project, id_manager, name, status, id_assign, comment, start_date, end_date;
        
        if (getline(iss, id, ',') &&
            getline(iss, id_project, ',') &&
            getline(iss, id_manager, ',') &&
            getline(iss, name, ',') &&
            getline(iss, status, ',') &&
            getline(iss, id_assign, ',') &&
            getline(iss, comment, ',') &&
            getline(iss, start_date, ',') &&
            getline(iss, end_date, ',')) {

            if (idTask == id) {
                prj_file.close();
                return isOwnerProject(idUser, id_project);
            }
        }
    }

    prj_file.close();
    return false;   
}