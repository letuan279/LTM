#include <iostream>
#include <string>
#include <map>
#include <functional>
#include <nlohmann/json.hpp>
#include <fstream>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#define PROJECT_FILE "data/project.csv"

using json = nlohmann::json;
using namespace std;

string getAllProjectById(const string _id) {
    ifstream prj_file(PROJECT_FILE);
    if (!prj_file) {
        return "Failed to open " + string(PROJECT_FILE);
    }

    string line;
    vector<string> lines;

    while (getline(prj_file, line)) {
        stringstream ss(line);
        string id, name, id_owner;
        getline(ss, id, ',');
        getline(ss, name, ',');
        getline(ss, id_owner, ',');

        if (_id == id) {
            lines.push_back({id, name, id_owner});
        }
    }

    prj_file.close();

    string data = "[";
    for (const string& line : lines) {
        data += line;
    }
    data += "]";

    return data;
}