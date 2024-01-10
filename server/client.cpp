#include <iostream>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string>

#define PORT 8080

int main() {
    int sock = 0, valread;
    struct sockaddr_in serv_addr;
    // std::string message = R"({"route": "project/all", "data": {"session":"LEnGx-"}})";
    // std::string message = R"({"route": "project/create", "data": {"session":"CSSgo","name":"Project moi"}})";
    // std::string message = R"({"route": "member/get", "data": {"session": "LEnGx", "id_project": "2frwa"}})";
    // std::string message = R"({"route": "member/add", "data": {"session": "LEnGx", "id_project": "2frwa", "id_user":"123ml"}})";
    // std::string message = R"({"route": "member/delete", "data": {"session": "LEnGx", "id_project": "2frwa", "id_user":"123ml"}})";
    // std::string message = R"({"route": "login", "data": {"username": "tuan", "password": "1234"}})";
    // std::string message = R"({"route": "task/get", "data": {"session": "CSSgo", "id_project": "OlDHv"}})";
    // std::string message = R"({"route": "task/create", "data": {"session": "CSSgo", "id_project": "OlDHv", "name": "Task_123", "status": "TODO", "start_date": "2024/1/1", "end_date": "2024/2/3"}})";
    // std::string message = R"({"route": "task/assign", "data": {"session": "CSSgo", "id_task": "9ChM9", "id_user":"asd23"}})";
    // std::string message = R"({"route": "task/update_status", "data": {"session": "CSSgo", "id_task": "9ChM9", "new_status":"DON"}})";
    std::string message = R"({"route": "task/add_comment", "data": {"session": "CSSgo", "id_task": "9ChM9", "comment_text":"Sample comment"}})";

    char buffer[1024] = {0};

    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        std::cout << "Socket creation error" << std::endl;
        return -1;
    }

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);

    if (inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr) <= 0) {
        std::cout << "Invalid address/ Address not supported" << std::endl;
        return -1;
    }

    if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) {
        std::cout << "Connection Failed" << std::endl;
        return -1;
    }

    send(sock, message.c_str(), message.length(), 0);
    valread = read(sock, buffer, 1024);
    std::cout << "Response: " << buffer << std::endl;

    return 0;
}