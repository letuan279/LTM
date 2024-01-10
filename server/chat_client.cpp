#include <bits/stdc++.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <errno.h>
#include <string.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <thread>
#include <signal.h>
#include <mutex>
#include <nlohmann/json.hpp>
#include <chrono>
#define MAX_LEN 1024

using namespace std;
using json = nlohmann::json;

bool exit_flag=false;
thread t_send, t_recv;
int client_socket;
constexpr int bufferSize = 1024;

struct User
{
    string id;
    string username;
    string password;
    string session;
};

struct Project
{
    string id;
    string name;
};

User user;
vector<Project> projects;
Project projectChoosen;

void catch_ctrl_c(int signal);
int eraseText(int cnt);
void send_message(int client_socket);
void recv_message(int client_socket);

string call(string message, int port) {
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd == -1) {
        cerr << "Error creating socket" << endl;
        return "";
    }

    sockaddr_in serverAddr{};
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(port);
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

    return response;
}

string getTimeAgo(const string& timeString)
{
    chrono::system_clock::time_point currentTime = chrono::system_clock::now();
    time_t currentTime_t = chrono::system_clock::to_time_t(currentTime);

    tm* currentTimeStruct = localtime(&currentTime_t);
    istringstream iss(timeString);
    tm messageTimeStruct = {};

    iss >> get_time(&messageTimeStruct, "%Y-%m-%d %H:%M:%S");

    chrono::system_clock::time_point messageTime = chrono::system_clock::from_time_t(mktime(&messageTimeStruct));
    chrono::duration<double> timeDifference = currentTime - messageTime;

    int minutesAgo = chrono::duration_cast<chrono::minutes>(timeDifference).count();
    return to_string(minutesAgo) + " phut truoc";
}

string formatMessage(const json& messageJson)
{
    string username = messageJson["username"];
    string content = messageJson["content"];
    string time = getTimeAgo(messageJson["time"]);

    return username + " (" + time + ") : " + content + "\n";
}

string getMessages(string session, string id_project) {
    // Get all message
    string getMessageString = R"({"route": "chat/get", "data": {"session": ")"
                                + string(session) +
                                R"(", "id_project": ")" + string(id_project) +
                                R"("}})";
    string res2 = call(getMessageString, 8080);
    cout << "---------------------CHAT ROOM------------------------" << endl;
    json jsonData = json::parse(res2);
    string messages = "";
    if (jsonData["success"] == 1)
    {
        for (const auto& messageData : jsonData["data"])
        {
            string formattedMessage = formatMessage(messageData);
            messages += formattedMessage;
        }
    }
    else
    {
        cout << "Khong the truy cap thong tin tin nhan" << endl;
        return "";
    }

    return messages;
}

int main()
{
	signal(SIGINT, catch_ctrl_c);

    // Login
    while (1)
    {
        char username[MAX_LEN], password[MAX_LEN];
        cout<<"Username : ";
        cin.getline(username,MAX_LEN);
        cout<<"Password : ";
        cin.getline(password,MAX_LEN);

        string loginMessage = R"({"route": "login", "data": {"username": ")"
                                + string(username) +
                                R"(", "password": ")" + string(password) +
                                R"("}})";
        string res = call(loginMessage, 8080);

        json jsonData = json::parse(res);
        int success = jsonData["success"];
        string message = jsonData["message"];
        if(success == 0) {
            cout << message << endl;
        } else {
            user.id = jsonData["data"]["id"];
            user.username = jsonData["data"]["username"];
            user.password = jsonData["data"]["password"];
            user.session = jsonData["data"]["session"];
            cout << message << endl;

            // get all project
            string getProjectMessage = R"({"route": "project/all", "data": {"session": ")"
                                + string(user.session) + R"("}})";
            string res = call(getProjectMessage, 8080);
            json jsonData = json::parse(res);
            json dataArray = jsonData["data"];
            for (const auto& item : dataArray) {
                string id = item["id"];
                string name = item["name"];
                projects.push_back({id, name});
            }
            break;
        }
    }

    if(projects.size() == 0) {
        cout << "Khong co du an nao!" << endl;
        return 0;
    }
	
    // Select project
    while(1){
        int index = 1;
        for (const auto& project : projects)
        {
            cout << index << ". " << project.name << endl;
            index++;
        }
        int choice;
        cout << "Chọn một dự án: ";
        cin >> choice;
        if (choice >= 1 && choice <= projects.size())
        {
            const Project& selectedProject = projects[choice - 1];
            cout << "ID của dự án \"" << selectedProject.name << "\" là: " << selectedProject.id << endl;
            projectChoosen.id = selectedProject.id;
            projectChoosen.name = selectedProject.name;
            break;
        }
        else
        {
            cout << "Lựa chọn không hợp lệ." << endl;
        }
    }

    // Get all message
    cout << getMessages(user.session, projectChoosen.id);

    // Join chat
    if((client_socket=socket(AF_INET,SOCK_STREAM,0))==-1)
	{
		perror("socket: ");
		exit(-1);
	}

	struct sockaddr_in client;
	client.sin_family=AF_INET;
	client.sin_port=htons(8081);
	client.sin_addr.s_addr=inet_addr("127.0.0.1");
	bzero(&client.sin_zero,0);

	if((connect(client_socket,(struct sockaddr *)&client,sizeof(struct sockaddr_in)))==-1)
	{
		perror("connect: ");
		exit(-1);
	}

    string joinChatString = user.id + "|" + projectChoosen.id;
    send(client_socket, joinChatString.c_str(), joinChatString.length(), 0);
	thread t1(send_message, client_socket);
	thread t2(recv_message, client_socket);

	t_send=move(t1);
	t_recv=move(t2);

	if(t_send.joinable())
		t_send.join();
	if(t_recv.joinable())
		t_recv.join();
			
	return 0;
}

void catch_ctrl_c(int signal) 
{
    cout << "ctrl_c" << endl;
	char str[MAX_LEN]="#exit";
	send(client_socket,str,sizeof(str),0);
	exit_flag=true;
	t_send.detach();
	t_recv.detach();
	close(client_socket);
	exit(signal);
}

int eraseText(int cnt)
{
	char back_space=8;
	for(int i=0; i<cnt; i++)
	{
		cout<<back_space;
    }
    return 0;
}

void send_message(int client_socket)
{
	while(1)
	{
		cout << "Enter message : ";
		cout << "Enter message 2: ";
		char str[MAX_LEN];
		cin.getline(str,MAX_LEN);
        string sendMess = string(str);
		send(client_socket,sendMess.c_str(),sendMess.length(),0);
		if(strcmp(str,"#exit")==0)
		{
			exit_flag=true;
			t_recv.detach();	
			close(client_socket);
			return;
		}	
	}		
}

void recv_message(int client_socket)
{
	while(1)
	{
		if(exit_flag)
			return;

        char buffer[1024];
        ssize_t receivedBytes = recv(client_socket, buffer, bufferSize - 1, 0);
        if (receivedBytes == -1) {
            continue;
        }

        buffer[receivedBytes] = '\0';

        string response(buffer);

        cout << response << endl;
        fflush(stdout);
	}	
}
