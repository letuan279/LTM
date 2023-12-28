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
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <random>

#define PORT 8080
#define USER_FILE "data/users.csv"

using json = nlohmann::json;
using namespace std;

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

// Function Define 
void handle_request(int client_socket, const string& request);

string handle_login_request(const json& data);
string handle_register_request(const json& data);
string handle_logout_request(const json& data);

void send_response(int client_socket, const string& response);

// Router Define
typedef function<void(int client_socket, const json&)> RequestHandler;
typedef map<string, RequestHandler> Router;
Router router;

// Route register
void register_routes() {
    router["login"] = [](int client_socket, const json& data) {
        string response = handle_login_request(data);
        send_response(client_socket, response);
    };

    router["register"] = [](int client_socket, const json& data) {
        string response = handle_register_request(data);
        send_response(client_socket, response);
    };

    router["logout"] = [](int client_socket, const json& data) {
        string response = handle_logout_request(data);
        send_response(client_socket, response);
    };
}

void handle_request(int client_socket, const string& request) {
    json json_obj = json::parse(request);

    if (json_obj.contains("route") && json_obj.contains("data")) {
        string route = json_obj["route"];
        json data = json_obj["data"];

        if (router.find(route) != router.end()) {
            router[route](client_socket, data);
        } else {
            send_response(client_socket, "Invalid route");
        }
    } else {
        send_response(client_socket, "Invalid JSON format");
    }
}

string handle_login_request(const json& data) {
    string username = data["username"];
    string password = data["password"];

    // Perform login authentication logic
    ifstream file(USER_FILE);
    if (!file) {
        return "Failed to open " + string(USER_FILE);
    }

    string line;
    vector<string> lines;  // To store all lines in memory

    while (getline(file, line)) {
        stringstream ss(line);
        string id, uname, pwd, session;
        getline(ss, id, ',');
        getline(ss, uname, ',');
        getline(ss, pwd, ',');
        getline(ss, session, ',');

        if (uname == username && pwd == password) {
            // Login successful
            session = generateRandomID();
        }

        lines.push_back(id + "," + uname + "," + pwd + "," + session);
    }

    file.close();

    // Write the modified lines back to the file
    ofstream outFile(USER_FILE);
    if (!outFile) {
        return "Failed to open " + string(USER_FILE) + " for writing";
    }

    for (const string& line : lines) {
        outFile << line << endl;
    }

    outFile.close();

    // Check if the login was successful based on the updated session field
    for (const string& line : lines) {
        stringstream ss(line);
        string id, uname, pwd, session;
        getline(ss, id, ',');
        getline(ss, uname, ',');
        getline(ss, pwd, ',');
        getline(ss, session, ',');

        if (uname == username && pwd == password && !session.empty()) {
            return "Login successful. Session ID: " + session;
        }
    }

    return "Login failed";
}

string handle_register_request(const json& data) {
    string username = data["username"];
    string password = data["password"];

    // Kiểm tra username và password không rỗng
    if (username.empty() || password.empty()) {
        return string("Username and password cannot be empty");
    }

    // Đọc dữ liệu từ file users.csv
    ifstream file(USER_FILE);
    if (!file) {
        return "Failed to open " + string(USER_FILE) ;
    }

    string line;
    while (getline(file, line)) {
        // Tách các trường dữ liệu trong dòng
        stringstream ss(line);
        string id, uname, pwd, session;
        getline(ss, id, ',');
        getline(ss, uname, ',');
        getline(ss, pwd, ',');
        getline(ss, session, ',');

        // Kiểm tra sự trùng lặp của username
        if (uname == username) {
            return string("Username already exists");
        }
    }

    // Kiểm tra độ dài mật khẩu
    if (password.length() < 4) {
        return string("Password length must be at least 4 characters");
    }

    // Tạo ID mới
    string newID = generateRandomID();

    // Ghi thông tin tài khoản mới vào file users.csv
    ofstream outfile(USER_FILE, ios::app);
    if (!outfile) {
        return "Failed to open " + string(USER_FILE);
    }

    outfile << newID << "," << username << "," << password << "," << endl;
    outfile.close();

    return string("Registration successful");
}

string handle_logout_request(const json& data) {
    string username = data["username"];

    // Remove the session for the user in the file
    ifstream file(USER_FILE);
    if (!file) {
        return "Failed to open " + string(USER_FILE);
    }

    string line;
    vector<string> lines;  // To store all lines in memory
    bool sessionRemoved = false;

    while (getline(file, line)) {
        stringstream ss(line);
        string id, uname, pwd, session;
        getline(ss, id, ',');
        getline(ss, uname, ',');
        getline(ss, pwd, ',');
        getline(ss, session, ',');

        if (uname == username) {
            // Remove the session for the user
            session = "";
            sessionRemoved = true;
        }

        lines.push_back(id + "," + uname + "," + pwd + "," + session);
    }

    file.close();

    // Write the modified lines back to the file
    ofstream outFile(USER_FILE);
    if (!outFile) {
        return "Failed to open " + string(USER_FILE) + " for writing";
    }

    for (const string& line : lines) {
        outFile << line << endl;
    }

    outFile.close();

    if (sessionRemoved) {
        return "Logout successful";
    } else {
        return "User not found";
    }
}

void send_response(int client_socket, const string& response) {
    send(client_socket, response.c_str(), response.length(), 0);
}

void handle_client(int client_socket) {
    char buffer[1024] = {0};
    int valread = read(client_socket, buffer, 1024);
    string request(buffer);

    // Xử lý yêu cầu từ client
    handle_request(client_socket, request);

    close(client_socket);
}

int main() {
    int server_fd, new_socket;
    struct sockaddr_in address;
    int addr_len = sizeof(address);

    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);
    bind(server_fd, (struct sockaddr *)&address, sizeof(address));

    listen(server_fd, 1024);

    register_routes();

    while (1) {
        new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addr_len);
        if (new_socket < 0) {
            perror("accept");
            exit(EXIT_FAILURE);
        }

        if (fork() == 0) {
            close(server_fd);
            handle_client(new_socket);
            exit(0);
        }
        close(new_socket);
    }

    return 0;
}