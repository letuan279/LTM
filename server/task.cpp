#include<iostream>
#include "config.hpp"

using namespace std;

struct Task {
    string id;
    string id_project;
    string id_manager;
    string name;
    string status;
    string id_assign;
    string comment;
    string start_date;
    string end_date;
};

string getAllTasksByProjectID(const string& projectID) {
    vector<string> tasks;

    ifstream inputFile(TASK_FILE);
    string line;

    while (getline(inputFile, line)) {
        istringstream iss(line);
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

            if (id_project == projectID) {
                tasks.push_back("{\"id\":\"" + id + "\",\"id_project\":\"" + id_project + "\",\"id_manager\":\"" + id_manager + "\",\"name\":\"" + name + "\",\"status\":\"" + status + "\",\"id_assign\":\"" + id_assign + "\",\"comment\":\"" + comment + "\",\"start_date\":\"" + start_date + "\",\"end_date\":\"" + end_date + "\"}");
            }
        }
    }

    inputFile.close();

    string data = "[";
    for (const string& task : tasks) {
        data += task + ",";
    }
    if(data[data.length() - 1] == ',') {
        data.pop_back();
    } 
    data += "]";

    return init_response(true, "Get tasks successed", data);
}

string createNewTask(const string id_user, const string id_project, const string name, const string status, const string id_assign, const string comment, const string start_date, const string end_date) {
    string newTaskId = generateRandomID();

    ofstream taskFile(TASK_FILE, ios::app);
    if (!taskFile) {
        return init_response(false, "[ERROR] Failed to open " + string(TASK_FILE), "");
    }

    // id,id_project,name,status,id_assign,comment,start_date,end_date
    taskFile << newTaskId << "," << id_project << "," << id_user << "," << name << "," << status << "," << id_assign << "," << comment << "," << start_date << "," << end_date << endl;
    taskFile.close();

    return init_response(true, "Created task with id: " + newTaskId, "");
}

string assignTaskToUser(const string& id_task, const string& id_assign_new) {
    ifstream input_file(TASK_FILE);
    if (!input_file) {
        return init_response(false, "[ERROR] Failed to open " + string(TASK_FILE), "");
    }

    vector<Task> tasks;
    string line;

    while (getline(input_file, line)) {
        istringstream iss(line);
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

            if (id_task == id) {
                id_assign = id_assign_new;
            }
            tasks.push_back({id, id_project, id_manager, name, status, id_assign, comment, start_date, end_date});
        }
    }

    input_file.close();

    ofstream output_file(TASK_FILE, ios::trunc);
    if (!output_file) {
        return init_response(false, "[ERROR] Failed to open " + string(TASK_FILE), "");
    }

    for (const auto& task : tasks) {
        output_file << task.id << "," << task.id_project << "," << task.id_manager << "," << task.name << "," << task.status << "," << task.id_assign << "," << task.comment << "," << task.start_date << "," << task.end_date << endl;
    }
    output_file.close();

    return init_response(true, "Assign successed to user " + id_assign_new, "");
}

string updateStatusByTaskId(const string& id_task, const string& new_status) {
    ifstream input_file(TASK_FILE);
    if (!input_file) {
        return init_response(false, "[ERROR] Failed to open " + string(TASK_FILE), "");
    }

    vector<Task> tasks;
    string line;

    while (getline(input_file, line)) {
        istringstream iss(line);
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

            if (id_task == id) {
                status = new_status;
            }
            tasks.push_back({id, id_project, id_manager, name, status, id_assign, comment, start_date, end_date});
        }
    }

    input_file.close();

    ofstream output_file(TASK_FILE, ios::trunc);
    if (!output_file) {
        return init_response(false, "[ERROR] Failed to open " + string(TASK_FILE), "");
    }

    for (const auto& task : tasks) {
        output_file << task.id << "," << task.id_project << "," << task.id_manager << "," << task.name << "," << task.status << "," << task.id_assign << "," << task.comment << "," << task.start_date << "," << task.end_date << endl;
    }
    output_file.close();

    return init_response(true, "Update status successed", "");
}

string editCommentByTaskId(const string& id_task, const string& new_comment) {
    ifstream input_file(TASK_FILE);
    if (!input_file) {
        return init_response(false, "[ERROR] Failed to open " + string(TASK_FILE), "");
    }

    vector<Task> tasks;
    string line;

    while (getline(input_file, line)) {
        istringstream iss(line);
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

            if (id_task == id) {
                comment = new_comment;
            }
            tasks.push_back({id, id_project, id_manager, name, status, id_assign, comment, start_date, end_date});
        }
    }

    input_file.close();

    ofstream output_file(TASK_FILE, ios::trunc);
    if (!output_file) {
        return init_response(false, "[ERROR] Failed to open " + string(TASK_FILE), "");
    }

    for (const auto& task : tasks) {
        output_file << task.id << "," << task.id_project << "," << task.id_manager << "," << task.name << "," << task.status << "," << task.id_assign << "," << task.comment << "," << task.start_date << "," << task.end_date << endl;
    }
    output_file.close();

    return init_response(true, "Update comment successed", "");
}