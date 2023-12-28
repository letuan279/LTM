#include <iostream>
#include <string>
#include <fstream>
#include <stdio.h>
#include <stdlib.h>
#include <nlohmann/json.hpp>
#include <unistd.h>
#include <string.h>
#include <random>

using namespace std;
using json = nlohmann::json;

// Utils
string generateRandomID() {
    string characters = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
    random_device rd;
    mt19937 generator(rd());
    uniform_int_distribution<int> distribution(0, characters.length() - 1);

    string randomID;
    for (int i = 0; i < 5; ++i) {
        randomID += characters[distribution(generator)];
    }

    return randomID;
}

string init_response(const bool success, const string message, const string data) {
    json res;
    string resMsg;

    res["success"] = int(success);

    if (message.empty()) {
        if (success) res["message"] = "[SUCCESS] Done";
        else res["message"] = "[ERROR] Something went wrong";
    } else {
        res["message"] = message;
    }

    if (data.find_first_of("{}[]") != string::npos) {
        res["data"] = json::parse(data);
    } else {
        res["data"] = data;
    }
    
    return res.dump();
}