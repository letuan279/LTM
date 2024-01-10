#include <nlohmann/json.hpp>
#include <iostream>
#include "config.hpp"

using json = nlohmann::json;
using namespace std;

struct MessageData {
    string id;
    string id_project;
    string id_user;
    string username;
    string content;
    string time;
};

unordered_map<string, string> loadUsernames() {
    unordered_map<string, string> usernames;

    ifstream file(USER_FILE);
    if (!file) {
        cerr << "Không thể mở file users.csv" << endl;
        return usernames;
    }

    string line;
    getline(file, line);

    while (getline(file, line)) {
        istringstream iss(line);
        string id, username;

        getline(iss, id, ',');
        getline(iss, username, ',');

        usernames[id] = username;
    }

    file.close();

    return usernames;
}

string getAllMessagesByProjectId(const string& idProject) {
    vector<MessageData> messages;

    ifstream file(MESSAGE_FILE);
    if (!file) {
        cerr << "Không thể mở file messages.csv" << endl;
        return "";
    }

    string line;
    getline(file, line);

    unordered_map<string, string> usernames = loadUsernames();

    while (getline(file, line)) {
        istringstream iss(line);
        string id, id_project, id_user, content, time;

        getline(iss, id, ',');
        getline(iss, id_project, ',');
        getline(iss, id_user, ',');
        getline(iss, content, ',');
        getline(iss, time, ',');

        if (id_project == idProject) {
            MessageData message;
            message.id = id;
            message.id_project = id_project;
            message.id_user = id_user;
            message.username = usernames[id_user];
            message.content = content;
            message.time = time;

            messages.push_back(message);
        }
    }
    file.close();

    json messageArray;
    for (const auto& message : messages) {
        json messageData;
        messageData["id"] = message.id;
        messageData["id_project"] = message.id_project;
        messageData["id_user"] = message.id_user;
        messageData["username"] = message.username;
        messageData["content"] = message.content;
        messageData["time"] = message.time;
        messageArray.push_back(messageData);
    }

    return messageArray.dump();
};

void addMessage(const string& idProject, const string& idUser, const string& content, const string& time) {
    ofstream file(MESSAGE_FILE, ios::app);

    if (!file) {
        cerr << "Không thể mở file messages.csv" << endl;
        return;
    }

    string id = generateRandomID();

    file << id << "," << idProject << "," << idUser << "," << content << "," << time << endl;

    file.close();
}