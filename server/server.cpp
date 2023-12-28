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
#include "config.hpp"
#include "utils.hpp"

#include "project.cpp"
#include "user.cpp"
#include "member.cpp"

using json = nlohmann::json;
using namespace std;

// Function Define 
void handle_request(int client_socket, const string& request);

string handle_login_request(const json& data);
string handle_register_request(const json& data);
string handle_logout_request(const json& data);
string handle_get_all_project(const json& data);
string handle_create_project(const json& data);

string handle_member_get_request(const json& data);
string handle_member_add_request(const json& data);
string handle_member_delete_request(const json& data);

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

    router["project/all"] = [](int client_socket, const json& data) {
        string response = handle_get_all_project(data);
        send_response(client_socket, response);
    };

    router["project/create"] = [](int client_socket, const json& data) {
        string response = handle_create_project(data);
        send_response(client_socket, response);
    };

    router["member/get"] = [](int client_socket, const json& data) {
        string response = handle_member_get_request(data);
        send_response(client_socket, response);
    };

    router["member/add"] = [](int client_socket, const json& data) {
        string response = handle_member_add_request(data);
        send_response(client_socket, response);
    };

    router["member/delete"] = [](int client_socket, const json& data) {
        string response = handle_member_delete_request(data);
        send_response(client_socket, response);
    };
}

void handle_request(int client_socket, const string& request) {
    json json_obj = json::parse(request);

    if (json_obj.contains("route") && json_obj.contains("data")) {
        string route = json_obj["route"];
        json data = json_obj["data"];

        if (router.find(route) != router.end()) {
            cout << "API: " << route << endl;
            router[route](client_socket, data);
        } else {
            send_response(client_socket, "Invalid route");
        }
    } else {
        send_response(client_socket, "Invalid JSON format");
    }
}

string handle_get_all_project(const json& data) {
    json response;
    string session = data["session"];
    if (session.empty())
        return init_response(false, "Session is not availble", "");

    string userId = getIdUserBySession(session);
    string projects = getAllProjectById(userId);

    return projects;
}

string handle_create_project(const json& data) {
    json response;
    string session = data["session"];
    string name = data["name"];
    if (session.empty())
        return init_response(false, "Session is not availble", "");
    if (name.empty())
        return init_response(false, "Project name can not be empty", "");

    string userId = getIdUserBySession(session);
    string res = createProject(userId, name);

    return res;
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

string handle_member_get_request(const json& data) {
    string session = data["session"];
    string idProject = data["id_project"];
    string idUser = getIdUserBySession(session);

    if (idUser.empty()) {
        return R"({"success": 0,"message": "User not found","data": []})";
    }

    vector<MemberData> members = getAllMembers(idProject);

    json responseData;
    responseData["success"] = 1;
    responseData["message"] = "Successful";
    responseData["data"] = json::array();

    for (const MemberData& member : members) {
        json memberData;
        memberData["id"] = member.id;
        memberData["username"] = member.username;
        responseData["data"].push_back(memberData);
    }

    return responseData.dump();
}

string handle_member_add_request(const json& data) {
    string session = data["session"];
    string idUser = data["id_user"];
    string idProject = data["id_project"];

    string idUserRequest = getIdUserBySession(session);

    if (idUserRequest.empty()) {
        return R"({"success": 0,"message": "User not found","data": []})";
    }

    ifstream file(MEMBER_FILE);
    string line;
    vector<Member> members;

    while (getline(file, line)) {
        istringstream iss(line);
        string id, id_user, id_project;

        if (getline(iss, id, ',') &&
            getline(iss, id_user, ',') &&
            getline(iss, id_project, ',')) {

            members.push_back({ id, id_user, id_project });
        }
    }

    file.close();

    // Check if the member already exists
    for (const auto& member : members) {
        if (member.id_user == idUser && member.id_project == idProject) {
            return R"({"success": 0,"message": "Member already exists","data": []})";
        }
    }

    // Add the new member
    std::ofstream outputFile(MEMBER_FILE, std::ios::app);
    outputFile << generateRandomID() << "," << idUser << "," << idProject << std::endl;
    outputFile.close();

    vector<MemberData> membersData = getAllMembers(idProject);

    json responseData;
    responseData["success"] = 1;
    responseData["message"] = "Member added successfully";
    responseData["data"] = json::array();

    for (const MemberData& member : membersData) {
        json memberData;
        memberData["id"] = member.id;
        memberData["username"] = member.username;
        responseData["data"].push_back(memberData);
    }

    return responseData.dump();
}

string handle_member_delete_request(const json& data) {
    string session = data["session"];
    string idUser = data["id_user"];
    string idProject = data["id_project"];

    string idUserRequest = getIdUserBySession(session);

    if (idUserRequest.empty()) {
        return R"({"success": 0,"message": "User not found","data": []})";
    }

    ifstream file(MEMBER_FILE);
    string line;
    vector<Member> members;

    while (getline(file, line)) {
        istringstream iss(line);
        string id, id_user, id_project;

        if (getline(iss, id, ',') &&
            getline(iss, id_user, ',') &&
            getline(iss, id_project, ',')) {

            members.push_back({ id, id_user, id_project });
        }
    }

    file.close();

    // Check if the member exists and delete it
    bool memberFound = false;
    for (auto it = members.begin(); it != members.end(); ++it) {
        if (it->id_user == idUser && it->id_project == idProject) {
            members.erase(it);
            memberFound = true;
            break;
        }
    }

    if (!memberFound) {
        return R"({"success": 0,"message": "Member not found","data": []})";
    }

    // Write the updated members list back to the file
    ofstream outputFile(MEMBER_FILE);
    for (const auto& member : members) {
        outputFile << member.id << "," << member.id_user << "," << member.id_project << endl;
    }
    outputFile.close();

    vector<MemberData> membersData = getAllMembers(idProject);

    json responseData;
    responseData["success"] = 1;
    responseData["message"] = "Member deleted successfully";
    responseData["data"] = json::array();

    for (const MemberData& member : membersData) {
        json memberData;
        memberData["id"] = member.id;
        memberData["username"] = member.username;
        responseData["data"].push_back(memberData);
    }

    return responseData.dump();
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