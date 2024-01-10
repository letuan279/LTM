#include <iostream>
#include <string>
#include <fstream>
#include <stdio.h>
#include <stdlib.h>
#include <nlohmann/json.hpp>
#include <unistd.h>
#include <string.h>
#include <random>
#include <chrono>
#include <ctime>

using namespace std;
using json = nlohmann::json;

bool isJson(const string str) {
    try
    {
        json data = json::parse(str);
        return true;
    }
    catch(const std::exception& e)
    {
        return false;
    }
    
}

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

    if (isJson(data)) {
        res["data"] = json::parse(data);
    } else {
        res["data"] = data;
    }
    
    return res.dump();
}

string getCurrentDate() {
    chrono::system_clock::time_point now = chrono::system_clock::now();
    time_t currentTime = chrono::system_clock::to_time_t(now);
    tm* timeInfo = localtime(&currentTime);
    char dateString[11];
    strftime(dateString, sizeof(dateString), "%Y/%m/%d", timeInfo);
    string formattedDate(dateString);
    return formattedDate;
}
