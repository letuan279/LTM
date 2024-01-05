#include <iostream>
#include "config.hpp"

using namespace std;

string getAllProjectById(const string _id) {
    if (_id.empty()) {
        return init_response(false, "[ERROR] User not found", "");
    }

    ifstream prj_file(PROJECT_FILE);
    if (!prj_file) {
        return init_response(false, "[ERROR] Failed to open " + string(PROJECT_FILE), "");
    }

    string line;
    vector<string> lines;

    while (getline(prj_file, line)) {
        stringstream ss(line);
        string id, name, id_owner;
        getline(ss, id, ',');
        getline(ss, name, ',');
        getline(ss, id_owner, ',');

        if (_id == id_owner)
            lines.push_back("{\"id\":\"" + id + "\",\"name\":\"" + name + "\",\"id_owner\":\"" + id_owner + "\"}");
    }

    prj_file.close();

    string data = "[";
    for (const string& line : lines) {
        data += line + ",";
    }
    data.pop_back();
    data += "]";

    return init_response(true, "Successful", data);
}

string findProjectById(const string _id) {
    if (_id.empty()) {
        return "[ERROR] User not found";
    }

    ifstream prj_file(PROJECT_FILE);
    if (!prj_file) {
        return "[ERROR] Failed to open " + string(PROJECT_FILE);
    }

    string line;
    vector<string> lines;

    string response;

    while (getline(prj_file, line)) {
        stringstream ss(line);
        string id, name, id_owner;
        getline(ss, id, ',');
        getline(ss, name, ',');
        getline(ss, id_owner, ',');

        if (_id == id)
            response = "{\"id\":\"" + id + "\",\"name\":\"" + name + "\",\"id_owner\":\"" + id_owner + "\"}";
    }

    prj_file.close();

    return response;
}

string createProject(const string user_id, const string name) {
    if (user_id.empty()) {
        return init_response(false, "[ERROR] User not found", "");
    }

    string newProjectID = generateRandomID();

    ofstream prj_file(PROJECT_FILE, ios::app);
    if (!prj_file) {
        return init_response(false, "[ERROR] Failed to open " + string(PROJECT_FILE), "");
    }

    prj_file << newProjectID << "," << name << "," << user_id << endl;
    prj_file.close();

    string newMemID = generateRandomID();

    ofstream mem_file(MEMBER_FILE, ios::app);
    if (!mem_file) {
        return init_response(false, "[ERROR] Failed to open " + string(PROJECT_FILE), "");
    }

    mem_file << newMemID << "," << user_id << "," << newProjectID << endl;
    mem_file.close();

    return init_response(true, "Created project with id: " + newProjectID, "");
}

// string deleteProject(const string _id) {
//     if (_id.empty()) {
//         return init_response(false, "[ERROR] Project not found", "");
//     }

//     ifstream prj_file(PROJECT_FILE);
//     if (!prj_file) {
//         return init_response(false, "[ERROR] Failed to open " + string(PROJECT_FILE), "");
//     }

//     string line;
//     vector<string> lines;

//     while (getline(prj_file, line)) {
//         stringstream ss(line);
//         string id, name, id_owner;
//         getline(ss, id, ',');
//         getline(ss, name, ',');
//         getline(ss, id_owner, ',');

//         if (_id != id)
//             lines.push_back({id, name, id_owner});
//     }

//     prj_file.close();

//     ofstream prj_file(PROJECT_FILE, ios::app);
//     if (!prj_file) {
//         return init_response(false, "[ERROR] Failed to open " + string(PROJECT_FILE), "");
//     }

//     for (const string& line : lines) {
//         prj_file << line["id"] << "," << line["name"] << "," << line["id_owner"] << "," << endl;
//     }
//     prj_file.close();

//     return init_response(true, "Delete project - id: " + newID, "");
// }