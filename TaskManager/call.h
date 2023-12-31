#ifndef CALL_H
#define CALL_H

#endif // CALL_H

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <iostream>

using namespace std;

string call(string message) {
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd == -1) {
        cerr << "Error creating socket" << endl;
        return "";
    }

    sockaddr_in serverAddr{};
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(8080);
    if (inet_pton(AF_INET, "127.0.0.1", &(serverAddr.sin_addr)) <= 0) {
        cerr << "Invalid server address" << endl;
        close(sockfd);
        return "";
    }

    if (connect(sockfd, (struct sockaddr*)&serverAddr, sizeof(serverAddr)) == -1) {
        cerr << "Failed to connect to the server" << endl;
        close(sockfd);
        return "";
    }

    ssize_t sentBytes = send(sockfd, message.c_str(), message.length(), 0);
    if (sentBytes == -1) {
        cerr << "Error sending data" << endl;
        close(sockfd);
        return "";
    }

    constexpr int bufferSize = 1024;
    char buffer[bufferSize];
    ssize_t receivedBytes = recv(sockfd, buffer, bufferSize - 1, 0);
    if (receivedBytes == -1) {
        cerr << "Error receiving data" << endl;
        close(sockfd);
        return "";
    }

    buffer[receivedBytes] = '\0';

    string response(buffer);
    close(sockfd);

    // Store the response as needed
    return response;
}

string performLogin(const string& username, const string& password)
{
    string message = R"({"route": "login", "data": {"username": ")" + username + R"(", "password": ")" + password + "\"}}";
    string res = call(message);
    return res;
}

string performRegister(const string& username, const string& password) {
    string message = R"({"route": "register", "data": {"username": ")" + username + R"(", "password": ")" + password + "\"}}";
    string res = call(message);
    return res;
}
