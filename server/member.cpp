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

