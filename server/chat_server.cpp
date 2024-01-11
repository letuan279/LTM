#include <bits/stdc++.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <errno.h>
#include <string.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <thread>
#include <mutex>

#include "utils.hpp"

#include "user.cpp"
#include "message.cpp"

#define MAX_LEN 10000

using namespace std;

// Chat app define
struct ChatConnectionMember {
    string id_user;
    int socket;
    string id_project;
    thread th;
};

vector<ChatConnectionMember> chatMembers;
mutex chatMembersMutex;

int broadcast_message(string message, int client_socket, string id_user, string id_project);
void end_connection(string id_user);
void handle_client(int client_socket, string id_user, string id_project);

int main()
{
    int server_socket;
    int port = 8081;
    if ((server_socket = socket(AF_INET, SOCK_STREAM, 0)) == -1)
    {
        perror("socket: ");
        exit(-1);
    }

    struct sockaddr_in server;
    server.sin_family = AF_INET;
    server.sin_port = htons(port);
    server.sin_addr.s_addr = INADDR_ANY;
    bzero(&server.sin_zero, sizeof(server.sin_zero));

    if (bind(server_socket, (struct sockaddr *)&server, sizeof(struct sockaddr_in)) == -1)
    {
        perror("bind error: ");
        exit(-1);
    }

    if (listen(server_socket, 8) == -1)
    {
        perror("listen error: ");
        exit(-1);
    }

    struct sockaddr_in client;
    int client_socket;
    unsigned int len = sizeof(sockaddr_in);

    cout << "Server is running on port " << port << endl;

    while (1)
    {
        if ((client_socket = accept(server_socket, (struct sockaddr *)&client, &len)) == -1)
        {
            perror("accept error: ");
            exit(-1);
        }

        char buffer[1024];
        ssize_t receivedBytes = recv(client_socket, buffer, 1024 - 1, 0);
        if (receivedBytes == -1) {
            continue;
        }

        buffer[receivedBytes] = '\0';

        string initialMessageStr(buffer);
        string id_user, id_project;
        size_t separatorPos = initialMessageStr.find('|');
        if (separatorPos != string::npos) {
            id_user = initialMessageStr.substr(0, separatorPos);
            id_project = initialMessageStr.substr(separatorPos + 1);
        }

        thread t(handle_client, client_socket, id_user, id_project);

        lock_guard<mutex> guard(chatMembersMutex);
        chatMembers.push_back({id_user, client_socket, id_project, move(t)});     
        cout << id_user << " join project: " << id_project << endl;
        cout << "Online: " << chatMembers.size() << endl;
    }

    for (int i = 0; i < chatMembers.size(); i++)
    {
        if (chatMembers[i].th.joinable())
            chatMembers[i].th.join();
        close(chatMembers[i].socket);
    }

    close(server_socket);
    return 0;
}

int broadcast_message(string message, int client_socket, string id_user, string id_project)
{
    char temp[MAX_LEN];
    strcpy(temp, message.c_str());
    string time = getCurrentTime();

    addMessage(id_project, id_user, message, time);

    lock_guard<mutex> guard(chatMembersMutex);
    for (int i = 0; i < chatMembers.size(); i++)
    {
        if (chatMembers[i].socket != client_socket && chatMembers[i].id_project == id_project)
        {
            string username = getUsernameUserById(id_user);
            string sendStr = username + "|" + time + "|" + temp;
            const char* sendPtr = sendStr.c_str();
            size_t sendLen = strlen(sendPtr);
            send(chatMembers[i].socket, sendPtr, sendLen, 0);
        }
    }
    return 0;
}

void end_connection(string id_user)
{
    lock_guard<mutex> guard(chatMembersMutex);
    for (int i = 0; i < chatMembers.size(); i++)
    {
        if (chatMembers[i].id_user == id_user)
        {
            chatMembers[i].th.detach();
            chatMembers.erase(chatMembers.begin() + i);
            close(chatMembers[i].socket);
            break;
        }
    }
    int result = deleteSession(id_user);
    if(!result) {
        cout << "Cannot logout!" << endl;
    }
}

void handle_client(int client_socket, string id_user, string id_project)
{
    while (1)
    {
        char buffer[1024];
        ssize_t receivedBytes = recv(client_socket, buffer, 1024 - 1, 0);
        if (receivedBytes == -1) {
            break;;
        }

        buffer[receivedBytes] = '\0';
        string str(buffer);

        if (strcmp(str.c_str(), "#exit") == 0)
        {
            end_connection(id_user);
            return;
        }
        broadcast_message(str, client_socket, id_user, id_project);
    }

    end_connection(id_user);
}