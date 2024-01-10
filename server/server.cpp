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
#include "message.cpp"
#include "task.cpp"

using json = nlohmann::json;
using namespace std;

// Function Define 
void handle_request(int client_socket, const string& request);

string handle_login_request(const json& data);
string handle_register_request(const json& data);
string handle_logout_request(const json& data);

string handle_get_user_by_id(const json&data);

string handle_get_all_project(const json& data);
string handle_create_project(const json& data);
string handle_delete_project(const json& data);

string handle_member_get_request(const json& data);
string handle_member_add_request(const json& data);
string handle_member_delete_request(const json& data);

string handle_task_get_request(const json& data);
string handle_task_create_request(const json& data);
string handle_task_assign_request(const json& data);
string handle_task_update_status_request(const json& data);
string handle_task_add_comment_request(const json& data);

string handle_chat_get_start(int client_socket, const json& data);

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

    router["user"] = [](int client_socket, const json& data) {
        string response = handle_get_user_by_id(data);
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

    router["project/delete"] = [](int client_socket, const json& data) {
        string response = handle_delete_project(data);
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

    router["task/get"] = [](int client_socket, const json& data) {
        string response = handle_task_get_request(data);
        send_response(client_socket, response);
    };

    router["chat/get"] = [](int client_socket, const json& data) {
        string response = handle_chat_get_start(client_socket, data);
        send_response(client_socket, response);
    };
    
    router["task/create"] = [](int client_socket, const json& data) {
        string response = handle_task_create_request(data);
        send_response(client_socket, response);
    };

    router["task/assign"] = [](int client_socket, const json& data) {
        string response = handle_task_assign_request(data);
        send_response(client_socket, response);
    };

    router["task/update_status"] = [](int client_socket, const json& data) {
        string response = handle_task_update_status_request(data);
        send_response(client_socket, response);
    };

    router["task/add_comment"] = [](int client_socket, const json& data) {
        string response = handle_task_add_comment_request(data);
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
    vector<Project> projects = getProjectsByUserId(userId);

    json responseData;
    responseData["success"] = 1;
    responseData["message"] = "Successful";
    responseData["data"] = json::array();

    for (const Project& project : projects) {
        json projectData;
        projectData["id"] = project.id;
        projectData["name"] = project.name;
        projectData["id_owner"] = project.ownerId;
        responseData["data"].push_back(projectData);
    }

    return responseData.dump();
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

string handle_delete_project(const json& data) {
    return "";
}

string handle_login_request(const json& data) {
    string username = data["username"];
    string password = data["password"];

    if (username.empty() || password.empty()) {
        return init_response(false, string("Username and password cannot be empty"), "");
    } 

    ifstream file(USER_FILE);
    if (!file) {
        return init_response(false, "[ERROR]: Failed to open " + string(USER_FILE), "");
    }

    string line;
    vector<string> lines;

    while (getline(file, line)) {
        stringstream ss(line);
        string id, uname, pwd, session;
        getline(ss, id, ',');
        getline(ss, uname, ',');
        getline(ss, pwd, ',');
        getline(ss, session, ',');

        if (uname == username && pwd == password) {
            session = generateRandomID();
        }

        lines.push_back(id + "," + uname + "," + pwd + "," + session);
    }

    file.close();

    ofstream outFile(USER_FILE);
    if (!outFile) {
        return init_response(false, "[ERROR]: Failed to open " + string(USER_FILE) + " for writing", "");
    }

    for (const string& line : lines) {
        outFile << line << endl;
    }

    outFile.close();

    for (const string& line : lines) {
        stringstream ss(line);
        string id, uname, pwd, session;
        getline(ss, id, ',');
        getline(ss, uname, ',');
        getline(ss, pwd, ',');
        getline(ss, session, ',');

        if (uname == username && pwd == password && !session.empty()) {
            json data = json::object();
            data["id"] = id;
            data["username"] = uname;
            data["password"] = pwd;
            data["session"] = session;
            return init_response(true, "Login successfull", data.dump());
        }
    }
  
    return init_response(false, "[ERROR]: User not found!", "");
}

string handle_register_request(const json& data) {
    string username = data["username"];
    string password = data["password"];

    if (username.empty() || password.empty()) {
        return init_response(false, "Username and password cannot be empty", "");
    }

    ifstream file(USER_FILE);
    if (!file) {
        return init_response(false,"Failed to open " + string(USER_FILE), "");
    }

    string line;
    while (getline(file, line)) {
        stringstream ss(line);
        string id, uname, pwd, session;
        getline(ss, id, ',');
        getline(ss, uname, ',');
        getline(ss, pwd, ',');
        getline(ss, session, ',');

        if (uname == username) {
            return init_response(false, "Username already exists", "");
        }
    }

    if (password.length() < 4) {
        return init_response(false, "Password length must be at least 4 characters", "");
    }

    string newID = generateRandomID();

    ofstream outfile(USER_FILE, ios::app);
    if (!outfile) {
        return init_response(false, "Failed to open " + string(USER_FILE), "");
    }

    outfile << newID << "," << username << "," << password << "," << endl;
    outfile.close();

    return init_response(true, "Registration successful", "");
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

string handle_get_user_by_id(const json& data) {
    string id = data["id"];

    if (id.empty()) return init_response(false, "User not found", "");

    string user = getUserById(id);

    if (user.empty()) return init_response(false, "User not found", "");

    return init_response(true, "User found", user);
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

string handle_task_get_request(const json& data) {
    string session = data["session"];
    string id_project = data["id_project"];
    if (session.empty()) return init_response(false, "Field session must not be empty", "");
    if (id_project.empty()) return init_response(false, "Field id_project must not be empty", "");

    string id_user = getIdUserBySession(session);
    if (id_user.empty()) init_response(false, "User not found", "");

    return getAllTasksByProjectID(id_project);
}

string handle_task_create_request(const json& data) {
    string session = data["session"];
    string id_project = data["id_project"];
    string name = data["name"];
    string status = data["status"];
    string start_date = data["start_date"];
    string end_date = data["end_date"];

    if (session.empty()) return init_response(false, "Field session must not be empty", "");
    if (id_project.empty()) return init_response(false, "Field id_project must not be empty", "");
    if (name.empty()) return init_response(false, "Field name must not be empty", "");
    if (status.empty()) status = "TODO";
    if (start_date.empty()) start_date = getCurrentDate();
    if (end_date.empty()) return init_response(false, "Field end_date must not be empty", "");

    string id_user = getIdUserBySession(session);

    if (id_user.empty()) init_response(false, "User not found", "");
    if (!isOwnerProject(id_user, id_project)) init_response(false, "Permission denied", "");

    return createNewTask(id_user, id_project, name, status, start_date, end_date);
}

string handle_task_assign_request(const json& data) {
    string session = data["session"];
    string id_task = data["id_task"];
    string id_assign = data["id_user"];

    if (session.empty()) return init_response(false, "Field session must not be empty", "");
    if (id_task.empty()) return init_response(false, "Field id_task must not be empty", "");
    if (id_assign.empty()) return init_response(false, "Field id_user must not be empty", "");

    string id_user = getIdUserBySession(session);

    if (id_user.empty()) init_response(false, "User not found", "");
    if (!isOwnerTask(id_user, id_task)) init_response(false, "Permission denied", "");

    return assignTaskToUser(id_task, id_assign);
}

string handle_task_update_status_request(const json& data) {
    string session = data["session"];
    string id_task = data["id_task"];
    string new_status = data["new_status"];

    if (session.empty()) return init_response(false, "Field session must not be empty", "");
    if (id_task.empty()) return init_response(false, "Field id_task must not be empty", "");
    if (new_status.empty()) return init_response(false, "Field new_status must not be empty", "");

    string id_user = getIdUserBySession(session);

    if (id_user.empty()) init_response(false, "User not found", "");
    // if (!isOwnerTask(id_user, id_task)) init_response(false, "Permission denied", "");

    return updateStatusByTaskId(id_task, new_status);
}

string handle_task_add_comment_request(const json& data) {
    string session = data["session"];
    string id_task = data["id_task"];
    string new_comment = data["comment_text"];

    if (session.empty()) return init_response(false, "Field session must not be empty", "");
    if (id_task.empty()) return init_response(false, "Field id_task must not be empty", "");
    if (new_comment.empty()) return init_response(false, "Field comment_text must not be empty", "");

    string id_user = getIdUserBySession(session);

    if (id_user.empty()) init_response(false, "User not found", "");
    if (!isOwnerTask(id_user, id_task)) init_response(false, "Permission denied", "");

    return editCommentByTaskId(id_task, new_comment);
}

string handle_chat_get_start(int client_socket, const json& data) {
    string session = data["session"];
    string idProject = data["id_project"];

    string idUser = getIdUserBySession(session);
    if (idUser.empty()) {
        return R"({"success": 0,"message": "User not found","data": []})";
    }

    // send all old message in project to client
    string messages = getAllMessagesByProjectId(idProject);

    return init_response(true, "Get message", messages);
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

    cout << "Server is running on port " << PORT << endl;

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