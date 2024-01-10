#include "testmessage.h"
#include "ui_testmessage.h"

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

#include <QThread>

class ReceiveThread : public QThread {
    Q_OBJECT

public:
    int socketFD;

protected:
    void run() override {
        constexpr int BUFFER_SIZE = 1024;
        char buffer[BUFFER_SIZE];

        while (1) {
            int bytes_received = recv(socketFD, buffer, BUFFER_SIZE - 1, 0);
            if (bytes_received <= 0) {
                if (bytes_received == 0) {
                    qDebug() << "Connection closed by the server";
                } else {
                    qDebug() << "Error receiving message";
                }
                break;
            }

            buffer[bytes_received] = '\0';
            QString receivedMessage = QString::fromUtf8(buffer);
            emit messageReceived(receivedMessage);
        }
    }

signals:
    void messageReceived(const QString& message);
};

TestMessage::TestMessage(const std::string& serverIP, int serverPort, QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::TestMessage)
    , serverIP(serverIP), serverPort(serverPort), socketFD(-1), isRunning(false)
{
    ui->setupUi(this);
    socketFD = socket(AF_INET, SOCK_STREAM, 0);
    if (socketFD < 0) {
        perror("Failed to create socket");
        exit(EXIT_FAILURE);
    }
}

TestMessage::~TestMessage()
{
    if (socketFD >= 0) {
        ::close(socketFD);
    }
    delete ui;
}

void TestMessage::on_send_message_btn_clicked()
{
    sendMessage();
}

void TestMessage::showEvent(QShowEvent *event) {
    emit showMessages();

    struct sockaddr_in serverAddress;
    memset(&serverAddress, 0, sizeof(serverAddress));
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_port = htons(serverPort);
    if (inet_pton(AF_INET, serverIP.c_str(), &(serverAddress.sin_addr)) <= 0) {
        perror("Invalid server IP address");
        exit(EXIT_FAILURE);
    }

    // Kết nối tới server
    if (::connect(socketFD, (struct sockaddr*)&serverAddress, sizeof(serverAddress)) < 0) {
        perror("Failed to connect to server");
        exit(EXIT_FAILURE);
    }

    std::string message = "abcde|OlDHv";
    int bytes_sent = send(socketFD, message.c_str(), message.size(), 0);
    if (bytes_sent == -1) {
        qDebug() << "Error sending message";
        return;
    }

    ReceiveThread* receiveThread = new ReceiveThread;
    receiveThread->socketFD = socketFD;
    connect(receiveThread, &ReceiveThread::messageReceived, this, &TestMessage::showMessageInScreen);
    receiveThread->start();

    isRunning = true;

    QWidget::showEvent(event);
}

void TestMessage::hideEvent(QHideEvent *event) {
    emit screenHidden();
    isRunning = false;
    if (socketFD >= 0) {
        ::close(socketFD);
    }

    QWidget::hideEvent(event);
}

void TestMessage::showMessageInScreen(std::string result) {
    QString resultQString = QString::fromStdString(result);
    ui->textEdit->clear();
    ui->textEdit->append(resultQString);
}

void TestMessage::sendMessage() {
    QString message = ui->lineEdit->text();
    ui->lineEdit->clear();

    std::string messageStr = message.toStdString();
    int bytes_sent = send(socketFD, messageStr.c_str(), messageStr.size(), 0);
    if (bytes_sent == -1) {
        qDebug() << "Error sending message";
        return;
    }
    ui->textEdit->append(message);
}

void TestMessage::recvMessage() {
    constexpr int BUFFER_SIZE = 1024;
    char buffer[BUFFER_SIZE];

    while (isRunning) {
        int bytes_received = recv(socketFD, buffer, BUFFER_SIZE - 1, 0);
        if (bytes_received <= 0) {
            if (bytes_received == 0) {
                qDebug() << "Connection closed by the server";
            } else {
                qDebug() << "Error receiving message";
            }
            break;
        }

        buffer[bytes_received] = '\0';
        QString receivedMessage = QString::fromUtf8(buffer);
        ui->textEdit->append(receivedMessage);
    }
}



