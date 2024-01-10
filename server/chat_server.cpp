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

#define MAX_LEN 1024

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
    if ((server_socket = socket(AF_INET, SOCK_STREAM, 0)) == -1)
    {
        perror("socket: ");
        exit(-1);
    }

    struct sockaddr_in server;
    server.sin_family = AF_INET;
    server.sin_port = htons(8081);
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

    while (1)
    {
        if ((client_socket = accept(server_socket, (struct sockaddr *)&client, &len)) == -1)
        {
            perror("accept error: ");
            exit(-1);
        }

        char initialMessage[MAX_LEN];
        int bytes_received = recv(client_socket, initialMessage, sizeof(initialMessage), 0);
        if (bytes_received <= 0)
            continue;

        string id_user, id_project;
        string initialMessageStr(initialMessage);
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

    cout << message << endl;

    lock_guard<mutex> guard(chatMembersMutex);
    for (int i = 0; i < chatMembers.size(); i++)
    {
        if (chatMembers[i].socket != client_socket && chatMembers[i].id_project == id_project)
        {
            string username = getUsernameUserById(id_user);
            string sendStr = chatMembers[i].id_user + "|" + username + "|" + id_project + "|" + temp;
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
}

void handle_client(int client_socket, string id_user, string id_project)
{
    char str[MAX_LEN];
    while (1)
    {
        int bytes_received = recv(client_socket, str, sizeof(str), 0);
        if (bytes_received <= 0)
            break;
        if (strcmp(str, "#exit") == 0)
        {
            end_connection(id_user);
            return;
        }
        broadcast_message(string(str), client_socket, id_user, id_project);
    }

    end_connection(id_user);
}