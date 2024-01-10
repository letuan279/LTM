#ifndef CALL_CHAT_H
#define CALL_CHAT_H

#endif // CALL_CHAT_H

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <iostream>

using namespace std;

int callChat(string id_user, string id_project) {
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd == -1) {
        cerr << "Error creating socket" << endl;
        return -1;
    }

    sockaddr_in serverAddr{};
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(8081);
    if (inet_pton(AF_INET, "127.0.0.1", &(serverAddr.sin_addr)) <= 0) {
        cerr << "Invalid server address" << endl;
        close(sockfd);
        return -1;
    }

    if (connect(sockfd, (struct sockaddr*)&serverAddr, sizeof(serverAddr)) == -1) {
        cerr << "Failed to connect to the server" << endl;
        close(sockfd);
        return -1;
    }

    string message = id_user + "|" + id_project;
    ssize_t sentBytes = send(sockfd, message.c_str(), message.length(), 0);
    if (sentBytes == -1) {
        cerr << "Error sending data" << endl;
        close(sockfd);
        return -1;
    }

    return sockfd;
}
