// #include "mainwindow.h"

#include <QApplication>
#include <QThread>
#include <QCoreApplication>
#include <QLocale>
#include <QTranslator>
#include <QDebug>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QString>
#include <QMessageBox>
#include <QtWidgets>

#include "loginscreen.h"
#include "registerscreen.h"
#include "projectlistscreen.h"
#include "projectdetails.h"

#include "call.h"

using namespace std;

// Define type
struct Account {
    string id;
    string username;
    string password;
    string session;
};
struct Project {
    string id;
    string name;
    string id_owner;
    string owner;
};
struct Task {
    string id;
    string id_project;
    string id_manager;
    string name;
    string status;
    string id_assign;
    string comment;
    string start_date;
    string end_date;
};

// Data
Account acc = {"", "", "", ""};
std::vector<Project> projects;
Project currProject;
std::vector<Task> currTask;
std::vector<Account> currMember;

// Action define

string parseMessages(const string& res)
{
    QString jsonString = QString::fromStdString(res);

    QJsonDocument jsonDoc = QJsonDocument::fromJson(jsonString.toUtf8());
    if (!jsonDoc.isNull()) {
        if (jsonDoc.isObject()) {
            QJsonObject jsonObj = jsonDoc.object();

            int success = jsonObj["success"].toInt();
            if (success == 1) {
                QJsonArray dataArray = jsonObj["data"].toArray();
                QString messagesString;
                for (const QJsonValue& value : dataArray) {
                    QJsonObject messageObj = value.toObject();
                    QString content = messageObj["content"].toString();
                    QString username = messageObj["username"].toString();
                    QString time = messageObj["time"].toString();
                    QString messageDetails = QString("Username: %1\nTime: %2\nContent: %3\n\n")
                                                 .arg(username, time, content);

                    messagesString.append(messageDetails);
                }
                return messagesString.toStdString();
            }
        }
    }

    return "";
}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QMainWindow window;

    // Screen
    LoginScreen loginScreen;
    RegisterScreen registerScreen;
    ProjectListScreen projectListScreen;
    ProjectDetails projectDetailsScreen;

    QObject::connect(&loginScreen, &LoginScreen::moveToRegisterClicked, [&]() {
        registerScreen.show();
        loginScreen.hide();
    });

    QObject::connect(&registerScreen, &RegisterScreen::moveToLoginClicked, [&]() {
        loginScreen.show();
        registerScreen.hide();
    });

    QObject::connect(&loginScreen, &LoginScreen::loginButtonClicked, [&](const QString& username, const QString& password) {
        std::string usernameStr = username.toStdString();
        std::string passwordStr = password.toStdString();
        std::string res = performLogin(usernameStr, passwordStr);

        QString jsonString = QString::fromStdString(res);
        QJsonDocument jsonDoc = QJsonDocument::fromJson(jsonString.toUtf8());
        if (!jsonDoc.isNull()) {
            if (jsonDoc.isObject()) {
                QJsonObject jsonObj = jsonDoc.object();
                int success = jsonObj["success"].toInt();
                QString message = jsonObj["message"].toString();
                if(!success){
                    QMessageBox::critical(nullptr, "Error", message);
                } else {
                    QJsonObject dataObj = jsonObj["data"].toObject();
                    acc.id = dataObj["id"].toString().toStdString();
                    acc.username = dataObj["username"].toString().toStdString();
                    acc.password = dataObj["password"].toString().toStdString();
                    acc.session = dataObj["session"].toString().toStdString();
                    loginScreen.hide();
                    projectListScreen.show();
                    // QMessageBox::information(nullptr, "Success", message);
                }
            }
        }
    });

    QObject::connect(&registerScreen, &RegisterScreen::registerButtonClicked, [&](const QString& username, const QString& password) {
        string usernameStr = username.toStdString();
        string passwordStr = password.toStdString();
        string res = performRegister(usernameStr, passwordStr);

        QString jsonString = QString::fromStdString(res);
        QJsonDocument jsonDoc = QJsonDocument::fromJson(jsonString.toUtf8());
        if (!jsonDoc.isNull()) {
            if (jsonDoc.isObject()) {
                QJsonObject jsonObj = jsonDoc.object();
                int success = jsonObj["success"].toInt();
                QString message = jsonObj["message"].toString();
                if(!success){
                    QMessageBox::critical(nullptr, "Error", message);
                } else {
                    registerScreen.hide();
                    loginScreen.show();
                    QMessageBox::information(nullptr, "Success", message);
                }
            }
        }
    });

    loginScreen.show();

    QObject::connect(&projectListScreen, &ProjectListScreen::widgetShown, [&]() {
        std::string res = performGetProjectList(acc.session);
        QString jsonString = QString::fromStdString(res);
        QJsonDocument jsonDoc = QJsonDocument::fromJson(jsonString.toUtf8());
        if (!jsonDoc.isNull()) {
            if (jsonDoc.isObject()) {
                QJsonObject jsonObj = jsonDoc.object();
                int success = jsonObj["success"].toInt();
                QString message = jsonObj["message"].toString();
                if (!success) {
                    QMessageBox::critical(nullptr, "Error", message);
                } else {
                    QJsonArray dataArr = jsonObj["data"].toArray();
                    QTableView *tableView = projectListScreen.findChild<QTableView*>("project_list");
                    QStandardItemModel *model = new QStandardItemModel(&window);

                    model->setHorizontalHeaderLabels({ "ProjectId", "Name", "Owner", "Action" });

                    qDebug() << "Loading projects : " << dataArr.size();

                    for (int i = 0; i < dataArr.size(); i++) {
                        QJsonObject prjObj = dataArr[i].toObject();
                        Project prjN;
                        prjN.id = prjObj["id"].toString().toStdString();
                        prjN.name = prjObj["name"].toString().toStdString();
                        prjN.id_owner = prjObj["id_owner"].toString().toStdString();

                        std::string user_res = performGetUserById(prjN.id_owner);
                        QString jsonString = QString::fromStdString(user_res);
                        QJsonDocument jsonDoc = QJsonDocument::fromJson(jsonString.toUtf8());
                        if (!jsonDoc.isNull() && jsonDoc.isObject()) {
                            QJsonObject jsonObj = jsonDoc.object();
                            int success = jsonObj["success"].toInt();
                            if (success) {
                                QJsonObject jsonData = jsonObj["data"].toObject();
                                string owner = jsonData["username"].toString().toStdString();
                                if (!owner.empty()) prjN.owner = owner;
                            }
                        }

                        projects.push_back(prjN);

                        QStandardItem *idItem = new QStandardItem(QString::fromStdString(prjN.id));
                        QStandardItem *nameItem = new QStandardItem(QString::fromStdString(prjN.name));
                        QString owner = prjN.id_owner == acc.id ? QString::fromStdString("You") : QString::fromStdString(prjN.owner);
                        QStandardItem *ownerItem = new QStandardItem(owner);
                        model->setItem(i, 0, idItem);
                        model->setItem(i, 1, nameItem);
                        model->setItem(i, 2, ownerItem);
                    }

                    tableView->setModel(model);
                }
            }
        }
    });

    QObject::connect(&projectListScreen, &ProjectListScreen::logout, [&]() {
        string res = performLogout(acc.session);

        QString jsonString = QString::fromStdString(res);
        QJsonDocument jsonDoc = QJsonDocument::fromJson(jsonString.toUtf8());
        if (!jsonDoc.isNull()) {
            if (jsonDoc.isObject()) {
                QJsonObject jsonObj = jsonDoc.object();
                int success = jsonObj["success"].toInt();
                QString message = jsonObj["message"].toString();
                if(!success){
                    QMessageBox::critical(nullptr, "Error", message);
                } else {
                    projectListScreen.hide();
                    loginScreen.show();
                    QMessageBox::information(nullptr, "Success", message);
                }
            }
        }
    });

    QPushButton *chatBtn = projectDetailsScreen.findChild<QPushButton*>("chat_btn"); // 0
    QPushButton *memberBtn = projectDetailsScreen.findChild<QPushButton*>("member_btn"); // 1
    QPushButton *taskBtn = projectDetailsScreen.findChild<QPushButton*>("task_btn"); // 2

    QStackedWidget *projectStackWidget = projectDetailsScreen.findChild<QStackedWidget*>("project_stackwidget");

    QWidget *chatWidget = projectDetailsScreen.findChild<QWidget*>("chat");
    QWidget *memberWidget = projectDetailsScreen.findChild<QWidget*>("member");
    QWidget *taskWidget = projectDetailsScreen.findChild<QWidget*>("task");

    int chat_index = projectStackWidget->indexOf(chatWidget);
    int member_index = projectStackWidget->indexOf(memberWidget);
    int task_index = projectStackWidget->indexOf(taskWidget);

    QObject::connect(chatBtn, &QPushButton::clicked, [projectStackWidget, chat_index]() {
        projectStackWidget->setCurrentIndex(chat_index);
        qDebug() << "Change to Chat Widget";
    });
    QObject::connect(memberBtn, &QPushButton::clicked, [projectStackWidget, member_index]() {
        projectStackWidget->setCurrentIndex(member_index);
        qDebug() << "Change to Member Widget";
    });
    QObject::connect(taskBtn, &QPushButton::clicked, [projectStackWidget, task_index]() {
        projectStackWidget->setCurrentIndex(task_index);
        qDebug() << "Change to Task Widget";
    });

    QPushButton *createProjectBtn = projectListScreen.findChild<QPushButton*>("create_project_btn");

    QObject::connect(createProjectBtn, &QPushButton::clicked, [&]() {

    });


    QObject::connect(&projectListScreen, &ProjectListScreen::doubleClick, [&](const QString& id) {
        qDebug() << "Double click " << id;
        currMember.clear();
        currTask.clear();
        currProject.id.clear();
        currProject.name.clear();
        currProject.id_owner.clear();
        currProject.owner.clear();

        auto it = std::find_if(projects.begin(), projects.end(), [&](const Project& p) {
            return p.id == id.toStdString();
        });

        if (it != projects.end()) {
            currProject.id = it->id;
            currProject.name = it->name;
            currProject.id_owner = it->id_owner;
            currProject.owner = it->owner;

            projectStackWidget->setCurrentIndex(task_index);
            projectDetailsScreen.show();
        }
    });

    QObject::connect(&projectDetailsScreen, &ProjectDetails::widgetShown, [&]() {
        // Get member list
        std::string member_res = performGetMemberList(acc.session, currProject.id);
        QString memberJsonString = QString::fromStdString(member_res);
        QJsonDocument memberJsonDoc = QJsonDocument::fromJson(memberJsonString.toUtf8());
        if (!memberJsonDoc.isNull()) {
            if (memberJsonDoc.isObject()) {
                QJsonObject jsonObj = memberJsonDoc.object();
                int success = jsonObj["success"].toInt();
                QString message = jsonObj["message"].toString();
                if (!success) {
                    QMessageBox::critical(nullptr, "Error", message);
                } else {
                    QJsonArray dataArr = jsonObj["data"].toArray();
                    QTableView *tableView = memberWidget->findChild<QTableView*>("member_table");
                    QStandardItemModel *model = new QStandardItemModel(&window);

                    model->setHorizontalHeaderLabels({ "UserId", "Username", "Action" });

                    qDebug() << "Loading members : " << dataArr.size();

                    for (int i = 0; i < dataArr.size(); i++) {
                        QJsonObject userObj = dataArr[i].toObject();
                        Account user;
                        user.id = userObj["id"].toString().toStdString();
                        user.username = userObj["username"].toString().toStdString();

                        currMember.push_back(user);

                        QStandardItem *idItem = new QStandardItem(QString::fromStdString(user.id));
                        QStandardItem *usernameItem = new QStandardItem(QString::fromStdString(user.username));
                        model->setItem(i, 0, idItem);
                        model->setItem(i, 1, usernameItem);
                    }

                    tableView->setModel(model);
                }
            }
        }

        // Get task list
        std::string task_res = performGetTaskList(acc.session, currProject.id);
        QString taskJsonString = QString::fromStdString(task_res);
        QJsonDocument taskJsonDoc = QJsonDocument::fromJson(taskJsonString.toUtf8());
        if (!taskJsonDoc.isNull()) {
            if (taskJsonDoc.isObject()) {
                QJsonObject jsonObj = taskJsonDoc.object();
                int success = jsonObj["success"].toInt();
                QString message = jsonObj["message"].toString();
                if (!success) {
                    QMessageBox::critical(nullptr, "Error", message);
                } else {
                    QJsonArray dataArr = jsonObj["data"].toArray();
                    QTableView *tableView = taskWidget->findChild<QTableView*>("task_table");
                    QStandardItemModel *model = new QStandardItemModel(&window);

                    model->setHorizontalHeaderLabels({ "TaskId", "Name", "Status", "Assignee", "Comment", "Deadline", "Action" });

                    qDebug() << "Loading tasks : " << dataArr.size();

                    for (int i = 0; i < dataArr.size(); i++) {
                        QJsonObject taskObj = dataArr[i].toObject();
                        Task task;
                        task.id = taskObj["id"].toString().toStdString();
                        task.id_project = taskObj["id_project"].toString().toStdString();
                        task.id_manager = taskObj["id_manager"].toString().toStdString();
                        task.name = taskObj["name"].toString().toStdString();
                        task.status = taskObj["status"].toString().toStdString();
                        task.id_assign = taskObj["id_assign"].toString().toStdString();
                        task.comment = taskObj["comment"].toString().toStdString();
                        task.start_date = taskObj["start_date"].toString().toStdString();
                        task.end_date = taskObj["end_date"].toString().toStdString();

                        currTask.push_back(task);

                        string assignee;
                        std::string user_res = performGetUserById(task.id_assign);
                        QString jsonString = QString::fromStdString(user_res);
                        QJsonDocument jsonDoc = QJsonDocument::fromJson(jsonString.toUtf8());
                        if (!jsonDoc.isNull() && jsonDoc.isObject()) {
                            QJsonObject jsonObj = jsonDoc.object();
                            int success = jsonObj["success"].toInt();
                            if (success) {
                                QJsonObject jsonData = jsonObj["data"].toObject();
                                string owner = jsonData["username"].toString().toStdString();
                                if (!owner.empty()) assignee = owner;
                            }
                        }

                        QStandardItem *idItem = new QStandardItem(QString::fromStdString(task.id));
                        QStandardItem *nameItem = new QStandardItem(QString::fromStdString(task.name));
                        QStandardItem *statusItem = new QStandardItem(QString::fromStdString(task.status));
                        QStandardItem *assigneeItem = new QStandardItem(QString::fromStdString(assignee));
                        QStandardItem *commentItem = new QStandardItem(QString::fromStdString(task.comment));
                        QStandardItem *end_dateItem = new QStandardItem(QString::fromStdString(task.end_date));
                        model->setItem(i, 0, idItem);
                        model->setItem(i, 1, nameItem);
                        model->setItem(i, 2, statusItem);
                        model->setItem(i, 3, assigneeItem);
                        model->setItem(i, 4, commentItem);
                        model->setItem(i, 5, end_dateItem);
                    }

                    tableView->setModel(model);
                }
            }
        }
    });


    QTranslator translator;
    const QStringList uiLanguages = QLocale::system().uiLanguages();
    for (const QString &locale : uiLanguages) {
        const QString baseName = "TaskManager_" + QLocale(locale).name();
        if (translator.load(":/i18n/" + baseName)) {
            a.installTranslator(&translator);
            break;
        }
    }

    return a.exec();
}


