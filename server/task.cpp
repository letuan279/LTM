#include<iostream>
#include "config.hpp"

using namespace std;

struct Task {
    string id;
    string id_project;
    string name;
    string id_assign;
    string comment;
    string start_date;
    string end_date;
};

vector<Task> getAllTasksByProjectID(const string& projectID) {
    vector<Task> tasks;

    ifstream inputFile(TASK_FILE);
    string line;

    while (getline(inputFile, line)) {
        istringstream iss(line);
        string id, id_project, name, id_assign, comment, start_date, end_date;

        if (getline(iss, id, ',') &&
            getline(iss, id_project, ',') &&
            getline(iss, name, ',') &&
            getline(iss, id_assign, ',') &&
            getline(iss, comment, ',') &&
            getline(iss, start_date, ',') &&
            getline(iss, end_date, ',')) {

            if (id_project == projectID) {
                tasks.push_back({ id, id_project, name, id_assign, comment, start_date, end_date });
            }
        }
    }

    inputFile.close();

    return tasks;
}